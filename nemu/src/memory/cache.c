#include "nemu.h"
#include "memory/cache.h"

CacheLine cache[CACHELINE_NUM]; //64KB Cache

void init_cache() {
	for(int i = 0; i < CACHELINE_NUM; i ++) {
		cache[i].valid = 0;
	}
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
	
}

