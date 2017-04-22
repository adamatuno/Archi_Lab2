#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"
void DM_stage() {
    unsigned int op, s, t, C;
    op = get_op(DM);
    regSchange();
    if(type(op) == 'I') {
        s = get_rs(DM);
        t = get_rt(DM);
        C = get_imm(DM);
        unsigned int a, b, c, d, Cu = C & 0x0000ffff;
        switch(op) {
            case 0x23://lw
                write_0(t);
                if(mem_out(mem_addr, 3)) break;
                a = D[mem_addr] & 0x000000ff;
                b = D[mem_addr + 1] & 0x000000ff;
                c = D[mem_addr + 2] & 0x000000ff;
                d = D[mem_addr + 3] & 0x000000ff;
                rB[t] = (a << 24) | (b << 16) | (c << 8) | d;
                rB[0] = 0;
                break;
            case 0x21://lh
                write_0(t);
                if(mem_out(mem_addr, 1)) break;
                a = D[mem_addr];
                b = D[mem_addr + 1];
                if(a >> 7) rB[t] = ((a << 8) | b) | 0xffff0000;
                else rB[t] = ((a << 8) | b) & 0x0000ffff;
                rB[0] = 0;
                break;
            case 0x25://lhu
                write_0(t);
                if(mem_out(mem_addr, 1)) break;
                a = D[mem_addr] & 0x000000ff;
                b = D[mem_addr + 1] & 0x000000ff;
                rB[t] = ((a << 8) | b) & 0x0000ffff;
                rB[0] = 0;
                break;
            case 0x20://lb
                write_0(t);
                if(mem_out(mem_addr, 0)) break;
                a = D[mem_addr] & 0x000000ff;
                if(a >> 7) rB[t] = a | 0xffffff00;
                else rB[t] = a;
                rB[0] = 0;
                break;
            case 0x24://lbu
                write_0(t);
                if(mem_out(mem_addr, 0)) break;
                rB[t] = D[mem_addr] & 0x000000ff;
                rB[0] = 0;
                break;
            case 0x2b://sw
                if(mem_out(mem_addr, 3)) break;
                D[mem_addr] = (r[t] >> 24) & 0x000000ff;
                D[mem_addr + 1] = (r[t] >> 16) & 0x000000ff;
                D[mem_addr + 2] = (r[t] >> 8) & 0x000000ff;
                D[mem_addr + 3] = r[t] & 0x000000ff;
                break;
            case 0x29://sh
                if(mem_out(mem_addr, 1)) break;
                D[mem_addr] = (r[t] >> 8) & 0x000000ff;
                D[mem_addr + 1] = r[t] & 0x000000ff;
                break;
            case 0x28://sb
                if(mem_out(mem_addr, 0)) break;
                D[mem_addr] = r[t] & 0x000000ff;
                break;
        }
    }
}

void regSchange() {
    unsigned int op, rs, rt, rd, fun;
    op = get_op(DM);
    rs = get_rs(DM);
    rt = get_rt(DM);
    fun = get_func(DM);
    if(type(op) == 'R') {
        rd = get_rd(DM);
        switch(fun) {
            case 0x00: //sll
                if(rt == 0 && rd == 0 && get_sha(DM) == 0) break; //nop
            case 0x02: //srl
            case 0x03: //sra
            case 0x20: //add
            case 0x21: //addu
            case 0x22: //sub
            case 0x24: //and
            case 0x25: //or
            case 0x26: //xor
            case 0x27: //nor
            case 0x28: //nand
            case 0x2A: //slt
            case 0x10: //mfhi
            case 0x12: //mflo
                if(rS[rd] == 1) DMchange = rd;
                break;
            default:
                break;
        }
    }
    else if(type(op) == 'I') {
        switch(op) {
            case 0x08: //addi
            case 0x09: //addiu
            case 0x0C: //andi
            case 0x0D: //ori
            case 0x0E: //nori
            case 0x0A: //slti
                if(rS[rt] == 1) DMchange = rt;
                break;
            case 0x23: //lw
            case 0x21: //lh
            case 0x25: //lhu
            case 0x20: //lb
            case 0x24: //lbu
                if(rS[rt] == 3) DMchange = rt;
                break;
            case 0x0F: //lui
            case 0x04: //beq
            case 0x05: //bne
            case 0x07: //bgtz
            case 0x2B: //sw
            case 0x29: //sh
            case 0x28: //sb
            default:
                break;
        }
    }
}