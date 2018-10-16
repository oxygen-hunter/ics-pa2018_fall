#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
if(opr_src.data_size < opr_dest.data_size) opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
//printf("src or dest: %x or %x\n", opr_src.val, opr_dest.val);
	opr_dest.val = alu_or(opr_src.val, opr_dest.val, data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(or, r, rm, b); //0x08
make_instr_impl_2op(or, r, rm, v); //0x09
make_instr_impl_2op(or, rm, r, b); //0x0a
make_instr_impl_2op(or, rm, r, v); //0x0b
make_instr_impl_2op(or, i, a, b); //0x0c
make_instr_impl_2op(or, i, a, v); //0x0d

make_instr_impl_2op(or, i, rm, bv); //0x83[0]
make_instr_impl_2op(or, i, rm, v);

/* stupid version...
make_instr_func(__or_i2rm_bv) { //0x83[1]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	operand_read(&imm); //get imm
	//rm.val = imm.val | rm.val;
	rm.val = alu_or(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("or", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}*/
