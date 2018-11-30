#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	uint32_t dir = laddr >> 22; // page dirctory index. high 10 bit
	uint32_t page = laddr << 10 >> 22; // page table index, mid 10 bit
	uint32_t offset = laddr << 20 >> 20; // page frame index, low 12 bit
	
	paddr_t PDE_start = cpu.cr3.pdbr + 4 * dir; // page directory start here. physical addr
	PDE pde;
	pde.val = paddr_read(PDE_start, 4); // read PDE
	assert(pde.present == 1);

	paddr_t PTE_start = pde.page_frame + 8 * page; // page table start here.
	PTE pte;
	pte.val = paddr_read(PTE_start, 4); // read PTE
	assert(pte.present == 1);

	paddr_t paddr = pte.page_frame + 8 * offset; // physical addr.
	return paddr;
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
