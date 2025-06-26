#ifndef ERROR_HPP 
#define ERROR_HPP

#include <stdexcept>
#include <cstring>

namespace sdb{
    class Error: public std::runtime_error{
        public:
            [[noreturn]] // 向编译器表明该函数在退出时不会返回
            static void send(const std::string& what) { throw Error(what);}
            [[noreturn]] 
            // 这个函数类似于 std::perror 
            static void send_errno(const std::string& prefix) {
                throw Error(prefix + ":" +std::strerror(errno));
            }
        private:
            Error(const std::string& what): std::runtime_error(what){}
    };
}

#endif // ERROR_HPP