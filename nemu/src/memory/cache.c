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
	uint32_t group_index = ((paddr << 19) >> 25) % CACHEGROUP_NUM; //which group, medium 7 bit
	uint32_t baddr = paddr & 127; //low 6 bit

	uint32_t group_start = group_index * CACHEGROUP_SIZE; //group start at here
	bool group_full = false; //if group is full
	
	uint32_t result = 0; //the memory i want to read
	int i = group_start;
	for(; i < CACHEGROUP_SIZE; i ++) {
		if(cache[i].tag == tag) { //hit
			if(cache[i].valid == 1) { //hit, and valid, read it from cache
				
			}
			else { //hit, but invalid, copy from disk to cache, then read it 

			}
			break;
		}
	}
	if(i == CACHEGROUP_SIZE) { //can't hit
		group_full = true;
		
	}
}





