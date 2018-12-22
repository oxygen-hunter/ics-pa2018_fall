#include "cpu/instr.h"

make_instr_func(out_b) {
	OPERAND AL, DX;
	
	AL.type = OPR_REG;
	AL.data_size = 8;
	AL.addr = 0;
	
	DX.type = OPR_REG;
	DX.data_size = 16;
	DX.addr = 2;
	return 1;
}
