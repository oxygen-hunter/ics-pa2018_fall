#include "nemu.h"
#include "cpu/reg.h"
#include "memory/memory.h"
#include "cpu/cpu.h"
#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, NUM, REG, SYMB

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// white space
	{"\\+", '+'},
	{"\\-", '-'},
	{"==", EQ},
	{"[0-9]+", NUM},
	{"\\$e[a,c,d,b]x", REG},
	{"\\$e[s,b]p", REG},
	{"\\$e[s,d]i", REG},
	{"[a-zA-Z]+[a-zA-Z0-9]*", SYMB},
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			assert(ret != 0);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

int which_reg(char* str);

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				printf("match regex[%d] at position %d with len %d: %.*s\n", i, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */
				memset(tokens[nr_token].str, 0, 32); //zeror str
				memcpy(tokens[nr_token].str, substr_start, substr_len); //to store substr

				/* case REG's variable */
				int reg_x = 0;
				char reg_val_s[32] = {0};

				switch(rules[i].token_type) {
								
							  //uint32_t reg_val_i;
							  
					case REG: 
							  reg_x = which_reg(tokens[nr_token].str); //to judge $xxx is which reg
							  //reg_val_i = cpu.gpr[reg_x].val; //get reg's val (uint32_t)
							  
							  memset(reg_val_s, 0, 32);
							  sprintf(reg_val_s, "%d", reg_x); //get reg's val (string)
							  memcpy(tokens[nr_token].str, reg_val_s, 32); //copy reg's val (string) to token's str
					default: tokens[nr_token].type = rules[i].token_type;
							 nr_token ++;
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

uint32_t eval(int p, int q);

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	*success = true; //??

	/*TODO:Implement code to eeeeeevaluate the expression.*/
	/*for(int i = 0; i < nr_token; i++) {
		if(tokens[i].type == '*' &&(i == 0 || tokens[i - 1].type == certain type) {
			tokens[i].type = DEREF;
		}
	}*/


	//printf("\nPlease implement expr at expr.c\n");
	//assert(0);

	return eval(0, nr_token - 1);
}

//uint32_t my_atoi(char* str);
bool check_parentheses(int p, int q);
int dominant_operator_position(int p, int q);

uint32_t eval(int p, int q) { //compute val of tokens
	if(p > q) {
		/*TODO:bad expression*/
		printf("\nInvalid expression. Please check.\n");
	}
	else if(p == q) {
		return atoi(tokens[p].str);
	}
	else if(check_parentheses(p,q) == true) {
		return eval(p + 1, q - 1);
	}
	else {
		int op = dominant_operator_position(p, q); 
		// to find the position of dominant operator in tokes[p, q]
		uint32_t val1 = eval(p, op - 1);
		uint32_t val2 = eval(op + 1, q);
		switch(tokens[op].type) {
			case '+': return val1 + val2;
			case '-': return val1 - val2; //to be continued...
			case '*': return val1 * val2; //to be continued...
			case '/': return val1 / val2;
		
			default: 
				printf("\ninvalid op type at tokens[%d], whose type is %d.\n", op, tokens[op].type);
				assert(0);
		}
	}
	return -1;
}

/*
uint32_t my_atoi(char* str) {
	//default str length <= 32
	uint32_t val_i = 0;
	int str_len = 0;
	uint32_t ten_exp_i = 1; //10^i	

	for(; str_len < 32; str_len++) {
		if(str[str_len] == '\0')
			break;
	}
//printf("to be atoi:%s\n", str);
	int i;
	for(i = str_len - 1; i >= 0; i--) {
		val_i += ((uint32_t)(str[i]-'0')) * ten_exp_i;
//printf("val_i:%d\n", val_i);
		ten_exp_i *= 10;
//printf("ten_exp_i:%d\n", ten_exp_i);
	}
//printf("val_i:%d\n", val_i);
	return val_i;
}*/

bool check_parentheses(int p, int q) {

	return false;
}

int dominant_operator_position(int p, int q) {
	return 0;
}

int which_reg(char* str) { //str format: $e??
	char str2 = str[2], str3 = str[3];
	if(str3 == 'x') { //e[a,c,d,b]x
		if(str2 == 'a') return cpu.eax;
		if(str2 == 'c') return cpu.ecx;
		if(str2 == 'd') return cpu.edx;
		if(str2 == 'b') return cpu.ebx;
	}
	else if(str3 == 'p') { //e[s,b]p
		if(str2 == 's') return cpu.esp;
		if(str2 == 'b') return cpu.ebp;
	}
	else if(str3 == 'i') { //e[s,d]i
		if(str2 == 's') return cpu.esi;
		if(str2 == 'd') return cpu.edi;
	}
	else {
		printf("\nreg format error: %s\n", str);
		assert(0);
	}
	return -1;
}







