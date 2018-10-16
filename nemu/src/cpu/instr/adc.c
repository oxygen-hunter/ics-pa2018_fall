#include "cpu/instr.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val = alu_adc(opr_src.val, opr_dest.val, data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(adc, r, rm, b); //0x10
make_instr_impl_2op(adc, r, rm, v); //0x11
make_instr_impl_2op(adc, rm, r, b); //0x12
make_instr_impl_2op(adc, rm, r, v); //0x13
make_instr_impl_2op(adc, i, a, b); //0x14
make_instr_impl_2op(adc, i, a, v); //0x15

make_instr_impl_2op(adc, i, rm, bv); //0x83[2]
make_instr_impl_2op(adc, i, rm, v);


/* stupid version...
make_instr_func(__adc_r2rm_b) { //0x00
	OPERAND r, rm;

	r.data_size = 8;
	rm.data_size = 8;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&r);
	//rm.val += r.val;
	rm.val = alu_adc(r.val, rm.val, 8);
	operand_write(&rm);

	return len;
}

make_instr_func(__adc_r2rm_v) { //0x01
	OPERAND r, rm;

	r.data_size = data_size;
	rm.data_size = data_size;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&r);
	//rm.val += r.val;
	rm.val = alu_adc(r.val, rm.val, data_size);
	operand_write(&rm);

	return len;
}

make_instr_func(__adc_rm2r_b) { //0x02
	OPERAND rm, r;

	r.data_size = 8;
	rm.data_size = 8;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&rm);
	//r.val += rm.val;
	r.val = alu_adc(rm.val, r.val, 8);
	operand_write(&r);

	return len;
}

make_instr_func(__adc_rm2r_v) { //0x03
	OPERAND rm, r;

	r.data_size = data_size;
	rm.data_size = data_size;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);

	operand_read(&rm);
	//r.val += rm.val;
	r.val = alu_adc(rm.val, r.val, data_size);
	operand_write(&r);

	return len;
}
make_instr_func(__adc_i2a_b) { //0x04
	OPERAND imm, a;
	
	int len = 1; //opcode length = 1
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.adcr = eip + len;

	a.type = OPR_REG;
	a.data_size = 8;
	a.adcr = 0; //AL
	
	operand_read(&a); //get AL
	operand_read(&imm); //get imm
	//a.val += imm.val;
	a.val = alu_adc(imm.val, a.val, 8);
	operand_write(&a);
	
	return len + 1; //opcode + imm_b
}
make_instr_func(__adc_i2a_v) { //0x05
	OPERAND imm, a;
	
	int len = 1; //opcode length = 1
	imm.type = OPR_IMM;
	imm.data_size = data_size;
	imm.adcr = eip + len;

	a.type = OPR_REG;
	a.data_size = data_size;
	a.adcr = 0; //EAX
	
	operand_read(&a); //get AL
	operand_read(&imm); //get imm
	//a.val += imm.val;
	a.val = alu_adc(imm.val, a.val, data_size);
	operand_write(&a);
	
	return len + data_size/8; //opcode + imm_v
}

make_instr_func(__adc_i2rm_bv) { //0x83[0]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.adcr = eip + len;

	operand_read(&imm); //get imm
	//rm.val += imm.val;
	rm.val = alu_adc(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("adc", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}

make_instr_func(__adc_i2rm_bv) { //0x83[2]
	OPERAND imm, rm;
	
	int len = 1; //opcode len = 1
	rm.data_size = data_size;
	len += modrm_rm(eip + 1, &rm);
	
	imm.type = OPR_IMM;
	imm.data_size = 8;
	imm.adcr = eip + len;

	operand_read(&imm); //get imm
	//rm.val += imm.val + cpu.CF;
	rm.val = alu_adc(imm.val, rm.val, data_size);
	operand_write(&rm);
print_asm_2("adc", "bv", len + 1, &imm, &rm);
	return len + 1; //opcode + modrm + imm_b
}*/








