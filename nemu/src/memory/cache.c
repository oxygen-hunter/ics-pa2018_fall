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
	uint32_t tag = paddr >> 13;
	uint32_t group_index = ((paddr << 19) >> 25) % CACHEGROUP_NUM;
	uint32_t baddr = paddr & 127;

	uint32_t group_start = group_index * CACHEGROUP_SIZE;
	bool group_full = false;
	for(int i = group_start; i < CACHEGROUP_SIZE; i ++) {
		if(cache[i].tag == tag) {
			if(cache[i].valid == 1) {
				
			}
			else {

			}
			break;
		}
	}
}





