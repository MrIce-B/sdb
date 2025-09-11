#ifndef SDB_PROCESS_HPP
#define SDB_PROCESS_HPP

#include <filesystem>
#include <memory>
#include <sys/types.h>

namespace sdb {
    // 枚举类 c++11 的功能，能够阻止枚举器值隐式地转化为整数或者从整数转换为枚举器值
    enum class Process_State{
        stopped,
        running,
        exited,
        terminated,
    };

    struct stop_reason {
        stop_reason(int wait_status);

        Process_State reason;
        std::uint8_t info;
    };

    class Process {
        public:
            // 确保用户在不使用这些静态成员函数的情况下构造Process对象
            // 禁止默认构造函数、拷贝构造函数和赋值运算符
            Process() = delete;
            Process(const Process&) = delete;
            Process& operator=(const Process&) = delete;
            ~Process();

            static std::unique_ptr<Process> launch(std::filesystem::path path, bool debug = true);
            static std::unique_ptr<Process> attach(pid_t pid);

            void resume();
            stop_reason wait_on_signal();
            // const 关键字放在函数参数列表之后，它的作用是声明这个成员函数不会修改对象的状态。
            pid_t pid() const { return pid_; }  
            Process_State state() const { return state_; }
        
        private: 
            // 将构造函数设为私有，以便客户端代码必须使用 static launch 或 attach 方法来创建 Process 对象
            Process(pid_t pid, bool terminate_on_end, bool is_attached ):pid_(pid), terminate_on_end_(terminate_on_end),is_attached_(is_attached) {}

        private: 
            pid_t pid_;
            bool terminate_on_end_ = true;
            bool is_attached_ = true;
            Process_State state_ = Process_State::stopped;
    };
}


#endif // SDB_PROCESS_HPP