#include "cpu/instr.h"

static void instr_execute_1op() {
	operand_read(&opr_src);
	opr_dest.val = alu_add(0x1, opr_src.val, data_size);
	operand_write(&opr_src);
}
