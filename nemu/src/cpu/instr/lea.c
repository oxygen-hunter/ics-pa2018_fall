#include "cpu/instr.h"

/* error: lea instr's len is unknown, so marco is ineffective
static void instr_execute_2op() {
	opr_dest.val = opr_src.addr;
	operand_write(&opr_dest);
}*/

make_instr_impl_2op(lea, rm, r, v);
