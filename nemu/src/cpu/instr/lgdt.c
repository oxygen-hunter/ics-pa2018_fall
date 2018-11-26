#include "cpu/instr.h"

make_instr_func(lgdt) {
	OPERAND rm;
	rm.data_size = data_size;
	modrm_rm(eip + 1, &rm);
	uint32_t base = rm.val;
	uint32_t limit = rm.val & 0xffff;
}
