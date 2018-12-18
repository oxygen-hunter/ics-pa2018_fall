#include "cpu/instr.h"

make_instr_func(int_) {
	OPERAND imm;

print_asm_1("int", "", 1, &imm);
	return 2;
}
