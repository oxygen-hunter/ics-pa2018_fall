#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
if(opr_src.data_size < opr_dest.data_size) opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
	opr_dest.val = alu_sub(opr_src.val, opr_dest.val, data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sub, i, rm, bv);

/* stupid version...
make_instr_func(__sub_i2rm_bv) { //0x83[5]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	operand_read(&imm); //get imm
	//rm.val -= imm.val;
	rm.val = alu_sub(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("sub", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}

make_instr_func(__sbb_i2rm_bv) { //0x83[3]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	operand_read(&imm); //get imm
	//rm.val -= imm.val + cpu.CF;
	rm.val = alu_sbb(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("sbb", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}
*/
