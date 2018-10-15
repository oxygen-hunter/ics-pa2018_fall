#ifndef __INSTR_ADC_H__
#define __INSTR_ADC_H__

make_instr_func(adc_r2rm_b); //0x00
make_instr_func(adc_r2rm_v); //0x01
make_instr_func(adc_rm2r_b); //0x02
make_instr_func(adc_rm2r_v); //0x03
make_instr_func(adc_i2a_b); //0x04
make_instr_func(adc_i2a_v); //0x05

make_instr_func(adc_i2rm_bv); //0x83[2]

make_instr_func(adc_i2rm_v); //
#endif
