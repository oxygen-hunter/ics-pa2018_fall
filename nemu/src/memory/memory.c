#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "memory/cache.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>

extern CacheLine cache[1024]; //64KB Cache
uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data) {
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
#ifdef CACHE_ENABLED
	if(is_mmio(paddr) == -1)
		ret = cache_read(paddr, len, cache);
	else {
		int map_NO = is_mmio(paddr);
		ret = mmio_read(paddr, len, map_NO);
	}
#else
	if(is_mmio(paddr) == -1)
		ret = hw_mem_read(paddr, len);
	else {
		int map_NO = is_mmio(paddr);
		ret = mmio_read(paddr, len, map_NO);
	}
#endif
	return ret;
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data) {
#ifdef CACHE_ENABLED
	if(is_mmio(paddr) == -1)
		cache_write(paddr, len, data, cache);
	else {
		int map_NO = is_mmio(paddr);
		mmio_write(paddr, len, data, map_NO);
	}
#else
	if(is_mmio(paddr) == -1)
		hw_mem_write(paddr, len, data);
	else {
		int map_NO = is_mmio(paddr);
		mmio_write(paddr, len, data, map_NO);
	}
#endif
}


uint32_t laddr_read(laddr_t laddr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	if(cpu.cr0.pe == 1 && cpu.cr0.pg == 1) {
		if(cross_page(laddr, len)) {
			/* TODO this is a special case, you can handle it later*/

			/*uint32_t low_len = (((laddr >> 12) + 1) << 12) - laddr;
			uint32_t high_len = len - low_len;

			paddr_t paddr1 = page_translate(laddr); // read len bytes, low low_len bytes is useful
			uint32_t low = paddr_read(paddr1, len);

			paddr_t paddr2 = page_translate(((laddr >> 12) + 1) << 12); // read len bytes, low high_len bytes is useful
			uint32_t high = paddr_read(paddr2, len);

			uint32_t low_useful = 0;
			uint32_t high_useful = 0;
			uint32_t data;
			switch(len) {
				case 1: printf("when cross page, len shouldn't be 1!\n");assert(0); break; //len 1 won't cross page
				case 2: 
						if(low_len == 1 && high_len == 1) { // 1:1
							low_useful = low & 0xFF;
							high_useful = high & 0xFF;
							data = (high_useful << 8) + low_useful;
						}
						else {
							printf("wrong low_len or high_len\n");
							printf("low_len: 0x%x, high_len: 0x%x", low_len, high_len);
							assert(0);
						}
						break;				
				case 4: 
						if(low_len == 1 && high_len == 3) { // 1:3
							low_useful = low & 0xFF;
							high_useful = high & 0xFFFFFF;
							data = (high_useful << 8) + low_useful;
						}
						else if(low_len == 2 && high_len == 2) { // 2:2
							low_useful = low & 0xFFFF;
							high_useful = high & 0xFFFF;
							data = (high_useful << 16) + low_useful;
						}
						else if(low_len == 3 && high_len == 1) { // 3:1
							low_useful = low & 0xFFFFFF;
							high_useful = high & 0xFF;
							data = (high_useful << 24) + low_useful;
						}
						else {
							printf("wrong low_len or high_len\n");
							printf("low_len: 0x%x, high_len: 0x%x", low_len, high_len);
							assert(0);
						}
						break;
				default: assert(0); break;// never reach here
			}
			return data;*/
			
			
			

			
			
			uint32_t data = 0;
			if(len == 1) {
				printf("when cross page, len shouldn't be 1!\n");
				assert(0);
			}
			else if(len == 2) {
				paddr_t paddr1 = page_translate(laddr);
				paddr_t paddr2 = page_translate(laddr + 8);
				uint32_t data1 = paddr_read(paddr1, 1);
				uint32_t data2 = paddr_read(paddr2, 1);
				data = (data2 << 8) + data1;
			}
			else if(len == 4) {
				paddr_t paddr1 = page_translate(laddr);
				paddr_t paddr2 = page_translate(laddr + 8);
				paddr_t paddr3 = page_translate(laddr + 16);
				paddr_t paddr4 = page_translate(laddr + 24);
				uint32_t data1 = paddr_read(paddr1, 1);
				uint32_t data2 = paddr_read(paddr2, 1);
				uint32_t data3 = paddr_read(paddr3, 1);
				uint32_t data4 = paddr_read(paddr4, 1);
				data = (data4 << 24) + (data3 << 16) + (data2 << 8) + data1;
			}
			return data;

		} else {
			paddr_t paddr = page_translate(laddr);
			return paddr_read(paddr, len);
		}
	}
	else {
		return paddr_read(laddr, len);
	}
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	if(cpu.cr0.pe == 1 && cpu.cr0.pg == 1) {
		if(cross_page(laddr, len)) {
			/* TODO this is a special case, you can handle it later*/	
			
		/*	uint32_t data1 = data & 0xFF;
			uint32_t data2 = (data >> 8) & 0xFF;
			uint32_t data3 = (data >> 16) & 0xFF;
			uint32_t data4 = (data >> 24) & 0xFF;

			if(len == 1) {
				printf("when cross page, len shouldn't be 1!\n");
				assert(0);
			}
			else if(len == 2) {
				paddr_t paddr1 = page_translate(laddr);
				paddr_t paddr2 = page_translate(laddr + 8);
				paddr_write(paddr1, 1, data1);
				paddr_write(paddr2, 1, data2);
			}
			else if(len == 4) {
				paddr_t paddr1 = page_translate(laddr);
				paddr_t paddr2 = page_translate(laddr + 8);
				paddr_t paddr3 = page_translate(laddr + 16);
				paddr_t paddr4 = page_translate(laddr + 24);
				paddr_write(paddr1, 1, data1);
				paddr_write(paddr2, 1, data2);
				paddr_write(paddr3, 1, data3);
				paddr_write(paddr4, 1, data4);
			}*/
			paddr_t paddr = page_translate(laddr);
			paddr_write(paddr, len, data);
		} else {
			paddr_t paddr = page_translate(laddr);
			paddr_write(paddr, len, data);
		}
	}
	else {
		paddr_write(laddr, len, data);
	}
}


uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	return laddr_read(vaddr, len);
#else
	uint32_t laddr = vaddr;
	if(cpu.cr0.pe == 1) {
		laddr = segment_translate(vaddr, sreg);
	}
	return laddr_read(laddr, len);
#endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data) {
if(len != 1 && len != 2 && len != 4) printf("\nvaddr_write: len error: len = %d\n", (int)len);
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	laddr_write(vaddr, len, data);
#else
	uint32_t laddr = vaddr;
	if(cpu.cr0.pe == 1) {
		laddr = segment_translate(vaddr, sreg);
	}
//printf("\nvaddr_write: laddr:%x\n", laddr);
	laddr_write(laddr, len, data);
#endif
}

void init_mem() {
	// clear the memory on initiation
	memset(hw_mem, 0, MEM_SIZE_B);
#ifdef CACHE_ENABLED
	init_cache();
#endif

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t * get_mem_addr() {
	return hw_mem;
}

// 2018-12-19 revise for pa-2-3
// when doing pa-2-3, i made a mistake here, because that time 
// i don't know the difference between vaddr-laddr-paddr-hwaddr
// at that time, '(nemu) x 0x8048000' will cause segmentation fault because seg-page function is OFF.
// so i thought when i use command `(nemu) x [addr]', i should make sure addr is [0,128MB]
// now this check may take a break. xD
bool addr_is_valid(vaddr_t addr) {
	//return addr < MEM_SIZE_B; // pa-2-3's history problem
	return true; // pa-4-1's revise
}


bool cross_page(laddr_t laddr, uint32_t len) {
	/*laddr_t high_20_now = laddr >> 12;
	laddr_t high_20_nxt = (laddr + len - 1) >> 12;
	return (high_20_nxt == (high_20_now + 1));*/
	return false;
}




