#include "cpu/instr.h"

/* pop ebx can't use marco.
static void instr_execute_1op() {
	operand_read(&opr_src)
}*/

make_instr_func(pop_r_v) { //0x58-0x5f
	OPERAND r, mem;

	r.type = OPR_REG;
	r.data_size = data_size;
	r.addr = opcode & 0x7;

	mem.type = OPR_MEM;
	mem.data_size = data_size;
	mem.addr = cpu.esp;
	operand_read(&mem);

	r.val = mem.val;
	operand_write(&r);

	cpu.esp -= 4;

print_asm_1("pop", "l", 1, &r);
	return 1;
}
