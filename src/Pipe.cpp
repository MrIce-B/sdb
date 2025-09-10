#include <unistd.h>
#include <fcntl.h>
#include <libsdb/Pipe.hpp>
#include <libsdb/Error.hpp>
#include <utility>

sdb::Pipe::Pipe(bool close_on_exec){
    // pipe2 允许在创建管道时设置管道上的标志，如进程调用exec* 族函数，则强制关闭管道。自动关闭不需要的文件描述符，防止资源泄漏
    if(pipe2(fds_,close_on_exec ? O_CLOEXEC : 0) < 0) {
        Error::send_errno("Pipe create failed");
    }
}

sdb::Pipe::~Pipe() {
    close_read();
    close_write();
}

int sdb::Pipe::release_read(){
    return std::exchange(fds_[read_fd],-1);
}

int sdb::Pipe::release_write(){
    return std::exchange(fds_[write_fd],-1);
}

void sdb::Pipe::close_read(){
    if(fds_[read_fd] != -1) {
        close(fds_[read_fd]);
        fds_[read_fd] = -1;
    }
}

void sdb::Pipe::close_write(){
    if(fds_[write_fd]) {
        close(fds_[write_fd]);
        fds_[write_fd] = -1;
    }
}

std::vector<std::byte> sdb::Pipe::read(){
    char buf[1024];
    int chars_read;
    if((chars_read =::read(fds_[read_fd],buf,sizeof(buf))) <0) {
        Error::send_errno("Could not read from pipe");
    }

    auto bytes = reinterpret_cast<std::byte*>(buf);
    return std::vector<std::byte>(bytes,bytes+chars_read);
}

void sdb::Pipe::write(std::byte*from ,std::size_t size) {
    if(::write(fds_[write_fd],from,size)<0) {
        Error::send_errno("Could not write to pipe");
    }
}


