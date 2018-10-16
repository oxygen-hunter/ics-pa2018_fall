#include "cpu/instr.h"

make_instr_func(ret_near) { //0xc3
	OPERAND ret_addr;

	ret_addr.type = OPR_MEM;
	ret_addr.data_size = data_size;
	ret_addr.addr = cpu.esp;
printf("now esp:%x\n",cpu.esp);
	operand_read(&ret_addr);

print_asm_0("ret", "", 1);
	cpu.eip = ret_addr.val; //eip = ret address
	cpu.esp += data_size / 8; //esp += 4 or 2
printf("ret's ret address:%x\n", cpu.eip);
printf("after ret's esp:%x\n", cpu.esp);
	return 0;
}
