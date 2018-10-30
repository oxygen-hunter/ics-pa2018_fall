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
	NOTYPE = 256, EQ, NUM, REG, SYMB, BRKT_L, BRKT_R, HEX, AND, OR, NEQ, NOT, DEREF, L, LE, G, GE, NEG

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
	{"\\*", '*'},
	{"\\/", '/'},
	{"<=", LE},
	{">=", GE},
	{"<", L},
	{">", G},
	{"!=", NEQ},
	{"==", EQ},
	{"&&", AND},
	{"\\|\\|", OR},
	{"!", NOT},
	{"\\(", BRKT_L},
	{"\\)", BRKT_R},
	{"0[Xx][0-9a-fA-F]+", HEX},
	{"[0-9]+", NUM},
	{"\\$e[a,c,d,b]x", REG},
	{"\\$e[s,b]p", REG},
	{"\\$e[s,d]i", REG},
	{"\\$eip", REG},
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

uint32_t which_reg(char* str);
uint32_t trans_hex_to_int(char* str);

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;
//printf("\n111\n");
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
				uint32_t reg_x = 0;
				char reg_val_s[32] = {0};

				/* case HEX's variable */
				uint32_t val_int = 0;
				char val_int_s[32] = {0};

				switch(rules[i].token_type) {
					case REG: 
							  reg_x = which_reg(tokens[nr_token].str); //to judge $xxx is which reg and get val
							  memset(reg_val_s, 0, 32); //zero
							  sprintf(reg_val_s, "%d", reg_x); //get reg's val (string)
//printf("after sprintf: reg_val_s : %s\n", reg_val_s);
							  memset(tokens[nr_token].str, 0, 32); //zeror str
							  memcpy(tokens[nr_token].str, reg_val_s, 32); //copy reg's val (string) to token's str
//printf("now token's str: %s\n", tokens[nr_token].str);					
							  break;
					case HEX:  
							  val_int = trans_hex_to_int(tokens[nr_token].str); //to change hex to int
							  memset(val_int_s, 0, 32); //zero
							  sprintf(val_int_s, "%d", val_int);
							  memset(tokens[nr_token].str, 0, 32); //zeror str
							  memcpy(tokens[nr_token].str, val_int_s, 32);
							  break;
					
					case SYMB:
							  load_elf_tables(exec_file);
							  break;
					default:  
							  break;
				}
				
				tokens[nr_token].type = rules[i].token_type;
				nr_token ++;				


				if(rules[i].token_type == NOTYPE)
					nr_token --;

				break;
			}
		}
//printf("\nnr_token: %d\n", nr_token);
		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
	return true; 
}

uint32_t eval(int p, int q, bool *success);

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	*success = true; //?? to be continued...

	/*TODO:Implement code to eeeeeevaluate the expression.*/
	for(int i = 0; i < nr_token; i++) {
		if(tokens[i].type == '*' &&(i == 0 || (tokens[i - 1].type != REG && tokens[i - 1].type != NUM && tokens[i - 1].type != HEX && tokens[i - 1].type != BRKT_R))) { // * is deref
			tokens[i].type = DEREF;
		}
		if(tokens[i].type == '-' &&(i == 0 || (tokens[i - 1].type != REG && tokens[i - 1].type != NUM && tokens[i - 1].type != HEX && tokens[i - 1].type != BRKT_R))) { // - is neg
			tokens[i].type = NEG;
		}
	}

	//printf("\nPlease implement expr at expr.c\n");
	//assert(0);
//for(int i=0;i<nr_token;i++) {
//	printf("\n%s\n", tokens[i].str);
//}
	return eval(0, nr_token - 1, success);
}

int check_parentheses(int p, int q); // -1: can't match, 0: can match but not (...), 1: (...)
int dominant_operator_position(int p, int q);

uint32_t eval(int p, int q, bool *success) { //compute val of tokens
	if(p > q) {
		/*TODO:bad expression*/
		printf("\nInvalid expression. Please check.\n");
		printf("p:%d, q:%d\n", p, q);
		*success = false;
	}
	else if(p == q) {
//printf("\np==q==%d\n",p);
		return atoi(tokens[p].str);
	}
	else if(check_parentheses(p,q) == -1) {
		printf("\nCan't match \"(\" and \")\". Please check.\n");
		*success = false;
	}
	else if(check_parentheses(p,q) == 1) {
		return eval(p + 1, q - 1, success);
	}
	else {
//printf("\nbefore op\n");
		int op = dominant_operator_position(p, q); 
//printf("\ndomi_op is:%d\n", op);
		//if(op == p) {
			if(tokens[op].type == DEREF) { //5+*0x8048000+-(5) -> 5+*0x8048000 '+' -(5)
				vaddr_t addr = eval(op + 1, q, success);
				/*TODO: judge addr is valid*/

				uint32_t mem = vaddr_read(addr, 0, 4);

				tokens[op].type = NUM;
				char unary_num[32] = {0};
				memset(unary_num, 0, 32);
				memset(tokens[op].str, 0, 32);
				sprintf(unary_num, "%d", mem);
				memcpy(tokens[op].str, unary_num, 32);
				return eval(p, op, success);
			}
			else if(tokens[op].type == NEG) {
				uint32_t val = -eval(op + 1, q, success);
				
				tokens[op].type = NUM;
				char unary_num[32] = {0};
				memset(unary_num, 0, 32);
				memset(tokens[op].str, 0, 32);
				sprintf(unary_num, "%d", val);
				memcpy(tokens[op].str, unary_num, 32);
				return eval(p, op, success);
			}
			else if(tokens[op].type == NOT) {
				uint32_t val = !eval(op + 1, q, success);

				tokens[op].type = NUM;
				char unary_num[32] = {0};
				memset(unary_num, 0, 32);
				memset(tokens[op].str, 0, 32);
				sprintf(unary_num, "%d", val);
				memcpy(tokens[op].str, unary_num, 32);
				return eval(p, op, success);
			}
		//}

		// to find the position of dominant operator in tokes[p, q]
		uint32_t val1 = eval(p, op - 1, success);
		uint32_t val2 = eval(op + 1, q, success);
//printf("\nval1:%d, val2:%d\n", val1, val2);
		switch(tokens[op].type) {
			case '+': return val1 + val2;
			case '-': return val1 - val2; //to be continued...
			case '*': return val1 * val2; //to be continued...
			case '/': if(val2 != 0)
					  	return val1 / val2;
					  else {
					  	printf("\nDivide Fault: dividend can't be '0'!\n");
						printf("Divide Fault happens at: ");
						for(int j = op + 1; j <= q; j++)
							printf("%s", tokens[j].str);
						printf("\n");
						*success = false;
						return -1;
					  }
			case EQ: return val1 == val2;
			case NEQ: return val1 != val2;
			case AND: return val1 && val2;
			case OR: return val1 || val2;
			case L: return val1 < val2;
			case G: return val1 > val2;
			case LE: return val1 <= val2;
			case GE: return val1 >= val2;
			default: 
				printf("\ninvalid op type at tokens[%d], whose type is %d.\n", op, tokens[op].type);
				assert(0);
		}
	}
	return -1;
}

int find_bracket_r(int p, int q, int bracket_l_pos);

int check_parentheses(int p, int q) {
//printf("\nchecking parentheses... p:%d, q:%d\n", p, q);
	int stack[32];
	memset(stack, 0, 32 * sizeof(int));
	int top = -1;
	for(int i = p; i <= q; i++) {
		if(tokens[i].type == BRKT_L) {
			top ++; //push i
			stack[top] = i;
		}
		else if(tokens[i].type == BRKT_R) {
			top --; //pop
		}
		if(top < -1) {
			printf("\n\')\' more than \'(\' at tokens[%d]\n", i);
//printf("return -1\n");
			return -1;
		}
	}
	if(top > -1) {
		printf("\n\'(\' more than \')\'\n");
//printf("return -1\n");		
		return -1;
	}
	else if(tokens[p].type == BRKT_L && q == find_bracket_r(p, q, p)) { // (...)
//printf("return 1\n");
		return 1;
	}
//printf("return 0");
	return 0;
}

int oprator_precedence(int opr);

int dominant_operator_position(int p, int q) {
//printf("\ndomi's p:%d, q:%d\n", p, q);
	int domi_opr_pos = p;
	int domi = 0x7777777;
	int i_domi = 0x7fffffff;	
	bool domi_is_inited = false;
	for(int i = p; i <= q; i++) {
		i_domi = oprator_precedence(tokens[i].type);

		//handle (...)
		if(i_domi == 10) {
			int bracket_r_pos = find_bracket_r(i, q, i);
			i = bracket_r_pos;
		}

		if(domi_is_inited == false && i_domi != -1) { //to init domi
			domi_opr_pos = i;
			domi = i_domi;
			domi_is_inited = true;
		}
		else
			domi = oprator_precedence(tokens[domi_opr_pos].type);
		if(i_domi != -1) {
			if(i_domi <= domi)
				domi_opr_pos = i;
		}
//printf("domi:%d, i_domi:%d, i:%d, domi_pos:%d\n", domi, i_domi, i, domi_opr_pos);
	}
	return domi_opr_pos;
}

uint32_t which_reg(char* str) { //str format: $e??
	char str2 = str[2], str3 = str[3];
	if(str3 == 'x') { //e[a,c,d,b]x
		if(str2 == 'a') {printf("0x%08x\n",cpu.eax);printf("%d",cpu.eax);return cpu.eax;}
		if(str2 == 'c') return cpu.ecx;
		if(str2 == 'd') return cpu.edx;
		if(str2 == 'b') return cpu.ebx;
	}
	else if(str3 == 'p') { //e[s,b]p
		if(str2 == 's') return cpu.esp;
		if(str2 == 'b') return cpu.ebp;
		if(str2 == 'i') return cpu.eip;
	}
	else if(str3 == 'i') { //e[s,d]i
		if(str2 == 's') return cpu.esi;
		if(str2 == 'd') return cpu.edi;
	}
	else { //this situation won't happen because tokens can't match these ones.
		printf("\nreg format error: %s\n", str);
		assert(0);
	}
	return -1;
}

uint32_t trans_hex_to_int(char* str) {
	//str format: 0x?????
	char* hex_start = str + 2;
	int hex_len = 0;
	for(; hex_start[hex_len] != '\0'; hex_len ++); //get hex_len

	uint32_t val_int = 0;
	uint32_t hex_exp = 1;
	uint32_t one_bit = 0;
	for(int i = hex_len - 1; i >= 0; i --) {
		if('0' <= hex_start[i] && hex_start[i] <= '9')
			one_bit = hex_start[i] - '0';
		else if('a' <= hex_start[i] && hex_start[i] <= 'f')
			one_bit = hex_start[i] - 'a' + 10; //a-10, b-11 ...
		else if('A' <= hex_start[i] && hex_start[i] <= 'F')
			one_bit = hex_start[i] - 'A' + 10; //A-10, B-11 ...
		else { //won't happen because make_token has done for me
			printf("\nHex Format Fault\n");
		}
		val_int += one_bit * hex_exp;
		hex_exp *= 16;
	}
	return val_int;
}

int oprator_precedence(int opr) {
	if(opr == OR)
		return -10;
	if(opr == AND)
		return -9;
	if(opr == EQ || opr == NEQ)
		return -5;
	if(opr == L || opr == G || opr == LE || opr == GE)
		return -4;
	if(opr == '+' || opr == '-')
		return 1;
	if(opr == '*' || opr == '/')
		return 2;
	if(opr == DEREF || opr == NOT || opr == NEG)
		return 3;
	if(opr == BRKT_L || opr == BRKT_R)
		return 10;
	else return -1; //if opr is not an operator.
}

int find_bracket_r(int p, int q, int bracket_l_pos) {
	int brkt_l_num = 0;
	int brkt_r_num = 0;
	for(int i = p; i <= q; i ++) {
		if(tokens[i].type == BRKT_L)
			brkt_l_num ++;
		else if(tokens[i].type == BRKT_R)
			brkt_r_num ++;
		if(brkt_l_num != 0 && brkt_l_num == brkt_r_num)
			return i;
	}
	printf("\ncan't find tokens[%d]'s matched \')\'.\n", p);
	assert(0);
	return -1;
}




