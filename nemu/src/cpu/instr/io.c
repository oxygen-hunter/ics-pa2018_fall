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
print_asm_0("in %dx, %al", "", 1);
	return 1;
}

make_instr_func(in_v) {
	OPERAND ax, dx;
	
	dx.type = OPR_REG;
	dx.data_size = 16; //%dx
	dx.addr = 2;
	operand_read(&dx); //get %dx

	ax.type = OPR_REG;
	ax.data_size = data_size; //%eax/%ax
	ax.addr = 0;
	ax.val = pio_read(dx.val, data_size / 8); //Input byte from port DX into %eax/%ax
	operand_write(&ax);
if(data_size == 16) print_asm_0("in %dx, %ax", "", 1);
else print_asm_0("in %dx, %eax", "", 1);
	return 1;
}
