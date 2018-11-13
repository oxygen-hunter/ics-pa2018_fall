//#include "nemu.h"

#define CACHE_BLOCK_SIZE 64
#define CACHELINE_NUM 1024
#define CACHEGROUP_NUM 128
#define CACHEGROUP_SIZE 8

struct CacheLine;

struct CacheLine {
	bool valid; //1 when CacheLine is valid, 0 when CacheLine is invalid
	uint32_t tag; //to sign which if this cache matches address
	uint8_t data[CACHE_BLOCK_SIZE]; //data area who has 64 B
};

//clear all valid bit
void init_cache(); 

//read cache
uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache);

//write cache
void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache);
