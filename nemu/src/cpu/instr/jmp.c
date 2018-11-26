#include "cpu/instr.h"

/* error: jmp short means len = 0, buf marco's len = 1, modify marco is too hard
static void make_instr_impl_1op() {
	operand_read(&src);
	eip = src.val;
	operand_write(&src);
}*/

make_instr_func(jmp_near) { //0xe9
	OPERAND rel;
	rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
	rel.data_size = data_size;
	rel.addr = eip + 1;

	operand_read(&rel);

	int offset = sign_ext(rel.val, data_size);
print_asm_1("jmp", "", 1 + data_size / 8, &rel);

	cpu.eip += offset;

	return 1 + data_size / 8;
}

make_instr_func(jmp_short) { //0xeb
	OPERAND imm;
	
	imm.type = OPR_IMM;
imm.sreg = SREG_CS;
	imm.data_size = 8;
	imm.addr = eip + 1;
	operand_read(&imm);

	int offset = sign_ext(imm.val, 8);
print_asm_1("jmp", "b", 2, &imm);

	cpu.eip += offset;

	return 2;
}

make_instr_func(jmp_near_indirect) { //0xff[4]
	OPERAND rm;
	
	int len = 1;
	rm.data_size = data_size;
	
	len += modrm_rm(eip + 1, &rm);

	operand_read(&rm);
print_asm_1("jmp", "", len, &rm);
//printf("jmp near indirect to:%x\n", rm.val);
	cpu.eip = rm.val;

	return 0;
}

make_instr_func(jmp_far_imm) {
	OPERAND imm;
	
	imm.addr = eip + 1;
	imm.data_size = 32;
	operand_read(&imm);
printasm_1("jmp", "", 6, &rm);
	cpu.eip = imm.val;
	return 0;
}



