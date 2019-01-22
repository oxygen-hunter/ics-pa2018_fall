#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
	alu_and(opr_src.val, opr_dest.val, data_size);
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
}

make_instr_impl_2op(test, r, rm, b); //0x84
make_instr_impl_2op(test, r, rm, v); //0x85
make_instr_impl_2op(test, i, rm, b); //0xf6[0]
make_instr_impl_2op(test, i, rm, v); //0xf7[0]
make_instr_impl_2op(test, i, a, b); //0xa8
make_instr_impl_2op(test, i, a, v); //0xa9
