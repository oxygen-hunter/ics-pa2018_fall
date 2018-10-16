#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
if(opr_src.data_size < opr_dest.data_size) opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
//printf("src + dest: %x + %x\n", opr_src.val, opr_dest.val);
	opr_dest.val = alu_xor(opr_src.val, opr_dest.val, data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(xor, r, rm, b); //0x00
make_instr_impl_2op(xor, r, rm, v); //0x01
make_instr_impl_2op(xor, rm, r, b); //0x02
make_instr_impl_2op(xor, rm, r, v); //0x03
make_instr_impl_2op(xor, i, a, b); //0x04
make_instr_impl_2op(xor, i, a, v); //0x05

make_instr_impl_2op(xor, i, rm, bv); //0x83[6]
make_instr_impl_2op(xor, i, rm, v); //0x81[6]

/* stupid version...
make_instr_func(__xor_i2rm_bv) { //0x83[6]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	operand_read(&imm); //get imm
	//rm.val = imm.val ^ rm.val;
	rm.val = alu_xor(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("xor", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}*/
