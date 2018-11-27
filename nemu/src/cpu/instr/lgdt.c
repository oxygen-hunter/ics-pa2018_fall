#include "cpu/instr.h"
#include "memory/memory.h"

make_instr_func(lgdt) {
	OPERAND rm;
	rm.data_size = 16;

	int len = 1;
	len += modrm_rm(eip + 1, &rm);
	operand_read(&rm);
	/*uint32_t base = rm.val;
	uint32_t limit = rm.val & 0xffff; //low 16 bit
	cpu.gdtr.base = base;
	cpu.gdtr.limit = limit;*/
	printf("addr:%x\n", rm.addr);
	printf("val:%x\n", rm.val);
	
	cpu.gdtr.limit = rm.val;
	rm.addr = rm.addr + 2*8;
	rm.data_size = 32;
	operand_read(&rm);
	cpu.gdtr.base = rm.val;
print_asm_1("lgdt", "", len, &rm);
	return len;
}
