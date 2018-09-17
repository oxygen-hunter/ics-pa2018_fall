#include "cpu/cpu.h"

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest + src;

	set_CF_add(res, src, data_size);
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_add(res, src, dest, data_size);

	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest + src + cpu.eflags.CF;
	
	set_CF_adc(res, src, data_size);
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_adc(res, src, dest, data_size);

	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}


uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest - src;

	set_CF_sub(src, dest, data_size);
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_sub(res, src, dest, data_size);

	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest - src - cpu.eflags.CF;

	set_CF_sbb(src, dest, data_size);
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_sbb(res, src, dest, data_size);

	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	uint64_t res = 0;
	res = (uint64_t)(dest * src);
		
	set_CF_OF_mul(src, dest, data_size);
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	
	return res&(0xFFFFFFFFFFFFFFFF >> (64 - 2*data_size));
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest) {
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest & src;

	cpu.eflags.CF = 0;
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	cpu.eflags.OF = 0;

	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest ^ src;

	cpu.eflags.CF = 0;
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	cpu.eflags.OF = 0;

	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest | src;

	cpu.eflags.CF = 0;
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	cpu.eflags.OF = 0;

	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest << src;

	set_CF_shl(dest, src, data_size);
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	//set_OF_shl; we don't simulate OF

	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	uint32_t res = 0;
	uint32_t dest_low = dest&(0xFFFFFFFF >> (32 - data_size));
	res = dest_low >> src;

	set_CF_shr(dest, src, data_size);
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	//set_OF_shl; we don't simulate OF
	return res;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);	
#else
	uint32_t res = 0;
	uint32_t dest_low = dest&(0xFFFFFFFF >> (32 - data_size));
	dest_low = sign_ext(dest_low, data_size);
	res = dest_low >> src;

	set_CF_shr(dest, src, data_size);
	set_PF(res);
	//set_AF(); we don't simulate AF
	set_ZF(res, data_size);
	set_SF(res, data_size);
	//set_OF_shl; we don't simulate OF
	return res&(0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	return alu_shl(src, dest, data_size);
#endif
}


// add
void set_CF_add(uint32_t res, uint32_t src, size_t data_size) {
	/*CF = 1 when res < src*/
	res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	cpu.eflags.CF = res < src;
}

void set_PF(uint32_t res) {
	/*count the number of 1 in low 8 bits of res*/
	/*PF = 1 when the number is odd*/
	int num_of_1 = 0;
	for(int i = 0; i < 8; i++){
		if((res&1) == 1)
			num_of_1++;
		res >>= 1;
	}
	cpu.eflags.PF = ((num_of_1%2 == 0)? 1:0);
}

void set_ZF(uint32_t res, size_t data_size) {
	/*ZF = 1 when data_size bits of res == 0*/
	res = res&(0xFFFFFFFF >> (32 - data_size));
	cpu.eflags.ZF = (res == 0);
}

void set_SF(uint32_t res, size_t data_size) {
	/*SF = 1 when res[data_size - 1] == 1*/
	/*my version*/
	//uint32_t judge = 1 << (data_size - 1);
	//cpu.eflags.SF = ((judge&res) == 0)? 0:1;
	/*pdf version*/
	res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
	cpu.eflags.SF = sign(res);
}

void set_OF_add(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
	/*OF = 1 when pos + pos = neg Or neg + neg = pos*/
	switch(data_size) {
		case 8:
				res = sign_ext(res & 0xFF, 8);
				src = sign_ext(src & 0xFF, 8);
				dest = sign_ext(dest & 0xFF, 8);
				break;
		case 16:
				res = sign_ext(res & 0xFFFF, 16);
				src = sign_ext(src & 0xFFFF, 16);
				dest = sign_ext(dest & 0xFFFF, 16);
				break;
		default: break;
	}
	if(sign(src)==sign(dest)) {
		if(sign(src) != sign(res))
			cpu.eflags.OF = 1;
		else
			cpu.eflags.OF = 0;
	}else {
		cpu.eflags.OF = 0;
	}
}

// adc
void set_CF_adc(uint32_t res, uint32_t src, size_t data_size) {
	/*CF = 1 when 1.old CF == 0 And ext_res < ext_src*/
	/*			  2.old CF == 1 And ext_res <= ext_src*/
	res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	if(cpu.eflags.CF == 1)
		cpu.eflags.CF = (res <= src);
	else
		cpu.eflags.CF = res < src;
}

void set_OF_adc(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
	/*same as add*/
	set_OF_add(res, src, dest, data_size);
}

// sub
void set_CF_sub(uint32_t src, uint32_t dest, size_t data_size) {
	/*CF = 1 when ext_dest < ext_src*/
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
	cpu.eflags.CF = dest < src;
}

void set_OF_sub(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
	/*CF = 1 when 1.neg - pos = pos*/
	/*			  2.pos - neg = neg*/
	switch(data_size) {
		case 8:
				res = sign_ext(res & 0xFF, 8);
				src = sign_ext(src & 0xFF, 8);
				dest = sign_ext(dest & 0xFF, 8);
				break;
		case 16:
				res = sign_ext(res & 0xFFFF, 16);
				src = sign_ext(src & 0xFFFF, 16);
				dest = sign_ext(dest & 0xFFFF, 16);
				break;
		default: break;
	}
	if(sign(src)!=sign(dest)) {
		if(sign(dest) != sign(res))
			cpu.eflags.OF = 1;
		else
			cpu.eflags.OF = 0;
	}else {
		cpu.eflags.OF = 0;
	}
}

// sbb
void set_CF_sbb(uint32_t src, uint32_t dest, size_t data_size) {
	/*if old CF = 0, same as sub*/
	/*if old CF = 1, CF = 1 when ext_dest <= ext_src*/
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
	if(cpu.eflags.CF == 0)
		cpu.eflags.CF = dest < src;
	else
		cpu.eflags.CF = dest <= src;
}

void set_OF_sbb(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
	/*same as sub*/
	set_OF_sub(res, src, dest, data_size);
}

// mul
void set_CF_OF_mul(uint32_t src, uint32_t dest, size_t data_size) {
	/*CF = 0 when high data_size bits of res == 0*/
	uint64_t res = (uint64_t)(src * dest);
	uint64_t res64_high32 = res & 0xFFFFFFFF00000000;
	uint64_t res32_high16 = res & 0x00000000FFFF0000;
	uint64_t res16_high8 = res & 0x000000000000FF00;
	switch(data_size) {
		case 8: 
				if(res16_high8 == 0)
					cpu.eflags.CF = 0;
				else
					cpu.eflags.CF = 1;
				break;
		case 16:
				if(res32_high16 == 0)
					cpu.eflags.CF = 0;
				else
					cpu.eflags.CF = 1;
				break;
		default:
				if(res64_high32 == 0)
					cpu.eflags.CF = 0;
				else
					cpu.eflags.CF = 1;
				break;

	}
	cpu.eflags.OF = cpu.eflags.CF;
}

// shl
void set_CF_shl(uint32_t dest, uint32_t src, size_t data_size) {
	/*CF = the last bit that shift out*/
	if(src != 0){
		if(src > data_size)
			cpu.eflags.CF = 0;
		else {
			uint32_t judge = 1 << (data_size - src);
			cpu.eflags.CF = ((dest & judge) != 0);
		}
	}
}

// shr
void set_CF_shr(uint32_t dest, uint32_t src, size_t data_size) {
	/*00001111>>5, 10000 */
	if(src != 0){
		if(src > data_size)
			cpu.eflags.CF = 0;
		else {
			uint32_t judge = 1 << (src - 1);
			cpu.eflags.CF = ((dest & judge) != 0);
		}
	}
}
