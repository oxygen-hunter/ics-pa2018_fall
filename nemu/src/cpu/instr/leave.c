#include "cpu/instr.h"

make_instr_func(leave) { //0xc9
	OPERAND esp, ebp;

	esp.type = OPR_REG;
	esp.data_size = data_size;
	esp.addr = 4;

	ebp.type = OPR_REG;
	ebp.data_size = data_size;
	ebp.addr = 5;
	operand_read(&ebp);

	esp.val = ebp.val; //mov %ebp, %esp
	operand_write(&esp);
	return 1;
}
