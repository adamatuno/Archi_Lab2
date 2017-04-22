#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

void ID_stage() {
    unsigned int op, fun, rt, rs, rd;
    int C, tt, ss;
    op = get_op(ID);
    fun = get_func(ID);
    rs = get_rs(ID);
    rt = get_rt(ID);
    C = get_imm(ID);
    ss = r[rs];
    tt = r[rt];
    if(type(op) == 'R') {
        rs = get_rs(ID);
        rt = get_rt(ID);
        rd = get_rd(ID);
        switch(fun) {
            case 0x00: //sll
                if(rt == 0 && rd == 0 && get_sha(ID) == 0) break; //nop
            case 0x02: //srl
            case 0x03: //sra
                if(rS[rt] == 3) STALLED();
                break;
            case 0x20: //add
            case 0x21: //addu
            case 0x22: //sub
            case 0x24: //and
            case 0x25: //or
            case 0x26: //xor
            case 0x27: //nor
            case 0x28: //nand
            case 0x2A: //slt
            case 0x18:///mult
            case 0x19:///multu
                if(rS[rs] == 3 || rS[rt] == 3) STALLED();
                break;
            default:
                break;
        }
    }
    else if(type(op) == 'I') {
        switch(op) {
            case 0x2B: //sw
            case 0x29: //sh
            case 0x28: //sb
            case 0x08: //addi
            case 0x09: //addiu
            case 0x0C: //andi
            case 0x0D: //ori
            case 0x0E: //nori
            case 0x0A: //slti
            case 0x23: //lw
            case 0x21: //lh
            case 0x25: //lhu
            case 0x20: //lb
            case 0x24: //lbu
                if(rS[rs] == 3)  STALLED();
                break;
            case 0x04: //beq
            case 0x05: //bne
                if(rS[rs] == 1 || rS[rt] == 1) STALLED();
                else if(rS[rs] == 3 || rS[rt] == 3) STALLED();
                else if(rS[rs] == 4 || rS[rt] == 4) {
                    STALLED();
                    rS[rs] = 0;
                }
                else if(rS[rs] == 2 || rS[rt] == 2 || rS[rs] == 6 || rS[rt] == 6) {
                    if(rS[rs] == 2 || rS[rs] == 6) {
                        EXtoID = rs;
                        EXtoID_case = 1;
                        ss = rB[rs];
                    }
                    else {
                        EXtoID = rt;
                        EXtoID_case = 2;
                        tt = rB[rt];
                    }
                    if(rS[rs] == rS[rt]) EXtoID_case = 3;
                }
                break;
            case 0x07: //bgtz
                if(rS[rs] == 1)  STALLED();
                if(rS[rs] == 3 || rS[rt] == 3)  STALLED();
                if(rS[rs] == 2) {
                    EXtoID = rs;
                    EXtoID_case = 1;
                    ss = rB[rs];
                }
            default:
                break;
        }
    }

    if(!stalled) {
        if(type(op) == 'I' && op == 0x04) { //beq
            if(ss == tt) PC_next = PC + 1 + C;
            newIF(PC_next);
        }
        else if(type(op) == 'I' && op == 0x05) { //bne
            if(ss != tt) PC_next = PC + 1 + C;
            newIF(PC_next);
        }
        else if(type(op) == 'I' && op == 0x07) { //bgtz
            if(ss > 0) PC_next = PC + 1 + C;
            newIF(PC_next);
        }
    }
}


void STALLED() {
    stalled = 1;
    IF_next = IF;
    ID_next = ID;
    EX_next = 0x00000000;
    PC_next = PC;
}