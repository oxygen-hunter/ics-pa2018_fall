#include "cpu/instr.h"

make_instr_func(lgdt) {
	OPERAND rm;
	rm.data_size = data_size;

	int len = 1;
	len += modrm_rm(eip + 1, &rm);
	operand_read(&rm);
	uint32_t base = rm.val;
	uint32_t limit = rm.val & 0xffff; //low 16 bit
	cpu.gdtr.base = base;
	cpu.gdtr.limit = limit;
print_asm_1("lgdt", "", len, &rm);
printf("sreg: %d\n", SREG_CS);
	return len;
}
