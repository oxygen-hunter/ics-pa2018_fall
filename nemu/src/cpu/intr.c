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
	

	// Find the IDT entry using 'intr_no'
	GateDesc gatedesc;
	laddr_t IDT_start = cpu.idtr.base + 4 * intr_no; // idt start here. laddr
	gatedesc.val = laddr_read(IDT_start, 8); // read gate descripter' val

	// Clear IF if it is an interrupt
	if(interrupt)
		cpu.eflags.IF = 0;

	// Set EIP to the entry of the interrut handler
	cpu.eip = gatedesc.
#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
