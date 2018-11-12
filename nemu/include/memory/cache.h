#include "nemu.h"

#define CACHE_BLOCK_SIZE 64
#define CACHELINE_NUM 1024

struct CacheLine {
	bool valid; //1 when CacheLine is valid, 0 when CacheLine is invalid
	uint32_t sign; //to sign which if this cache matches address
	uint8_t data[CACHE_BLOCK_SIZE]; //data area who has 64 B
}

//clear all valid bit
void init_cache(); 

//read cache
uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache);
