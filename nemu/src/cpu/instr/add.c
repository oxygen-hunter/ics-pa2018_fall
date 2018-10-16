#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
if(opr_src.data_size < opr_dest.data_size) opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
printf("src + dest: %x + %x\n", opr_src.val, opr_dest.val);
	opr_dest.val = alu_add(opr_src.val, opr_dest.val, data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(add, r, rm, b); //0x00
make_instr_impl_2op(add, r, rm, v); //0x01
make_instr_impl_2op(add, rm, r, b); //0x02
make_instr_impl_2op(add, rm, r, v); //0x03
make_instr_impl_2op(add, i, a, b); //0x04
make_instr_impl_2op(add, i, a, v); //0x05

make_instr_impl_2op(add, i, rm, bv); //0x83[0]
make_instr_impl_2op(add, i, rm, v);


/* stupid version...
make_instr_func(__add_r2rm_b) { //0x00
	OPERAND r, rm;

	r.data_size = 8;
	rm.data_size = 8;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&r);
	//rm.val += r.val;
	rm.val = alu_add(r.val, rm.val, 8);
	operand_write(&rm);

	return len;
}

make_instr_func(__add_r2rm_v) { //0x01
	OPERAND r, rm;

	r.data_size = data_size;
	rm.data_size = data_size;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&r);
	//rm.val += r.val;
	rm.val = alu_add(r.val, rm.val, data_size);
	operand_write(&rm);

	return len;
}

make_instr_func(__add_rm2r_b) { //0x02
	OPERAND rm, r;

	r.data_size = 8;
	rm.data_size = 8;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&rm);
	//r.val += rm.val;
	r.val = alu_add(rm.val, r.val, 8);
	operand_write(&r);

	return len;
}

make_instr_func(__add_rm2r_v) { //0x03
	OPERAND rm, r;

	r.data_size = data_size;
	rm.data_size = data_size;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&rm);
	//r.val += rm.val;
	r.val = alu_add(rm.val, r.val, data_size);
	operand_write(&r);

	return len;
}
make_instr_func(__add_i2a_b) { //0x04
	OPERAND imm, a;
	
	int len = 1; //opcode length = 1
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	a.type = OPR_REG;
	a.data_size = 8;
	a.addr = 0; //AL
	
	operand_read(&a); //get AL
	operand_read(&imm); //get imm
	//a.val += imm.val;
	a.val = alu_add(imm.val, a.val, 8);
	operand_write(&a);
	
	return len + 1; //opcode + imm_b
}
make_instr_func(__add_i2a_v) { //0x05
	OPERAND imm, a;
	
	int len = 1; //opcode length = 1
	imm.type = OPR_IMM;
	imm.data_size = data_size;
	imm.addr = eip + len;

	a.type = OPR_REG;
	a.data_size = data_size;
	a.addr = 0; //EAX
	
	operand_read(&a); //get AL
	operand_read(&imm); //get imm
	//a.val += imm.val;
	a.val = alu_add(imm.val, a.val, data_size);
	operand_write(&a);
	
	return len + data_size/8; //opcode + imm_v
}

make_instr_func(__add_i2rm_bv) { //0x83[0]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	operand_read(&imm); //get imm
	//rm.val += imm.val;
	rm.val = alu_add(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("add", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}

make_instr_func(__adc_i2rm_bv) { //0x83[2]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.addr = eip + len;

	operand_read(&imm); //get imm
	//rm.val += imm.val + cpu.CF;
	rm.val = alu_adc(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("adc", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}*/








