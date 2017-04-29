#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"
void EX_stage() {
    CheckForward();
    if(DMchange > -1) {
        if(rS[DMchange] == 1) rS[DMchange] = 6;
        else if(rS[DMchange] == 3) rS[DMchange] = 4;
        DMchange = -1;
    }
    if(WBchange > -1) {
        if(rS[WBchange] == 2) rS[WBchange] = 0;
        if(rS[WBchange] == 4) rS[WBchange] = 0;
        WBchange = -1;
    }
    EXregSchange();
    switch(type(get_op(EX))) {
        case 'R':
            REX(get_func(EX), get_rs(EX), get_rt(EX), get_rd(EX), get_sha(EX));
            break;
        case 'J':
            JSEX(get_op(EX), get_addr(EX));
            break;
        default:
            IEX(get_op(EX), get_rs(EX), get_rt(EX), get_imm(EX));
            break;
    }
}

void CheckForward() {
    unsigned int op, fun, rt, rs, rd;
    op = get_op(EX);
    fun = get_func(EX);
    ID_next = IF;
    EX_next = ID;
    DM_next = EX;
    WB_next = DM;
    if(type(op) == 'R') {
        rs = get_rs(EX);
        rt = get_rt(EX);
        rd = get_rd(EX);
        switch(fun) {
            case 0x00: //sll
                if(rt == 0 && rd == 0 && get_sha(EX) == 0) break; //nop
            case 0x02: //srl
            case 0x03: //sra
                if(rS[rt] == 1) { // EXtoEX
                    EXtoEX = rt;
                    EXtoEX_case = 2;
                }
                if(rS[rt] == 2) { // DMtoEX
                    DMtoEX = rt;
                    DMtoEX_case = 2;
                    rS[rt] = 0;
                }
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
                if(rS[rs] == 1 || rS[rt] == 1) {
                    EXtoEX = (rS[rs] == 1)? rs : rt;
                    EXtoEX_case = (rS[rs] == 1)? 1 : 2;
                    if(rS[rs] == rS[rt]) EXtoEX_case = 3;
                }
                if((rS[rs] == 2 || rS[rs] == 4) && rS[rs] == rS[rt]) {
                    DMtoEX = rs;
                    DMtoEX_case = 3;
                    rS[rs] = 0;
                }
                else if(rS[rs] == 2 || rS[rs] == 4) {
                    DMtoEX = rs;
                    DMtoEX_case = 1;
                    rS[rs] = 0;
                }
                else if(rS[rt] == 2 || rS[rt] == 4) {
                    DMtoEX = rt;
                    DMtoEX_case = 2;
                    rS[rt] = 0;
                }
                if(rS[rt] == 3) STALLED();
                break;
            case 0x10:
            case 0x12:
            default:
                break;
        }
    }
    else if(type(op) == 'I') {
        rs = get_rs(EX);
        rt = get_rt(EX);
        switch(op) {
            case 0x2B: //sw
            case 0x29: //sh
            case 0x28: //sb
                if(rS[rt] == 1) {
                    EXtoEX = rt;
                    EXtoEX_case = 2;
                }
                if(rS[rt] == 2 || rS[rt] == 4) {
                    DMtoEX = rt;
                    DMtoEX_case = 2;
                }
                if(rS[rt] == 3) STALLED();
            case 0x08: //addi
            case 0x09: //addiu
            case 0x0C: //andi
            case 0x0D: //ori
            case 0x0E: //nori
            case 0x0A: //slti
                if(rS[rs] == 1) {
                    EXtoEX = rs;
                    EXtoEX_case = 1;
                }
                if(rS[rs] == 2 || rS[rs] == 4) {
                    DMtoEX = rs;
                    DMtoEX_case = 1;
                }
                if(rS[rs] == 3) STALLED();
                break;
            case 0x23: //lw
            case 0x21: //lh
            case 0x25: //lhu
            case 0x20: //lb
            case 0x24: //lbu
                if(rS[rs] == 1) {
                    EXtoEX = rs;
                    EXtoEX_case = 1;
                }
                if(rS[rs] == 2 || rS[rs] == 4) {
                    DMtoEX = rs;
                    DMtoEX_case = 1;
                }
                if(rS[rs] == 3) STALLED();
                break;
            case 0x04: //beq
            case 0x05: //bne
                if(rS[rs] == 3 || rS[rt] == 3)  STALLED();
            case 0x07: //bgtz
            case 0x0F: //lui
            default:
                break;
        }
    }
}


void EXregSchange() {
    unsigned int op, fun, rt, rs, rd;
    op = get_op(EX);
    fun = get_func(EX);
    ID_next = IF;
    EX_next = ID;
    DM_next = EX;
    WB_next = DM;
    if(type(op) == 'R') {
        rs = get_rs(EX);
        rt = get_rt(EX);
        rd = get_rd(EX);
        switch(fun) {
            case 0x00: //sll
                if(rt == 0 && rd == 0 && get_sha(EX) == 0) break; //nop
            case 0x02: //srl
            case 0x03: //sra
                if(rd != 0) rS[rd] = 1;
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
                if(rd != 0) rS[rd] = 1;
                break;
            case 0x10: //mfhi
            case 0x12: //mflo
                if(rd != 0) rS[rd] = 1;
            default:
                break;
        }
    }
    else if(type(op) == 'I') {
        rs = get_rs(EX);
        rt = get_rt(EX);
        switch(op) {
            case 0x2B: //sw
            case 0x29: //sh
            case 0x28: //sb
                break;
                //
            case 0x08: //addi
            case 0x09: //addiu
            case 0x0C: //andi
            case 0x0D: //ori
            case 0x0E: //nori
            case 0x0A: //slti
                if(rt != 0) rS[rt] = 1;
                break;
            case 0x23: //lw
            case 0x21: //lh
            case 0x25: //lhu
            case 0x20: //lb
            case 0x24: //lbu
                if(rt != 0) rS[rt] = 3;
                break;
            case 0x0F: //lui
                if(rt != 0) rS[rt] = 1;
            case 0x04: //beq
            case 0x05: //bne
            case 0x07: //bgtz
            default:
                break;
        }
    }
    else if(type(op) == 'J' && op == 0x03) { //jal
        rS[31] = 1;
    }
}

void JSEX(unsigned int op, unsigned int C) {
    switch(op){
    case 0x02://j
    case 0x03://jal
        rB[31] = R31;
        break;
    case 0x3f://halt
        halt = 1;
        break;
    default:
        halt = 1;
        bigError = 1;
        printf("illegal instruction found at 0x%08x",PC * 4 - 4);
        break;
    }
}

void REX(unsigned int func, unsigned int s, unsigned int t, unsigned int d, unsigned int C){
    long long t1, t2, temp;
    unsigned long long ull;
    int ss, tt;
    ss = (rS[s] > 0)? rB[s] : r[s];
    tt = (rS[t] > 0)? rB[t] : r[t];
    int n;
    switch(func){
    case 0x20:///add
        write_0(d);
        number_overflow(ss, tt, 1);
        rB[d] = ss + tt;
        rB[0] = 0;
        break;
    case 0x21:///addu
        write_0(d);
        rB[d] = ss + tt;
        rB[0] = 0;
        break;
    case 0x22:///sub
        write_0(d);
        number_overflow(ss, -tt, 1);
        rB[d] = ss - tt;
        rB[0] = 0;
        break;
    case 0x24://and
        write_0(d);
        rB[d] = ss & tt;
        rB[0] = 0;
        break;
    case 0x25://or
        write_0(d);
        rB[d] = ss | tt;
        rB[0] = 0;
        break;
    case 0x26://xor
        write_0(d);
        rB[d] = ss ^ tt;
        rB[0] = 0;
        break;
    case 0x27://nor
        write_0(d);
        rB[d] = ~(ss | tt);
        rB[0] = 0;
        break;
    case 0x28://nand
        write_0(d);
        rB[d] = ~(ss & tt);
        rB[0] = 0;
        break;
    case 0x2a://slt
        write_0(d);
        rB[d] = ss < tt;
        rB[0] = 0;
        break;
    case 0x00://sll
        if(t == 0 && d == 0 && C == 0) break; //nop
        write_0(d);
        rB[d] = tt << C;
        rB[0] = 0;
        break;
    case 0x02://srl
        write_0(d);
        rB[d] = (unsigned int)tt >> C;
        rB[0] = 0;
        break;
    case 0x03://sra
        write_0(d);
        rB[d] = tt >> C;
        rB[0] = 0;
        break;
    case 0x08://jr
        PC_overflow();
        break;
    case 0x18:///mult
        overwrite_HiLo(0);
        number_overflow(ss, tt, 0);
        t1 = ss;
        t2 = tt;
        ull = t1 * t2;
        Hi = (int) (ull >> 32);
        Lo = (int) (ull & 0x00000000ffffffff);
        break;
    case 0x19:///multu
        overwrite_HiLo(0);
        t1 = ss & 0x00000000ffffffff;
        t2 = tt & 0x00000000ffffffff;
        ull = t1 * t2;
        Hi = (int) (ull >> 32);
        Lo = (int) (ull & 0x00000000ffffffff);
        break;
    case 0x10://mfhi
        write_0(d);
        overwrite_HiLo(1);
        rB[d] = Hi;
        rB[0] = 0;
        break;
    case 0x12://mflo
        write_0(d);
        overwrite_HiLo(1);
        rB[d] = Lo;
        rB[0] = 0;
        break;
    default:
        halt = 1;
        bigError = 1;
        printf("illegal instruction found at 0x%08x",PC * 4 - 4);
        break;
    }

}

void IEX(unsigned int op, unsigned int s, unsigned int t, int C){
    long long temp;
    unsigned int a, b, c, d, Cu = C & 0x0000ffff;
    int ss, tt;
    ss = (rS[s] > 0)? rB[s] : r[s];
    tt = (rS[t] > 0)? rB[t] : r[t];
    switch(op){
    case 0x08://addi
        write_0(t);
        number_overflow(ss, C, 1);
        rB[t] = ss + C;
        rB[0] = 0;
        break;
    case 0x09://addiu
        write_0(t);
        rB[t] = ss + C;
        rB[0] = 0;
        break;
    case 0x23://lw
        write_0(t);
        number_overflow(ss, C, 1);
        mem_overflow(ss + C, 3);
        data_misaligned(ss + C, 1);
        mem_addr = ss + C;
        break;
    case 0x21://lh
        write_0(t);
        number_overflow(ss, C, 1);
        mem_overflow(ss + C, 1);
        data_misaligned(ss + C, 0);
        mem_addr = ss + C;
        break;
    case 0x25://lhu
        write_0(t);
        number_overflow(ss, C, 1);
        mem_overflow(ss + C, 1);
        data_misaligned(ss + C, 0);
        mem_addr = ss + C;
        break;
    case 0x20://lb
        write_0(t);
        number_overflow(ss, C, 1);
        mem_overflow(ss + C, 0);
        mem_addr = ss + C;
        break;
    case 0x24://lbu
        write_0(t);
        number_overflow(ss, C, 1);
        mem_overflow(ss + C, 0);
        mem_addr = ss + C;
        break;
    case 0x2b://sw
        number_overflow(ss, C, 1);
        mem_overflow(ss + C, 3);
        data_misaligned(ss + C, 1);
        mem_addr = ss + C;
        rDB[t] = tt;
        break;
    case 0x29://sh
        number_overflow(ss, C, 1);
        mem_overflow(ss + C, 1);
        data_misaligned(ss + C, 0);
        mem_addr = ss + C;
        rDB[t] = tt;
        break;
    case 0x28://sb
        number_overflow(ss, C, 0);
        mem_overflow(ss + C, 0);
        mem_addr = ss + C;
        rDB[t] = tt;
        break;
    case 0x0f:///lui
        write_0(t);
        rB[t] = Cu << 16;
        rB[0] = 0;
        break;
    case 0x0c:///andi
        write_0(t);
        a = ss;
        rB[t] = a & Cu;
        rB[0] = 0;
        break;
    case 0x0d:///ori
        write_0(t);
        a = ss;
        rB[t] = ss | Cu;
        rB[0] = 0;
        break;
    case 0x0e:///nori
        write_0(t);
        a = ss;
        rB[t] = ~(a | Cu);
        rB[0] = 0;
        break;
    case 0x0a://slti
        write_0(t);
        rB[t] = ss < C;
        rB[0] = 0;
        break;
    case 0x04://beq
    case 0x05://bne
    case 0x07://bgtz
        break;
    default:
        halt = 1;
        bigError = 1;
        printf("illegal instruction found at 0x%08x",PC * 4 - 4);
        break;
    }
}