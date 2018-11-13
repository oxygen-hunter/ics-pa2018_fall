#include "nemu.h"
#include "memory/cache.h"

#define CACHE_BLOCK_SIZE 64
#define CACHELINE_NUM 1024
#define c 10
#define q 8
#define s 2
#define CACHEGROUP_NUM (1 << q)
#define CACHEGROUP_SIZE (1 << s)

CacheLine cache[CACHELINE_NUM]; //64KB Cache

void init_cache() {
	memset(cache, 0, sizeof(cache));
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
	uint32_t tag = paddr >> (32 - c);
	uint32_t group_index = ((paddr << (32 - c)) >> (32 - q)) % CACHEGROUP_NUM;
	uint32_t gaddr = paddr & (CACHEGROUP_SIZE - 1);

	uint32_t group_start = group_index * CACHEGROUP_SIZE;
	bool group_full = false;
	for(int i = group_start; i < CACHEGROUP_SIZE; i ++) {
		if(cache[i].tag == tag) {
			if(cache[i].valid == 1) {
				return
			}
			else {

			}
			break;
		}
	}
}





