#include "nemu.h"
#include "memory/cache.h"

CacheLine cache[CACHELINE_NUM]; //64KB Cache

void init_cache() {
	memset(cache, 0, sizeof(cache));
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
	
}

