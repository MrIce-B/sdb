#ifndef SDB_REGISTER_INFO_HPP
#define SDB_REGISTER_INFO_HPP

#include <cstdint>
#include <cstddef>
#include <string_view>
#include <sys/user.h>

namespace sdb
{
    // 为系统中的每个寄存器提供其唯一的枚举器值
    enum class register_id {
        // ?
    };

    // 指定给定寄存器是GPR, GPR的子寄存器（eax是rax的32位版本），FPR 或者是DR （调试寄存器）
    enum class register_type {
        gpr,
        sub_gpr,
        fpr,
        dr
    };

    // 指定解释寄存器的不同方式
    enum class register_format {
        uint,
        double_float,
        long_double,
        vector
    };

    // 收集关于单个寄存器的所有信息
    struct register_info
    {
        register_id id;
        std::string_view name;
        std::int32_t dwarf_id;
        std::size_t size;
        std::size_t offset;
        register_type type;
        register_format format;
    };

    // 系统中每个寄存器的信息的全局数组
    // inline 关键字可以让我们在头文件中定义这个数组，从而在初始化器自动推导出寄存器的数量
    // inline 关键字避免头文件全局变量的链接错误--- 所有包含该头文件的源文件共享同一个数组实例
    inline constexpr const register_info g_register_infos[] = {
        // ?
    };
    
    
} // namespace sdb






#endif // SDB_REGISTER_INFO_HPP