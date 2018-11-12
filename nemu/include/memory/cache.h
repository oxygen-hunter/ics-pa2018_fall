#include "nemu.h"

struct CacheLine {
	bool valid; //1 when CacheLine is valid, 0 when CacheLine is invalid
	uint32_t sign; //to sign which if this cache matches address
	uint8_t data[64]; //data area who has 64 B
}

//clear all valid bit
void init_cache(); 

//read cache
uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache);
