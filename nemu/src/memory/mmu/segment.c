#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg) {
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */

	uint32_t base = cpu.segReg[sreg].base;
//printf("\nseg_trans: base:%x, offset:%x, base + offset:%x, sreg:%x\n", base, offset, base+offset, sreg);	
	return base + offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg) {
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
printf("\nload_sreg: sreg:%x\n", sreg);
	uint32_t index = cpu.segReg[sreg].index; //which SegmentDescriptor
printf("\nload_sreg: index:%x\n", index);
	laddr_t segTable = (laddr_t) cpu.gdtr.base; //segTable start addr, is a laddr

	SegDesc segdesc;
	segdesc.val[0] = laddr_read(segTable + 8 * index, 4);
	segdesc.val[1] = laddr_read(segTable + 8 * index + 4, 4);
printf("\nload_sreg: segTable:%x\n", (uint32_t)segTable);

	//assert(segdesc.base_15_0 == 0x0); //check SegmentDescriptor
	//assert(segdesc.limit_15_0 == 0xffff);
	//assert(segdesc.granularity == 0x1);
//printf("load_sreg: sizeof():%x\n", sizeof(segdesc));
//printf("load_sreg: segTable[index].val[0]:%x, val[1]:%x\n", segTable[index].val[0], segTable[index].val[1]);
	cpu.segReg[sreg].base = segdesc.base_15_0; //load sreg's invisible part
	cpu.segReg[sreg].limit = segdesc.limit_15_0;
//printf("3\n");
}
