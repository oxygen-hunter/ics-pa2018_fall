#include "cpu/instr.h"

make_intr_func(cli) {
	cpu.eflags.IF = 0;
	return 1;
}
