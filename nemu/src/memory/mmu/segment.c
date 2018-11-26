#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg) {
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	uint32_t base = cpu.segReg[sreg].base;
	return base + offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg) {
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	
	uint32_t index = cpu.segReg[sreg].index; //which SegmentDescriptor
	SegmentDescriptor* segTable = (SegmentDescriptor*) cpu.gdtr.base; //segTable start addr

	assert(segTable[index].base_15_0 == 0x0);
	assert(segTable[index].limit_15_0 == 0xffff);
	assert(segTable[index].granularity == 0x1);

	cpu.segReg[sreg].base = segTable[index].base_15_0; //load sreg's invisible part
	cpu.segReg[sreg].limit = segTable[index].limit_15_0;
}
