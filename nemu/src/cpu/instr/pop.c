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
mem.sreg = SREG_DS;
	operand_read(&mem);

	r.val = mem.val;
	operand_write(&r);

	cpu.esp += data_size / 8;
//printf("pop's:%x\n", mem.val);
//printf("after pop's esp:%x\n", cpu.esp);
print_asm_1("pop", "l", 1, &r);
	return 1;
}

make_instr_func(popa) {
	OPERAND mem;
	OPERAND DI, SI, BP, /*SP,*/ BX, DX, CX, AX; // order mustn't change, throwaway SP.
	
	DI.type = SI.type = BP.type = BX.type = DX.type = CX.type = AX.type = OPR_REG;
	DI.data_size = SI.data_size = BP.data_size = BX.data_size = DX.data_size = CX.data_size = AX.data_size = data_size;
	DI.addr = 7; sI.addr = 6; BP.addr = 5; BX.addr = 3; DX.addr = 2; CX.addr = 1; AX.addr = 0;

	mem.type = OPR_MEM;
	mem.data_size = data_size;
	mem.sreg = SREG_DS;
	
	mem.addr = cpu.esp;
	operand_read(&mem);
	DI.val = mem.val;
	operand_write(&DI);
	cpu.esp = cpu.esp - data_size / 8;


	print_asm_0("popa", "", 1);
	return 1;
}
