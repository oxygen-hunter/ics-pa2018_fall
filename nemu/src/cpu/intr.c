#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"


void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);

	// Trigger an exception/interrrupt with 'intr_no'
	// 'intr_no' is the index to the IDT
	

	// Push EFLAGS, CS and EIP
	cpu.esp = cpu.esp - 4;
	OPERAND EFLAGS, CS, EIP;
	EFLAGS.val = cpu.eflags.val

	// Find the IDT entry using 'intr_no'
	GateDesc gatedesc; // sizeof(GateDesc) == 8
	laddr_t IDT_start = cpu.idtr.base + 8 * intr_no; // idt start here. laddr
	gatedesc.val = laddr_read(IDT_start, 8); // read gate descripter' val

	// Clear IF if it is an interrupt
	if(gatedesc.type == 0xe) // gatedesc's type: 1110 means interrupt, 1111 means trap
		cpu.eflags.IF = 0;

	// Set EIP to the entry of the interrut handler
	cpu.eip = (gatedesc.offset_31_16 << 16) + gatedesc.offset_15_0;
#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
