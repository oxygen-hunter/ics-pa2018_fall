#include "nemu.h"
#include "memory/cache.h"
#include "memory/memory.h"

CacheLine cache[1024]; //64KB Cache

void init_cache() {
	memset(cache, 0, sizeof(cache));
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
	uint32_t tag = paddr >> 13; //high 19 bit
	uint32_t group_index = (paddr << 19) >> 25; //which group, medium 7 bit
	uint32_t baddr = paddr & 0x3f; //low 6 bit
//printf("tag:0x%x, group_index:0x%x, baddr:0x%x\n",tag, group_index, baddr);
	uint32_t group_start = group_index * 8; //group start at here
	uint8_t flag = 0;
	uint32_t result = 0; //the memory i want to read
	int i = group_start;

	for(; i < group_start + 8; i ++) { //search all lines of the group
		if(cache[i].tag == tag) { //hit
			if(cache[i].valid == 1) { //hit, and valid, read it from cache
				if(baddr <= 64 - len) { //directly read from cache data
					/*uint32_t cc=0;
					uint32_t mm=0;
					memcpy(&cc, cache[i].data + baddr, len);
					memcpy(&mm, hw_mem + paddr, len);
					if(cc != mm) {
						printf("i:%d\n", i);
						printf("baddr:0x%x\n", baddr);
						printf("incache:%x, inmem:%x\n\n", cc, mm);
					memcpy(cache[i].data, hw_mem+((paddr >> 6) << 6), 64);
						//assert(0);
					}*/
					memcpy(&result, cache[i].data + baddr, len);
					//memcpy(&result, hw_mem + paddr, len);
				}
					
				else { //cross cacheline to read data
					/*uint32_t len_this = 64 - baddr; //length in this line
					uint32_t len_next = len - len_this; //length in next line
					uint32_t val_this = 0; //val in this line
					uint32_t val_next = 0; //val in next line
					memcpy(&val_this, cache[i].data + baddr, len_this); //read val in this line
					val_next = cache_read(paddr + len_this, len_next, cache); //read val in next line
					result = (val_next << (len_this * 8)) | val_this;*/
				 	memcpy(&result, hw_mem + paddr, len);
					//connect val_this with val_next, pay attention to little-edium
				}
			}
			else { //hit, but invalid, copy from memory to cache, then read it 
				memcpy(cache[i].data, hw_mem + ((paddr >> 6) << 6), 64);
				cache[i].valid = 1;
				cache[i].tag = tag;
				result = cache_read(paddr, len, cache);
				//memcpy(&result, hw_mem + paddr, len);
			}
			flag = 1;
			break;
		}
	}
	bool group_blank = false;
	int blank_line_index = -1;
	if(flag == 0) { //can't hit
		for(int j = group_start; j < group_start + 8; j ++) { // to test if any line is blank
			if(cache[j].valid == 0) {
				group_blank = true;
				blank_line_index = j;
				break;
			}
		}
		if(group_blank == true) { //cache group has a blank line
			memcpy(cache[blank_line_index].data, hw_mem + ((paddr >> 6) << 6), 64); //full this blank line
			cache[blank_line_index].valid = 1;
			cache[blank_line_index].tag = tag;
			result = cache_read(paddr, len, cache); //read cache
		}
		else { //cache group is full
			int random_num = group_start + 1; //to get a random number in [0:7]
			memcpy(cache[random_num].data, hw_mem + ((paddr >> 6) << 6), 64); //replace this line
			cache[random_num].valid = 1;
			cache[random_num].tag = tag;
			result = cache_read(paddr, len, cache); //read cache
			//memcpy(&result, hw_mem + paddr, len);
		}
	}
	return result;
}

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache) {
	;
}



