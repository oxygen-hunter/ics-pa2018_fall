#ifndef __INSTR_JMP_H__
#define __INSTR_JMP_H__

make_instr_func(jmp_near); //0xe9
make_instr_func(jmp_short); //0xeb
make_instr_func(jmp_near_indirect); //0xff[4]

#endif
