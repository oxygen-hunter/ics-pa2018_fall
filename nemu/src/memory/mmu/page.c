#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	uint32_t dir = laddr >> 22; // page dirctory index. high 10 bit
	uint32_t page = laddr << 10 >> 22; // page table index, mid 10 bit
	uint32_t offset = laddr << 22 >> 22; // page frame index, low 12 bit
	
	uint32_t PDE_start = cpu.cr3.pdtr + dir; // page directory start here. physical addr
	uint32_t PTE_start = PDE_start + dir; //page table start here.
	uint32_t 
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
