#include "cpu/instr.h"
#include "cpu/intr.h"

make_instr_func(int_) {
	OPERAND intr_no;
	
	intr_no.type = OPR_IMM;
	intr_no.data_size = 8; //uint8_t
	intr_no.addr = eip + 1;
	
	operand_read(&intr_no);

print_asm_1("int", "", 1, &intr_no);
	
	raise_sw_intr(intr_no.val); // awake os	
	return 0;
}
