#include "cpu/instr.h"

make_instr_func(__push_r_v) { //0x50-0x57
	OPERAND r, esp;

	r.type = OPR_REG;
	r.data_size = data_size;
	r.addr = opcode & 0x7;

	esp.type = OPR_REG;
	esp.daya_size = data_size;
	esp.addr = 4;

	operand_read(&r);
	operand_read(&esp);
	esp.val = alu_sub(0x4, esp.val, data_size); //esp -= 4
	
	r.type = OPR_MEM; //movl r, (esp)
	r.addr = esp.val;
	
	operand_write(&esp);
	operand_write(&r);
	
}
