#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"
void ID_stage() {
    unsigned int op, fun, rt, rs, rd, C;
    op = get_op(ID);
    fun = get_func(ID);
    ID_next = IF;
    EX_next = ID;
    DM_next = EX;
    WB_next = DM;
    rs = get_rs(ID);
    rt = get_rt(ID);
    C = get_imm(ID);
    if(type(op) == 'I' && op == 0x04) { //beq
        if(r[rs] == r[rt]) PC_next = PC + 1 + C;
        newIF(PC_next);
    }
    else if(type(op) == 'I' && op == 0x05) { //bne
        if(r[rs] != r[rt]) PC_next = PC + 1 + C;
        newIF(PC_next);
    }
    else if(type(op) == 'I' && op == 0x07) { //bgtz
        if(r[rs] > 0) PC_next = PC + 1 + C;
        newIF(PC_next);
    }
    if(type(op) == 'R') {
        rd = get_rd(ID);
        switch(fun) {
            case 0x00: //sll
                if(rt == 0 && rd == 0 && get_sha(ID) == 0) break; //nop
            case 0x02: //srl
            case 0x03: //sra
                if(rS[rt] == 1) { // EXtoID
                    EXtoID = rt;
                    EXtoID_case = 2;
                }
                else if(rS[rt] == 2) { // DMtoEX
                    DMtoEX = rt;
                    DMtoEX_case = 2;
                    stalled = 1;
                    IF_next = IF;
                    ID_next = ID;
                    EX_next = 0x00000000;
                }
                rS[rd] = 1;
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
                if(rS[rs] == 1 || rS[rt] == 1) {
                    EXtoID = (rS[rs] == 1)? rs : rt;
                    EXtoID_case = (rS[rs] == 1)? 1 : 2;
                }
                else if(rS[rs] == 2 || rS[rt] == 2) {
                    DMtoEX = (rS[rs] == 1)? rs : rt;
                    DMtoEX_case = (rS[rs] == 2)? 1 : 2;
                    IF_next = IF;
                    ID_next = ID;
                    EX_next = 0x00000000;
                }
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
                if(rS[rs] == 1) {
                    EXtoID = rs;
                    EXtoID_case = 1;
                }
                else if(rS[rs] == 2) {
                    DMtoEX = rs;
                    DMtoEX_case = 1;
                    stalled = 1;
                    IF_next = IF;
                    ID_next = ID;
                    EX_next = 0x00000000;
                }
                break;
            case 0x23: //lw
            case 0x21: //lh
            case 0x25: //lhu
            case 0x20: //lb
            case 0x24: //lbu
                if(rS[rs] == 1) {
                    EXtoID = rs;
                    EXtoID_case = 1;
                }
                else if(rS[rs] == 2) {
                    DMtoEX = rs;
                    DMtoEX_case = 1;
                    stalled = 1;
                    IF_next = IF;
                    ID_next = ID;
                    EX_next = 0x00000000;
                }
                rS[rt] = 2;
                break;
            case 0x04: //beq
            case 0x05: //bne
            case 0x07: //bgtz
                if(rS[rs] == 1 || rS[rt] == 1) {
                    EXtoID = (rS[rs] == 1)? rs : rt;
                    EXtoID_case = (rS[rs] == 1)? 1 : 2;
                }
                else if(rS[rs] == 2 || rS[rs] == 2) {
                    DMtoEX = (rS[rs] == 1)? rs : rt;
                    DMtoEX_case = (rS[rs] == 2)? 1 : 2;
                    IF_next = IF;
                    ID_next = ID;
                    EX_next = 0x00000000;
                }
                break;
            case 0x0F: //lui
                rS[rt] = 1;
            default:
                break;
        }
    }
}