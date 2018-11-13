#include "nemu.h"
#include "memory/cache.h"

#define CACHE_BLOCK_SIZE 64
#define CACHELINE_NUM 1024
#define c 10
#define q 8
#define s 2
#define b 6
#define CACHEGROUP_NUM 128
#define CACHEGROUP_SIZE 8

CacheLine cache[CACHELINE_NUM]; //64KB Cache

void init_cache() {
	memset(cache, 0, sizeof(cache));
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
	uint32_t tag = paddr >> 13; //high 19 bit
	uint32_t group_index = ((paddr << 19) >> 25) % 128; //which group, medium 7 bit
	uint32_t baddr = paddr & 127; //low 6 bit

	uint32_t group_start = group_index * 8; //group start at here
	bool group_full = true; //if group is full
	
	uint32_t result = 0; //the memory i want to read
	int i = group_start;
	for(; i < 8; i ++) { //search all lines of the group
		if(cache[i].tag == tag) { //hit
			if(cache[i].valid == 1) { //hit, and valid, read it from cache
				if(baddr <= 64 - len) { //directly read from cache data
					memcpy(&result, cache[i].data + baddr, len);
				}
				else { //cross cacheline to read data
					uint32_t len_this = 64 - baddr; //length in this line
					uint32_t len_next = len - len_this; //length in next line
					uint32_t val_this = 0; //val in this line
					uint32_t val_next = 0; //val in next line
					memcpy(&val_this, cache[i].data + baddr, len_this); //read val in this line
					val_next = cache_read(paddr + len_this, len_next, cache); //read val in next line
					result = (val_this << (32 - len_this)) | val_next; //connect val_this with val_next
				}
			}
			else { //hit, but invalid, copy from memory to cache, then read it 
				memcpy(cache[i].data, hw_mem + paddr, 64);
				result = cache_read(paddr, len, cache);
			}
			break;
		}
	}
	bool group_blank = false;
	int blank_line_index = -1;
	if(i == CACHEGROUP_SIZE) { //can't hit
		for(int i = group_start; i < 8; i ++) {
			if(cache[i].valid == 0) {
				group_blank = true;
				blank_line_index = i;
				break;
			}
		}
		if(group_blank == true) { //cache group has a blank line
			memcpy(cache[i].data, hw_mem + ((paddr >> 6) << 6), 64);
		}
		else {

		}
	
	}
	return result;
}





