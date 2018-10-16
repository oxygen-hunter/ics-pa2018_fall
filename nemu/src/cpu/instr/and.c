#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
//printf("opr_src.data_size:%u\nopr_dest.data_size:%u\n", opr_src.data_size, opr_dest.data_size);
if(opr_src.data_size < opr_dest.data_size) opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
//printf("opr_src.val:%x\n", opr_src.val);
	opr_dest.val = alu_and(opr_src.val, opr_dest.val, data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(and, i, rm, bv);

/* stupid version
make_instr_func(__and_i2rm_bv) { //0x83[4]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	operand_read(&imm); //get imm
	//rm.val = imm.val & rm.val;
	rm.val = alu_and(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("and", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}*/
