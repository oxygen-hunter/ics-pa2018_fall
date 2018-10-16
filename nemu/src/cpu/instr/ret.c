#include "cpu/instr.h"

make_instr_func(ret_near) { //0xc3
	OPERAND ret_addr;

	ret_addr.type = OPR_MEM;
	ret_addr.data_size = data_size;
	ret_addr.addr = cpu.esp;
	operand_read(&ret_addr);

print_asm_0("ret", "", 1);
	cpu.eip = ret_addr.val; //eip = ret address
	esp.val -= 4; //esp -= 4
	operand_write(&esp);

	return 0;
}
