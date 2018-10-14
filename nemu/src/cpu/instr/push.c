#include "cpu/instr.h"

make_instr_func(__push_r_v) { //0x50-0x57
	OPERAND r, esp;

	r.type = OPR_REG;
	r.data_size = data_size;
	r.addr = opcode & 0x7;

	esp.type = OPR_REG;
	esp.data_size = data_size;
	esp.addr = 4; //esp = grp[4]

	operand_read(&r); 
//printf("r.val:%x\n",r.val);
	operand_read(&esp); 
//printf("esp.val:%x\n",esp.val);
	esp.val = alu_sub(0x4, esp.val, data_size); //esp -= 4
	operand_write(&esp);
//printf("esp.val:%x\n",esp.val);

	r.type = OPR_MEM; //movl (esp), r
	r.addr = esp.val;
	operand_write(&r);
print_asm_1("push", "", 1, &r);
	return 1;
}
