#ifndef __INSTR_SBB_H__
#define __INSTR_SBB_H__

make_instr_func(sbb_r2rm_b); //0x18
make_instr_func(sbb_r2rm_v); //0x19
make_instr_func(sbb_rm2r_b); //0x1a
make_instr_func(sbb_rm2r_v); //0x1b
make_instr_func(sbb_i2a_b); //0x1c
make_instr_func(sbb_i2a_v); //0x1d

make_instr_func(sbb_i2rm_bv); //0x83[3]
make_instr_func(sbb_i2rm_b); //0x80[3]
make_instr_func(sbb_i2rm_v); //0x81[3]
#endif
