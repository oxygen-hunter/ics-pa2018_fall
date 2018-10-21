#include "cpu/instr.h"

make_instr_func(call_near) {
	OPERAND rel, mem;
	rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
	rel.data_size = data_size;
	rel.addr = eip + 1;

	operand_read(&rel);

	cpu.esp -= data_size / 8;
		
	mem.type = OPR_MEM; //push ret address
	mem.data_size = data_size;
	mem.val = eip + 1 + data_size / 8;
cpu.esp -= data_size / 8;
	mem.addr = cpu.esp;
	operand_write(&mem);
//printf("call's ret addr:%x\n", mem.val);
//printf("after call's esp:%x\n", cpu.esp);

	int offset = sign_ext(rel.val, data_size);
print_asm_1("call", "", 1 + data_size / 8, &rel);

	cpu.eip += offset;

	return 1 + data_size / 8;
}

make_instr_func(call_near_indirect) { //0xff[2]
	OPERAND rm, mem;
	
	int len = 1;
	rm.data_size = data_size;
	
	len += modrm_rm(eip + 1, &rm);

	operand_read(&rm);

	mem.type = OPR_MEM; //push ret address
	mem.data_size = data_size;
	mem.val = eip + len;
cpu.esp -= data_size / 8;
	mem.addr = cpu.esp;
	operand_write(&mem);
print_asm_1("call", "", len, &rm);

	cpu.eip = rm.val;

	return 0;
}
