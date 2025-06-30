#include <libsdb/Error.hpp>
#include <libsdb/Process.hpp>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

std::unique_ptr<sdb::Process> sdb::Process::launch(std::filesystem::path path){
    pid_t pid ;
    if((pid = fork())<0) {
        Error::send_errno("fork failed");
    } 

    if (pid == 0) {
        // 子进程
        if(ptrace(PTRACE_TRACEME,0,nullptr,nullptr) <0) {
            Error::send_errno("ptrace failed");
        }
        if(execlp(path.c_str(), path.c_str(), nullptr) < 0) {
            Error::send_errno("exec failed");
        }
    }

    std::unique_ptr<sdb::Process> proc(new Process(pid, /*terminate_on_end=*/true));
    proc->wait_on_signal();
    return proc;
}

std::unique_ptr<sdb::Process> sdb::Process::attach(pid_t pid) {
    if(pid == 0) {
        Error::send("Invalid PID");
    }

    if(ptrace(PTRACE_ATTACH,pid,nullptr,nullptr) < 0) {
        Error::send_errno("Could not attach to process");
    }
    std::unique_ptr<sdb::Process> proc(new Process(pid, /*terminate_on_end=*/false));
    proc->wait_on_signal();
    return proc;
}

sdb::Process::~Process() {
    if(pid_ != 0) {
        int status;
        if(state_ == Process_State::running) {
            kill(pid_,SIGSTOP);
            waitpid(pid_, &status, 0);
        }
        ptrace(PTRACE_DETACH, pid_, nullptr, nullptr);
        kill(pid_, SIGCONT);

        if(terminate_on_end_) {
            kill(pid_, SIGKILL);
            waitpid(pid_, &status, 0);
        }
    }
}

void sdb::Process::resume() {
    if(ptrace(PTRACE_CONT, pid_, nullptr, nullptr) < 0) {
        Error::send_errno("Could not resume");
    }
    state_ = Process_State::running;
}

sdb::stop_reason::stop_reason(int wait_status) {
    if(WIFEXITED(wait_status)) {
        reason == Process_State::exited;
        info = WEXITSTATUS(wait_status);
    } else if (WIFSIGNALED(wait_status)) {
        reason = Process_State::terminated;
        info = WTERMSIG(wait_status);
    } else if (WIFSTOPPED(wait_status)) {
        reason = Process_State::stopped;
        info = WSTOPSIG(wait_status);
    }
}

sdb::stop_reason sdb::Process::wait_on_signal() {
    int wait_status;
    int options = 0;
    if(waitpid(pid_,&wait_status,options) < 0) {
        Error::send_errno("waitpid failed");
    }
    stop_reason reason(wait_status);
    state_ = reason.reason;
    return  reason;
}