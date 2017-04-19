#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

void WB_stage() {
    unsigned int op, fun, rt, rs, rd;
    op = get_op(ID);
    fun = get_func(ID);
    if(type(op) == 'R') {
        rs = get_rs(ID);
        rt = get_rt(ID);
        rd = get_rd(ID);
        switch(fun) {
            case 0x00:
                if(rt == 0 && rd == 0 && get_sha(ID) == 0) break; //nop
                else { //sll
                    rS[rd] = 0;
                    r[rd] = rB[rd];
                    break;
                }
            case 0x20: //add
            case 0x21: //addu
            case 0x22: //sub
            case 0x24: //and
            case 0x25: //or
            case 0x26: //xor
            case 0x27: //nor
            case 0x28: //nand
            case 0x2A: //slt
            case 0x02: //srl
            case 0x03: //sra
                rS[rd] = 0;
                r[rd] = rB[rd];
                break;
            case 0x10: //mfhi
                r[rd] = Hi;
                break;
            case 0x12: //mflo
                r[rd] = Lo;
                break;
            default: // mult, multu
                break;
        }
    }
    else if(type(op) == 'I') {
        rs = get_rs(ID);
        rt = get_rt(ID);
        switch(op) {
            case 0x08: //addi
            case 0x09: //addiu
            case 0x2B: //sw
            case 0x29: //sh
            case 0x28: //sb
            case 0x0C: //andi
            case 0x0D: //ori
            case 0x0E: //nori
            case 0x0A: //slti
            case 0x23: //lw
            case 0x21: //lh
            case 0x25: //lhu
            case 0x20: //lb
            case 0x24: //lbu
            case 0x0F: //lui
                r[rt] = rB[rt];
                rS[rt] = 0;
                break;
            case 0x04: //beq
            case 0x05: //bne
            case 0x07: //bgtz
            default:
                break;
        }
    }
}