#ifndef __INSTR_ADD_H__
#define __INSTR_ADD_H__

make_instr_func(__add_r2rm_b); //0x00
make_instr_func(__add_r2rm_v); //0x01
make_instr_func(__add_rm2r_b); //0x02
make_instr_func(__add_rm2r_v); //0x03
make_instr_func(__add_i2a_b); //0x04
make_instr_func(__add_i2a_v); //0x05

make_instr_func(__add_i2rm_bv); //0x83[0]
make_instr_func(__adc_i2rm_bv); //0x83[2]

make_instr_func(add_i2rm_v); //0x81[0]
#endif
