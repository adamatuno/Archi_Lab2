#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"
void DM_stage() {
    unsigned int op, s, t, C;
    op = get_op(DM);
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