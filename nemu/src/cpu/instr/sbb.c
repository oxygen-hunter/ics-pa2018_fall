#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val = alu_sbb(opr_src.val, opr_dest.val, data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sbb, r, rm, b); //0x18
make_instr_impl_2op(sbb, r, rm, v); //0x19
make_instr_impl_2op(sbb, rm, r, b); //0x1a
make_instr_impl_2op(sbb, rm, r, v); //0x1b
make_instr_impl_2op(sbb, i, a, b); //0x1c
make_instr_impl_2op(sbb, i, a, v); //0x1d

make_instr_impl_2op(sbb, i, rm, bv); //0x83[3]
make_instr_impl_2op(sbb, i, rm, v); //0x81[3]
