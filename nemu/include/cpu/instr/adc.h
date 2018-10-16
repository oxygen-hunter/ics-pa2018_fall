#ifndef __INSTR_ADC_H__
#define __INSTR_ADC_H__

make_instr_func(adc_r2rm_b); //0x10
make_instr_func(adc_r2rm_v); //0x11
make_instr_func(adc_rm2r_b); //0x12
make_instr_func(adc_rm2r_v); //0x13
make_instr_func(adc_i2a_b); //0x14
make_instr_func(adc_i2a_v); //0x15

make_instr_func(adc_i2rm_bv); //0x83[2]
make_instr_func(adc_i2rm_b); //0x80[2]
make_instr_func(adc_i2rm_v); //0x81[2]
#endif
