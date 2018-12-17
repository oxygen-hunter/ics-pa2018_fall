#include "cpu/instr.h"

make_instr_func(lidt) {
	OPERAND rm;

	int len = 1;
	len += modrm_rm(eip + 1, &rm);
	
	rm.data_size = 16;
	operand_read(&rm);
	
	cpu.idtr.limit = rm.val; // load limit
	rm.addr = rm.addr + 2; // addr + 16bit
	rm.data_size = 32;
	operand_read(&rm);
	cpu.idtr.base = rm.val; //load base

print_asm_1("lidt", "", len, &rm);
	return len;
}
