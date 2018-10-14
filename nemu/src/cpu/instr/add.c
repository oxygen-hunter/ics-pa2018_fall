#include "cpu/instr.h"

make_instr_func(__add_r2rm_b) { //0x00
	OPERAND r, rm;

	r.data_size = 8;
	rm.data_size = 8;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);
	operand_read(&r);
	rm.val += r.val;
	operand_write(&rm);
	return len;
}

make_instr_func(__add_r2rm_v); //0x01
make_instr_func(__add_rm2r_b); //0x02
make_instr_func(__add_rm2r_v); //0x03
