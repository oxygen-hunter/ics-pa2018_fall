#include "cpu/instr.h"

make_instr_func(iret) {
	OPERAND mem;

	mem.data_size = 32;
	mem.type = OPR_MEM;
	mem.sreg = SREG_DS;

	mem.addr = cpu.esp; // pop EIP
	operand_read(&mem);
	cpu.eip = mem.val;
	cpu.esp = cpu.esp + 4;

	mem.addr = cpu.esp; // pop CS
	operand_read(&mem);
	cpu.cs.val = mem.val;
	cpu.esp = cpu.esp + 4;

	mem.addr = cpu.esp; // pop EFLAGS
	operand_read(&mem);
	cpu.eflags.val = mem.val;
	cpu.esp = cpu.esp + 4;

print_asm_0("iret", "", 1);
	return 1;
}
