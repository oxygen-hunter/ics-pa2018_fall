#include "cpu/instr.h"

make_instr_func(in_b) {
	OPERAND al, dx;
	
	dx.type = OPR_REG;
	dx.data_size = 16; //%dx
	dx.addr = 2;
	operand_read(&dx); //get %dx

	al.type = OPR_REG;
	al.data_size = 8; //%al
	al.addr = 0;
	al.val = pio_read(dx.val, 1); //Input byte from port dx into al
	return 1;
}
