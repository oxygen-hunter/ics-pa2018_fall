#include "cpu/instr.h"

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
print_asm_2("xor", "bv", &i, &rm);
	return len + 1; //opcode + modrm + imm_b
}
