#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_b) {
	OPERAND al, dx;
	
	dx.type = OPR_REG;
	dx.data_size = 16; //%dx
	dx.addr = 2;
	operand_read(&dx); //get %dx

	al.type = OPR_REG;
	al.data_size = 8; //%al
	al.addr = 0;
	al.val = pio_read(dx.val, 1); //Input byte from port DX into AL
	operand_write(&al);
print_asm_0("in", "%dx, %al", 1);
	return 1;
}
