#ifndef __INSTR_CMP_H__
#define __INSTR_CMP_H__

make_instr_func(cmp_r2rm_b); //0x38
make_instr_func(cmp_r2rm_v); //0x39
make_instr_func(cmp_rm2r_b); //0x3a
make_instr_func(cmp_rm2r_v); //0x3b
make_instr_func(cmp_i2a_b); //0x3c
make_instr_func(cmp_i2a_v); //0x3d

make_instr_func(cmp_i2rm_bv); //0x83[7]

make_instr_func(cmp_i2rm_v); //0x81[7]

#endif
