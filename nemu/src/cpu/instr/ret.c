#include "cpu/instr.h"

make_instr_func(ret_near) { //0xc3
	OPERAND ret_addr, esp;

	esp.type = OPR_REG;
	esp.data_size = data_size;
	esp.addr = 4;
	operand_read(&esp);

	ret_addr.type = OPR_MEM;
	ret_addr.data_size = data_size;
	ret_addr.addr = esp.val;
	operand_read(&ret_addr);
//printf("ret addr:%x\n", ret_addr.val);
print_asm_0("ret", "", 1);
	cpu.eip = ret_addr.val; //eip = ret address
	esp.val -= 4; //esp -= 4
	operand_write(&esp);

	return 0;
}
