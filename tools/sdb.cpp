// ************************* Launching and Attaching to Process **********************************************

// #include <iostream>
// #include <unistd.h>
// #include <sys/ptrace.h>
// #include <string_view>
// #include <sys/types.h>
// #include <sys/wait.h>
// namespace  {
//     pid_t attach(int argc,const char** argv){
//         pid_t pid=0;
//         // Passing PID
//         // 如果用户通过 `-p` 参数指定 PID，附加到该进程
// 		if(argc == 3 && argv[1]==std::string_view("-p")){  /*mark1*/
//             pid ==std::atoi(argv[2]);
//             if(pid == 0){
//                 std::cerr << "Invalid PID\n";
//                 return -1;
//             }
// 		    if(ptrace(PTRACE_ATTACH,pid,/*addr=*/nullptr,/*data=*/nullptr)  < 0){/*mark2*/
//                 std::perror("Could not attach to process");
//                 return -1;
//             }
//         }
//         // Passing Process
//         // 如果用户未指定 `-p` 参数，启动一个新的子进程并对其进行跟踪。
//         else{
//             const char* program_path = argv[1];
//             if((pid=fork())<0){ /*mark3*/
//                 std::cerr << "Fork failed\n";
//                 return -1;
//             }

//             if(pid==0){
//                 // we're in the child process
//                 // Execute debugger
//                 if(ptrace(PTRACE_TRACEME,0,/*addr=*/nullptr,/*data=*/nullptr) < 0){ /*mark4*/
//                     std::perror("Tracing failed");
//                     return -1;
//                 }
//                 if(execlp(program_path, program_path, nullptr) < 0){/*mark5*/
//                     std::perror("Exec failed");
//                     return -1;
//                 }
//             }
//         }
//         return pid;
//     }
// }

// int main(int argc, const char** argv) {
//     if (argc == 1) {
//         std::cerr <<" No arguments given\n"; 
//         return -1;
//     } 

//     pid_t pid = attach(argc, argv);

//     int wait_status;
//     int options = 0;
//     if(waitpid(pid,&wait_status,options) < 0){ /*mark6*/
//         std::perror("Waitpid failed");
//         return -1;
//     }
//     return 0;
// } 

// ************************ Launching and Attaching to Process *********************************


// ************************* Adding a User Interface ***********************************************
// #include <iostream>
// #include <unistd.h>
// #include <sys/ptrace.h>
// #include <string_view>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <editline/readline.h>
// #include <string>
// #include <vector>
// #include <sstream>
// #include <algorithm>
// namespace {
//     pid_t attach(int argc,const char** argv){
//         pid_t pid=0;
//         // Passing PID
//         // 如果用户通过 `-p` 参数指定 PID，附加到该进程
// 		if(argc == 3 && argv[1]==std::string_view("-p")){  /*mark1*/
//             pid =std::atoi(argv[2]);
//             if(pid == 0){
//                 std::cerr << "Invalid PID\n";
//                 return -1;
//             }
// 		    if(ptrace(PTRACE_ATTACH,pid,/*addr=*/nullptr,/*data=*/nullptr)  < 0){/*mark2*/
//                 std::perror("Could not attach to process");
//                 return -1;
//             }
//         }
//         // Passing Process
//         // 如果用户未指定 `-p` 参数，启动一个新的子进程并对其进行跟踪。
//         else{
//             const char* program_path = argv[1];
//             if((pid=fork())<0){ /*mark3*/
//                 std::cerr << "Fork failed\n";
//                 return -1;
//             }

//             if(pid==0){
//                 // we're in the child process
//                 // Execute debugger
//                 if(ptrace(PTRACE_TRACEME,0,/*addr=*/nullptr,/*data=*/nullptr) < 0){ /*mark4*/
//                     std::perror("Tracing failed");
//                     return -1;
//                 }
//                 if(execlp(program_path, program_path, nullptr) < 0){/*mark5*/
//                     std::perror("Exec failed");
//                     return -1;
//                 }
//             }
//         }
//         return pid;
//     }
//     std::vector<std::string> split(std::string_view str,char delimiter){
//         std::vector<std::string> out{};
//         std::stringstream ss {std::string(str)};
//         std::string item;
//         while(std::getline(ss,item,delimiter)){
//             if(!item.empty()){   // this judge null is necessary ??
//                 out.push_back(item);
//             }
//         }
//         return out;
//     }
//     bool is_prefix(std::string_view str,std::string_view of){
//         if (str.size()>of.size()) {
//             return false;
//         }
//         return std::equal(str.begin(),str.end(),of.begin());
//     }
//     void resume(pid_t pid){
//         if(ptrace(PTRACE_CONT,pid,nullptr,nullptr)<0) {
//             std::cerr << "Could not continue"<<std::endl;
//             std::exit(-1);
//         }
//     }
//     void wait_on_signal(pid_t pid){
//         int wait_status;
//         int options = 0;
//         if (waitpid(pid,&wait_status,options) < 0) {
//             std::perror("Waitpid failed");
//             std::exit(-1);
//         }
//     }
//     void handle_command(pid_t pid, std::string_view line) {
//         auto args = split(line, ' ');
//         auto command = args[0];

//         if (is_prefix(command,"continue")) {
//             resume(pid);
//             wait_on_signal(pid);
//         } else {
//             std::cerr << "Unknown command: " << command << "\n";
//         }
//     }
// }

// int main(int argc, const char** argv) {
//     if (argc == 1) {
//         std::cerr << "No arguments given\n"; 
//         return -1;
//     } 
//     pid_t pid = attach(argc, argv);
//     char *line = nullptr;
//     while ((line = readline("sdb> ")) != nullptr) {
//         std::string line_str;
//         if (line == std::string_view("")) {
//             free(line);
//             if (history_length > 0) {
//                 line_str = history_list()[history_length - 1]->line; 
//             }
//         } else {
//             line_str = line;
//             add_history(line);
//             free(line);
//         }

//         if (!line_str.empty()) {
//             handle_command(pid,line_str);
//         }
//     }
    
//     return 0;
// }

// ************************* Adding a User Interface ***********************************************



// ************************* Refactoring into a Library ***********************************************



// ************************* Refactoring into a Library ***********************************************

#include <libsdb/Process.hpp>
#include <vector>
#include <iostream>
#include <cstring>
#include <libsdb/Error.hpp>
#include <editline/readline.h>

namespace {
    std::unique_ptr<sdb::Process> attach(int argc, const char** argv) {
        // passing pid 
        if(argc == 3 && argv[1] == std::string_view("-p")) { /*mark1*/
            pid_t pid = std::atoi(argv[2]);
            return sdb::Process::attach(pid);
        }
        // passing program name 
        else {
            const char * program_path = argv[1];
            return sdb::Process::launch(std::filesystem::path(program_path));
        }
    }
    
    std::vector<std::string> split(std::string_view str,char delimiter){
        std::vector<std::string> out{};
        std::stringstream ss {std::string(str)};
        std::string item;
        while(std::getline(ss,item,delimiter)){
            if(!item.empty()){   // this judge null is necessary ??
                out.push_back(item);
            }
        }
        return out;
    }

    bool is_prefix(std::string_view str,std::string_view of){
        if (str.size()>of.size()) {
            return false;
        }
        return std::equal(str.begin(),str.end(),of.begin());
    }  

    void print_stop_reason(const sdb::Process& process, sdb::stop_reason reason ) {
        std::cout << "Process " << process.pid() << ' ';
        switch (reason.reason)
        {
        case sdb::Process_State::exited:
            std::cout << "exit with status" << static_cast<int>(reason.info);
            break;
        case sdb::Process_State::terminated:
            std::cout << "terminated with signal " <<  sigabbrev_np(reason.info);
            break;
        case sdb::Process_State::stopped:
            std::cout << "stopped with signal " << sigabbrev_np(reason.info);
            break;
        default:
            break;
        }
        std::cout << std::endl;
    }

    void handle_command(std::unique_ptr<sdb::Process>& process, std::string_view line) {
        auto args = split(line, ' ');
        auto command = args[0];
        if(is_prefix(command,"continue")){
            process->resume();
            auto reason = process->wait_on_signal();
            print_stop_reason(*process, reason);
        } else {
            std::cerr<< "Unknown command: " << command << "\n";
        }
    }

    void main_loop(std::unique_ptr<sdb::Process>& process) {
        char* line = nullptr;
        while((line = readline("sdb> ")) != nullptr) {
            std::string line_str;
            if(line==std::string_view("")) {
                free(line);
                if(history_length >0) {
                    line_str = history_list()[history_length -1]->line;
                }
            } else {
                line_str = line;
                add_history(line);
                free(line);
            }
            if(!line_str.empty()) {
                try {
                    handle_command(process, line_str);
                }
                catch (const sdb::Error& err) {
                    std::cout << err.what() << std::endl;
                }
            }
        }
    }
}

int main(int argc,const char** argv) {
    if(argc == 1) {
        std::cerr << "No arguments given\n";
        return -1;
    }

    try{
        auto process = attach(argc,argv);
        main_loop(process);
    } 
    catch (const sdb::Error& err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}