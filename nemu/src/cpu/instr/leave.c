#include "cpu/instr.h"

make_instr_func(leave) { //0xc9
	OPERAND esp, ebp, mem;

	esp.type = OPR_REG;
	esp.data_size = data_size;
esp.sreg = SREG_SS; //2018.11.27 15:46
	esp.addr = 4;

	ebp.type = OPR_REG;
	ebp.data_size = data_size;
	ebp.addr = 5;
ebp.sreg = SREG_SS; //2018.11.27 15:46
	operand_read(&ebp);

	esp.val = ebp.val; //mov %ebp/bp, %esp/sp
	operand_write(&esp);

	mem.type = OPR_MEM; //pop %ebp/bp
	mem.data_size = data_size;
	mem.addr = esp.val;
mem.sreg = SREG_DS; //2018.11.27 15:46
	operand_read(&mem);

	ebp.val = mem.val;
	operand_write(&ebp);

	cpu.esp += data_size / 8;
print_asm_0("leave", "", 1);
	return 1;
}
