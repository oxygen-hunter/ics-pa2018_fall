#include "cpu/instr.h"

make_instr_func(call_near) {
	OPERAND rel, mem;
	rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
	rel.data_size = data_size;
	rel.addr = eip + 1;

	operand_read(&rel);

	esp.val -= data_size / 8;
		
	mem.type = OPR_MEM; //push ret address
	mem.data_size = data_size;
	mem.val = eip + 1 + data_size / 8;
	mem.addr = cpu.esp;
	operand_write(&mem);
printf("call's ret addr:%x\n", mem.val);
//printf("esp:%x\n", esp.val);

	int offset = sign_ext(rel.val, data_size);
	print_asm_1("call", "", 2, &rel);

	cpu.eip += offset;

        return 1 + data_size / 8;
}
