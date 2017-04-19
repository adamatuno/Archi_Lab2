#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

void newIF(int pc) {
    if(pc >= 0 && pc < 1024) IF_next = I[pc];
    else halt = 1;
}

void IF_stage(){
    unsigned int op, fun, rs, C;
    op = get_op(IF);
    fun = get_func(IF);
    rs = get_rs(IF);
    C = get_imm(IF);
    if(type(op) == 'R' && fun == 0x08) { //jr
        PC_next = r[rs] / 4;
        newIF(PC_next);
    }
    else if(type(op) == 'J' && op == 0x02) { //j
        PC_next = ((((PC + 1) << 2) & 0xf0000000) | (C << 2)) >> 2;
        newIF(PC_next);
    }
    else if(type(op) == 'J' && op == 0x03) { //jal
        PC_next = ((((PC + 1) << 2) & 0xf0000000) | (C << 2)) >> 2;
        newIF(PC_next);
    }
    else {
        PC_next = PC + 1;
        newIF(PC_next);
    }
}