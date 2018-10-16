#ifndef __INSTR_JCC_H__
#define __INSTR_JCC_H__

make_instr_func(jo_short_); //0x70
make_instr_func(jno_short_); //0x71
make_instr_func(jb_short_); //0x72
make_instr_func(jae_short_); //0x73
make_instr_func(je_short_); //0x74
make_instr_func(jne_short_); //0x75
make_instr_func(jna_short_); //0x76 jbe
make_instr_func(ja_short_); //0x77
make_instr_func(js_short_); //0x78
make_instr_func(jns_short_); //0x79
make_instr_func(jp_short_); //0x7a
make_instr_func(jnp_short_); //0x7b
make_instr_func(jl_short_); //0x7c
make_instr_func(jge_short_); //0x7d
make_instr_func(jle_short_); //0x7e
make_instr_func(jg_short_); //0x7f

make_instr_func(jo_near); //0x0f 80
make_instr_func(jno_near); //0x0f 81
make_instr_func(jb_near); //0x0f 82
make_instr_func(jae_near); //0x0f 83
make_instr_func(je_near); //0x0f 84
make_instr_func(jne_near); //0x0f 85
make_instr_func(jna_near); //0x0f 86
make_instr_func(ja_near); //0x0f 87
make_instr_func(js_near); //0x0f 88
make_instr_func(jns_near); //0x0f 89
make_instr_func(jp_near); //0x0f 8a
make_instr_func(jnp_near); //0x0f 8b
make_instr_func(jl_near); //0x0f 8c
make_instr_func(jge_near); //0x0f 8d
make_instr_func(jle_near); //0x0f 8e
make_instr_func(jg_near); //0x0f 8f

#endif
