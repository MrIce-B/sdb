// 用户不应该直接包含，而应该先定义DEFINE_REGISTER 再包含
#ifndef DEFINE_REGISTER
#error "This file is intended for textual inclusion with the\
DEFINE_REGISTER macro defined"
#endif

// 获取user内部的寄存器成员的偏移量，然后降给定寄存器 user_regs_struct 的偏移量添加到它
#define GPR_OFFSET(reg) (offsetof(user, regs) + offsetof(user_regs_struct, reg))

// --------------------HELPTER MACRO ---------------------------------------

// 定义64位GPR的 helpter macro
#define DEFINE_GPR_64(name, dwarf_id) \
    DEFINE_REGISTER(name, dwarf_id, 8, GPR_OFFSET(name), \
    register_type::gpr, register_format::uint)

// 采用子寄存器的名称和它们所属的寄存器的名称（super）
// 子寄存器没有DWARF_ID 因此我们在此字段中使用虚拟值-1
#define DEFINE_GPR_32(name, super) \
    DEFINE_REGISTER(name, -1, 4, GPR_OFFSET(super), \
    register_type::sub_gpr, register_format::uint)

#define DEFINE_GPR_16(name, super) \
    DEFINE_REGISTER(name, -1, 2, GPR_OFFSET(super), \
    register_type::sub_gpr, register_format::uint)

#define DEFINE_GPR_8H(name, super) \
    DEFINE_REGISTER(name, -1, 1, GPR_OFFSET(super) + 1, \
    register_type::sub_gpr, register_format::uint)

#define DEFINE_GPR_8L(name, super) \
    DEFINE_REGISTER(name, -1, 1, GPR_OFFSET(super), \
    register_type::sub_gpr, register_format::uint)

// --------------------HELPTER MACRO ---------------------------------------

DEFINE_GPR_64(rax, 0),
DEFINE_GPR_64(rdx, 1),
DEFINE_GPR_64(rcx, 2),
DEFINE_GPR_64(rbx, 3),
DEFINE_GPR_64(rsi, 4),
DEFINE_GPR_64(rdi, 5),
DEFINE_GPR_64(rbp, 6),
DEFINE_GPR_64(rsp, 7),
DEFINE_GPR_64(r8, 8),
DEFINE_GPR_64(r9, 9),
DEFINE_GPR_64(r10, 10),
DEFINE_GPR_64(r11, 11),
DEFINE_GPR_64(r12, 12),
DEFINE_GPR_64(r13, 13),
DEFINE_GPR_64(r14, 14),
DEFINE_GPR_64(r15, 15),
DEFINE_GPR_64(rip, 16),
DEFINE_GPR_64(eflags, 49),
DEFINE_GPR_64(cs, 51),
DEFINE_GPR_64(fs, 54),
DEFINE_GPR_64(gs, 55),
DEFINE_GPR_64(ss, 52),
DEFINE_GPR_64(ds, 53),
DEFINE_GPR_64(es, 50),
