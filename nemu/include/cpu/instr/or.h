#ifndef __INSTR_OR_H__
#define __INSTR_OR_H__

make_instr_func(or_r2rm_b); //0x08
make_instr_func(or_r2rm_v); //0x09
make_instr_func(or_rm2r_b); //0x0a
make_instr_func(or_rm2r_v); //0x0b
make_instr_func(or_i2a_b); //0x0c
make_instr_func(or_i2a_v); //0x0d

make_instr_func(or_i2rm_bv); //0x83[1]
make_instr_func(or_i2rm_b); //0x80[1]
make_instr_func(or_i2rm_v); //0x81[1]

#endif
