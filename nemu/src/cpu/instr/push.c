#include "cpu/instr.h"

make_instr_func(push_r_v) { //0x50-0x57
	OPERAND r, mem;

	r.type = OPR_REG;
	r.data_size = data_size;
	r.addr = opcode & 0x7;

	operand_read(&r); 

	cpu.esp -= data_size; //esp -= 4 or esp -= 2

	mem.type = OPR_MEM; //mov (esp), r
	mem.data_size = data_size;
	mem.val = r.val;
	mem.addr = cpu.esp;
	operand_write(&mem);
print_asm_1("push", "l", 1, &r);
	return 1;
}

make_instr_func(pusha) { //0x60
	OPERAND r, temp, mem;
	
	r.type = temp.type = OPR_REG;
	r.data_size = temp.data_size = data_size;
	r.addr = 0;
	temp.addr = 4;

	mem.type = OPR_MEM;
	mem.data_size = data_size;

	operand_read(&temp); //store old esp/sp

	for(; r.addr < 8; r.addr++) { //ax, ec, dx, bx, sp, bp, si, di
		if(r.addr == 4) //old sp
			r = temp;
		else {
			operand_read(&r);
		}
		cpu.esp -= data_size; //esp -= 4; or esp -= 2 
		mem.val = r.val; //mov r, (%esp)
		mem.addr = cpu.esp;
		operand_write(&mem); 
	}
	
print_asm_0("pusha", "", 1);
	return 1;
}










