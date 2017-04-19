#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

unsigned int get_op(unsigned int i) {//6
    return i >> 26;
}

unsigned int get_rs(unsigned int i) {//5
    return (i >> 21) & 0x0000001f;
}

unsigned int get_rt(unsigned int i) {//5
    return (i >> 16) & 0x0000001f;
}

unsigned int get_rd(unsigned int i) {//5
    return (i >> 11) & 0x0000001f;
}

unsigned int get_sha(unsigned int i) {//5
    return (i >> 6) & 0x0000001f;
}

unsigned int get_func(unsigned int i) {//6
    return i & 0x0000003f;
}

int get_imm(unsigned int i) {//16
    return (i & 0x0000ffff);
}

int get_addr(unsigned int i) {//26
    return (i & 0x03ffffff);
}

char type(unsigned int op){
    switch(op) {
    case 0x00: return 'R';
    case 0x02:
    case 0x03:
    case 0x3f: return 'J';
    default: return 'I';
    }
}

