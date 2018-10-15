#include "cpu/instr.h"

make_instr_func(__or_r2rm_b); //0x08

make_instr_func(__or_r2rm_v); //0x09
make_instr_func(__or_rm2r_b); //0x0a
make_instr_func(__or_rm2r_v); //0x0b
make_instr_func(__or_i2a_b); //0x0c
make_instr_func(__or_i2a_v); //0x0d

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

	return len + 1; //opcode + modrm + imm_b
}
