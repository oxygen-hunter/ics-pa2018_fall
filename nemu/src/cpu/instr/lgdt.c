#include "cpu/instr.h"
#include "memory/memory.h"

make_instr_func(lgdt) {
	OPERAND rm;

	int len = 1;
	len += modrm_rm(eip + 1, &rm);
	
	rm.data_size = 16;
	operand_read(&rm);
	
	cpu.gdtr.limit = rm.val; // load limit
	rm.addr = rm.addr + 2; // addr + 16bit
	rm.data_size = 32;
	operand_read(&rm);
	cpu.gdtr.base = rm.val; //load base

print_asm_1("lgdt", "", len, &rm);
	return len;
}
