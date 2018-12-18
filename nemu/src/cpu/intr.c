#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"


void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	// Trigger an exception/interrrupt with 'intr_no'
	// 'intr_no' is the index to the IDT
	
	// Push EFLAGS, CS and EIP	
	OPERAND EFLAGS, CS, EIP;
	EFLAGS.data_size = 4; 
	EFLAGS.val = cpu.eflags.val; 
	EFLAGS.type = OPR_MEM; 
	EFLAGS.sreg = SREG_DS;
	
	CS.data_size = 4;
	CS.val = cpu.cs.val; 
	CS.type = OPR_MEM; 
	CS.sreg = SREG_DS;
	
	EIP.data_size = 4;
	EIP.val = cpu.eip; 
	EIP.type = OPR_MEM; 
	EIP.sreg = SREG_DS;

	cpu.esp = cpu.esp - 4; // push EFLAGS, next lines's order mustn't change
	EFLAGS.addr = cpu.esp;
	operand_write(&EFLAGS);

	cpu.esp = cpu.esp - 4; // push CS's visible part
	CS.addr = cpu.esp;
	operand_write(&CS);

	cpu.esp = cpu.esp - 4; // push EIP
	EIP.addr = cpu.esp;
	operand_write(&EIP);

	// Find the IDT entry using 'intr_no'
	GateDesc gatedesc; // sizeof(GateDesc) == 8
	laddr_t IDT_start = cpu.idtr.base + 8 * intr_no; // idt start here. laddr
	gatedesc.val[0] = laddr_read(IDT_start, 4); // read gate descripter' val
	gatedesc.val[1] = laddr_read(IDT_start + 4, 4);

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
