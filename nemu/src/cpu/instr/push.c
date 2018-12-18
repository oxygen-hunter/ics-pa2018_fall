#include "cpu/instr.h"

static void instr_execute_1op() {
	operand_read(&opr_src);

if(opr_src.type == OPR_IMM && opr_src.data_size == 8) {
//printf("push imm8!!!\n");
	opr_src.val = sign_ext(opr_src.val, 8); //guide says "push imm8 needs to sign extend imm8"
	opr_src.data_size = 32; //to fit with its imm32 val
}
	cpu.esp -= opr_src.data_size / 8; //esp -= 4 or 2
	OPERAND mem;
	mem.type = OPR_MEM; //mov ?, (%esp)
	mem.data_size = opr_src.data_size;
	mem.val = opr_src.val;
	mem.addr = cpu.esp;
mem.sreg = SREG_DS;
	operand_write(&mem);
}

make_instr_impl_1op(push, r, v); //0x50-57
make_instr_impl_1op(push, i, b); //0x6a
make_instr_impl_1op(push, i, v); //0x68
make_instr_impl_1op(push, rm, v); //0xff[6]

/* stupid version...
make_instr_func(push_r_v) { //0x50-0x57
	OPERAND r, mem;

	r.type = OPR_REG;
	r.data_size = data_size;
	r.addr = opcode & 0x7;

	operand_read(&r); 

	cpu.esp -= data_size / 8; //esp -= 4 or esp -= 2

	mem.type = OPR_MEM; //mov r, (%esp)
	mem.data_size = data_size;
	mem.val = r.val;
	mem.addr = cpu.esp;
	operand_write(&mem);
//printf("push's:%x\n", mem.val);
//printf("after push's esp:%x\n", cpu.esp);
print_asm_1("push", data_size == 8 ? "b" : (data_size == 16 ? "w" : "l"), 1, &r);
	return 1;
}*/

make_instr_func(pusha) { //0x60
	OPERAND r, temp, mem;
	
	r.type = temp.type = OPR_REG;
	r.data_size = temp.data_size = data_size;
	r.addr = 0;
	temp.addr = 4; //temp = old esp

	mem.type = OPR_MEM;
	mem.data_size = data_size;
mem.sreg = SREG_DS;
	operand_read(&temp); //store old esp/sp

	for(; r.addr < 8; r.addr++) { //ax, cx, dx, bx, sp, bp, si, di
		if(r.addr == 4) //old sp
			r = temp;
		else {
			operand_read(&r);
		}
		cpu.esp -= data_size / 8; //esp -= 4; or esp -= 2 
		mem.val = r.val; //mov r, (%esp)
		mem.addr = cpu.esp;
		operand_write(&mem); 
	}
	
print_asm_0("pusha", "", 1);
	return 1;
}










