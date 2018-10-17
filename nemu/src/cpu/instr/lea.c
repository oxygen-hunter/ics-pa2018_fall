#include "cpu/instr.h"

static void instr_execute_2op() {
/*attention: don't read opr_src, because you don't know what the f**king opr_src.addr is!*/
	//operand_read(&opr_src); //don't!
	//operand_read(&opr_dest); //right but needless
	opr_dest.val = opr_src.addr;
	operand_write(&opr_dest);
}

make_instr_impl_2op(lea, rm, r, v);
