#include "nemu.h"
#include "memory/cache.h"
#include "memory/memory.h"

CacheLine cache[CACHELINE_NUM]; //64KB Cache

void init_cache() {
	memset(cache, 0, sizeof(cache));
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
	uint32_t tag = paddr >> 13; //high 19 bit
	uint32_t group_index = (paddr << 19) >> 25; //which group, medium 7 bit
	uint32_t baddr = paddr & 0x3f; //low 6 bit
printf("tag:%d, group_index:%d, baddr:%d\n",tag, group_index, baddr);
	uint32_t group_start = group_index * 8; //group start at here
	//bool group_full = true; //if group is full
	
	uint32_t result = 0; //the memory i want to read
	int i = group_start;
	for(; i < 8; i ++) { //search all lines of the group
		if(cache[i].tag == tag) { //hit
			if(cache[i].valid == 1) { //hit, and valid, read it from cache
printf("hit and valid\n");
				if(baddr <= 64 - len) { //directly read from cache data
printf("directly read from cache\n");
					memcpy(&result, cache[i].data + baddr, len);
				}
				else { //cross cacheline to read data
printf("cross cacheline to read\n");
					uint32_t len_this = 64 - baddr; //length in this line
					uint32_t len_next = len - len_this; //length in next line
					uint32_t val_this = 0; //val in this line
					uint32_t val_next = 0; //val in next line
					memcpy(&val_this, cache[i].data + baddr, len_this); //read val in this line
					val_next = cache_read(paddr + len_this, len_next, cache); //read val in next line
					result = (val_next << len_this) | val_this; 
					//connect val_this with val_next, pay attention to little-edium
				}
			}
			else { //hit, but invalid, copy from memory to cache, then read it 
printf("hit but invalid\n");
				memcpy(cache[i].data, hw_mem + ((paddr >> 6) << 6), 64);
				cache[i].valid = 1;
				cache[i].tag = tag;
				result = cache_read(paddr, len, cache);
			}
			break;
		}
	}
	bool group_blank = false;
	int blank_line_index = -1;
	if(i == 8) { //can't hit
printf("can't hit\n");
		for(int j = group_start; j < 8; j ++) { // to test if any line is blank
			if(cache[j].valid == 0) {
				group_blank = true;
				blank_line_index = j;
				break;
			}
		}
		if(group_blank == true) { //cache group has a blank line
printf("group blank, at cache[%d][%d]\n", group_index, blank_line_index);
			memcpy(cache[blank_line_index].data, hw_mem + ((paddr >> 6) << 6), 64); //full this blank line
			cache[blank_line_index].valid = 1;
			cache[blank_line_index].tag = tag;
			result = cache_read(paddr, len, cache); //read cache
		}
		else { //cache group is full
printf("group[%d] is full\n", group_index);
			int random_num = 1; //to get a random number in [0:7]
			memcpy(cache[random_num].data, hw_mem + ((paddr >> 6) << 6), 64); //replace this line
			cache[random_num].valid = 1;
			cache[random_num].tag = tag;
			result = cache_read(paddr, len, cache); //read cache
		}
	}
printf("paddr:%x, len:%x, result:%x\n\n", (uint32_t)paddr, (uint32_t)len, result);
	return result;
}





