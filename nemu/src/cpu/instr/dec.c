#include "cpu/instr.h"

static void instr_execute_1op() {
	operand_read(&opr_src);
	opr_src.val = alu_sub(0x1, opr_src.val, data_size);
	operand_write(&opr_src);
}

make_instr_impl_1op(inc, rm, v); //0xff[1]
make_instr_impl_lop(inc, r, v); //0x48-4f
