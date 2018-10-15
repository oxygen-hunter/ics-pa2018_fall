#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	opr_dest.val = alu_sub(opr_src.val, opr_dest.val, data_size);
}

make_instr_impl_2op(cmp, i, rm, bv); //0x83[7]
make_instr_impl_2op(cmp, r, rm, b); //0x38
make_instr_impl_2op(cmp, r, rm, v); //0x39
make_instr_impl_2op(cmp, rm, r, b); //0x3a
make_instr_impl_2op(cmp, rm, r, v); //0x3b
make_instr_impl_2op(cmp, i, a, b); //0x3c
make_instr_impl_2op(cmp, i, a, v); //0x3d




/* stupid version
make_instr_func(__cmp_i2rm_bv) { //0x83[7]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	operand_read(&imm); //get imm
	//rm.val - imm.val;
	alu_sub(imm.val, rm.val, data_size);
	//operand_write(&rm);
print_asm_2("cmp", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}*/
