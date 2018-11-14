#include "nemu.h"
#include "memory/cache.h"
#include "memory/memory.h"

CacheLine cache[1024]; //64KB Cache

void init_cache() {
	//memset(cache, 0, sizeof(cache));
	for(int i=0;i<1024;i++)
		cache[i].valid=0;
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
printf("hw_mem:0x%x\n", (uint32_t)hw_mem);
printf("paddr:0x%x, len:0x%x\n", (uint32_t)paddr, (uint32_t)len);
	uint32_t tag = paddr >> 13; //high 19 bit
	uint32_t group_index = (paddr << 19) >> 25; //which group, medium 7 bit
	uint32_t baddr = paddr & 0x3f; //low 6 bit
printf("tag:0x%x, group_index:0x%x, baddr:0x%x\n",tag, group_index, baddr);
	uint32_t group_start = group_index * 8; //group start at here
	//bool group_full = true; //if group is full
	
	uint32_t result = 0; //the memory i want to read
	int i = group_start;
printf("group_start:%d\n", group_start);
	for(; i < group_start + 8; i ++) { //search all lines of the group
		if(cache[i].tag == tag) { //hit
printf("hit\n");
			if(cache[i].valid == 1) { //hit, and valid, read it from cache
printf("hit and valid\n");
				if(baddr <= 64 - len) { //directly read from cache data
printf("directly read from cache\n");
					//memcpy(&result, cache[i].data + baddr, len);
					memcpy(&result, hw_mem + paddr, len);
				}
				else { //cross cacheline to read data
printf("cross cacheline to reald\n");
					uint32_t len_this = 64 - baddr; //length in this line
					uint32_t len_next = len - len_this; //length in next line
					uint32_t val_this = 0; //val in this line
					uint32_t val_next = 0; //val in next line
					val_this=1;
					val_next=1;
					len_this=1;
					len_next=0;
					//memcpy(&val_this, cache[i].data + baddr, len_this); //read val in this line
					//val_next = cache_read(paddr + len_this, len_next, cache); //read val in next line
					//result = (val_next << (len_this * 8)) | val_this;
				 	memcpy(&result, hw_mem + paddr, len);
					//connect val_this with val_next, pay attention to little-edium
				}
			}
			else { //hit, but invalid, copy from memory to cache, then read it 
printf("hit but invalid\n");
				//memcpy(cache[i].data, hw_mem + ((paddr >> 6) << 6), 64);
				cache[i].valid = 1;
				cache[i].tag = tag;
				//result = cache_read(paddr, len, cache);
				memcpy(&result, hw_mem + paddr, len);
			}
			break;
		}
	}
	bool group_blank = false;
	int blank_line_index = 0;
	if(i == group_start + 8) { //can't hit
printf("can't hit\n");
		for(int j = group_start; j < group_start + 8; j ++) { // to test if any line is blank
			if(cache[j].valid == 0) {
				group_blank = true;
				blank_line_index = j;
				break;
			}
		}
		if(group_blank == true) { //cache group has a blank line
printf("group blank, at cacheline[%d]\n", blank_line_index);
printf("hw_mem:0x%x\n", (uint32_t)hw_mem);
printf("hw_mem+paddr >><<6:0x%x\n", (uint32_t)(hw_mem + ((paddr >> 6) << 6)));
			memcpy(cache[blank_line_index].data, hw_mem + ((paddr >> 6) << 6), 64); //full this blank line
printf("after memcpy\n");
			cache[blank_line_index].valid = 1;
			cache[blank_line_index].tag = tag;

			//result = cache_read(paddr, len, cache); //read cache
			memcpy(&result, hw_mem + paddr, len);
		}
		else { //cache group is full
printf("group[%d] is full\n", group_index);
			int random_num = group_start + 1; //to get a random number in [0:7]
			memcpy(cache[random_num].data, hw_mem + ((paddr >> 6) << 6), 64); //replace this line
			cache[random_num].valid = 1;
			cache[random_num].tag = tag;
			//result = cache_read(paddr, len, cache); //read cache
			memcpy(&result, hw_mem + paddr, len);
		}
	}
printf("result:0x%x\n\n", result);
	return result;
}





