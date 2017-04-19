#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"
void JSti(unsigned int op, unsigned int C){
    switch(op){
    case 0x02://j
        PC = (((PC << 2) & 0xf0000000) | (C << 2)) >> 2;
        PC_overflow();
        break;
    case 0x03://jal
        r[31] = PC << 2;
        PC = (((PC << 2) & 0xf0000000) | (C << 2)) >> 2;
        PC_overflow();
        break;
    case 0x3f://halt
        halt = 1;
        break;
    default:
        halt = 1;
        printf("illegal instruction found at 0x%08x",PC * 4 - 4);
        break;
    }
}

void Rti(unsigned int func, unsigned int s, unsigned int t, unsigned int d, unsigned int C){
    long long t1, t2, temp;
    unsigned long long ull;
    unsigned int sign;
    int n;
    switch(func){
    case 0x20:///add
        write_0(d);
        number_overflow(r[s], r[t], 1);
        r[d] = r[s] + r[t];
        r[0] = 0;
        break;
    case 0x21:///addu
        write_0(d);
        r[d] = r[s] + r[t];
        r[0] = 0;
        break;
    case 0x22:///sub
        write_0(d);
        number_overflow(r[s], -r[t], 1);
        r[d] = r[s] - r[t];
        r[0] = 0;
        break;
    case 0x24://and
        write_0(d);
        r[d] = r[s] & r[t];
        r[0] = 0;
        break;
    case 0x25://or
        write_0(d);
        r[d] = r[s] | r[t];
        r[0] = 0;
        break;
    case 0x26://xor
        write_0(d);
        r[d] = r[s] ^ r[t];
        r[0] = 0;
        break;
    case 0x27://nor
        write_0(d);
        r[d] = ~(r[s] | r[t]);
        r[0] = 0;
        break;
    case 0x28://nand
        write_0(d);
        r[d] = ~(r[s] & r[t]);
        r[0] = 0;
        break;
    case 0x2a://slt
        write_0(d);
        r[d] = r[s] < r[t];
        r[0] = 0;
        break;
    case 0x00://sll
        write_0(d);
        r[d] = r[t] << C;
        r[0] = 0;
        break;
    case 0x02://srl
        write_0(d);
        r[d] = (unsigned int)r[t] >> C;
        r[0] = 0;
        break;
    case 0x03://sra
        write_0(d);
        r[d] = r[t] >> C;
        r[0] = 0;
        break;
    case 0x08://jr
        PC = r[s] / 4;
        PC_overflow();
        break;
    case 0x18:///mult
        overwrite_HiLo(0);
        number_overflow(r[s], r[t], 0);
        t1 = r[s];
        t2 = r[t];
        ull = t1 * t2;
        Hi = (int) (ull >> 32);
        Lo = (int) (ull & 0x00000000ffffffff);
        break;
    case 0x19:///multu
        overwrite_HiLo(0);
        t1 = r[s] & 0x00000000ffffffff;
        t2 = r[t] & 0x00000000ffffffff;
        ull = t1 * t2;
        Hi = (int) (ull >> 32);
        Lo = (int) (ull & 0x00000000ffffffff);
        break;
    case 0x10://mfhi
        write_0(d);
        overwrite_HiLo(1);
        r[d] = Hi;
        r[0] = 0;
        break;
    case 0x12://mflo
        write_0(d);
        overwrite_HiLo(1);
        r[d] = Lo;
        r[0] = 0;
        break;
    default:
        halt = 1;
        printf("illegal instruction found at 0x%08x",PC * 4 - 4);
        break;
    }

}

void Iti(unsigned int op, unsigned int s, unsigned int t, int C){
    long long temp;
    unsigned int a, b, c, d, Cu = C & 0x0000ffff;
    switch(op){
    case 0x08://addi
        write_0(t);
        number_overflow(r[s], C, 1);
        r[t] = r[s] + C;
        r[0] = 0;
        break;
    case 0x09://addiu
        write_0(t);
        r[t] = r[s] + C;
        r[0] = 0;
        break;
    case 0x23://lw
        write_0(t);
        number_overflow(r[s], C, 1);
        mem_overflow(r[s] + C, 3);
        data_misaligned(r[s] + C, 1);
        if(mem_out(r[s] + C, 3)) break;
        a = D[r[s] + C] & 0x000000ff;
        b = D[r[s] + C + 1] & 0x000000ff;
        c = D[r[s] + C + 2] & 0x000000ff;
        d = D[r[s] + C + 3] & 0x000000ff;
        r[t] = (a << 24) | (b << 16) | (c << 8) | d;
        r[0] = 0;
        break;
    case 0x21://lh
        write_0(t);
        number_overflow(r[s], C, 1);
        mem_overflow(r[s] + C, 1);
        data_misaligned(r[s] + C, 0);
        if(mem_out(r[s] + C, 1)) break;
        a = D[r[s] + C];
        b = D[r[s] + C + 1];
        if(a >> 7) r[t] = ((a << 8) | b) | 0xffff0000;
        else r[t] = ((a << 8) | b) & 0x0000ffff;
        r[0] = 0;
        break;
    case 0x25://lhu
        write_0(t);
        number_overflow(r[s], C, 1);
        mem_overflow(r[s] + C, 1);
        data_misaligned(r[s] + C, 0);
        if(mem_out(r[s] + C, 1)) break;
        a = D[r[s] + C] & 0x000000ff;
        b = D[r[s] + C + 1] & 0x000000ff;
        r[t] = ((a << 8) | b) & 0x0000ffff;
        r[0] = 0;
        break;
    case 0x20://lb
        write_0(t);
        number_overflow(r[s], C, 1);
        mem_overflow(r[s] + C, 0);
        if(mem_out(r[s] + C, 0)) break;
        a = D[r[s] + C] & 0x000000ff;
        if(a >> 7) r[t] = a | 0xffffff00;
        else r[t] = a;
        r[0] = 0;
        break;
    case 0x24://lbu
        write_0(t);
        number_overflow(r[s], C, 1);
        mem_overflow(r[s] + C, 0);
        if(mem_out(r[s] + C, 0)) break;
        r[t] = D[r[s] + C] & 0x000000ff;
        r[0] = 0;
        break;
    case 0x2b://sw
        number_overflow(r[s], C, 1);
        mem_overflow(r[s] + C, 3);
        data_misaligned(r[s] + C, 1);
        if(mem_out(r[s] + C, 3)) break;
        D[r[s] + C] = (r[t] >> 24) & 0x000000ff;
        D[r[s] + C + 1] = (r[t] >> 16) & 0x000000ff;
        D[r[s] + C + 2] = (r[t] >> 8) & 0x000000ff;
        D[r[s] + C + 3] = r[t] & 0x000000ff;
        break;
    case 0x29://sh
        number_overflow(r[s], C, 1);
        mem_overflow(r[s] + C, 1);
        data_misaligned(r[s] + C, 0);
        if(mem_out(r[s] + C, 1)) break;
        D[r[s] + C] = (r[t] >> 8) & 0x000000ff;
        D[r[s] + C + 1] = r[t] & 0x000000ff;
        break;
    case 0x28://sb
        number_overflow(r[s], C, 0);
        mem_overflow(r[s] + C, 0);
        if(mem_out(r[s] + C, 0)) break;
        D[r[s] + C] = r[t] & 0x000000ff;
        break;
    case 0x0f:///lui
        write_0(t);
        r[t] = Cu << 16;
        r[0] = 0;
        break;
    case 0x0c:///andi
        write_0(t);
        a = r[s];
        r[t] = a & Cu;
        r[0] = 0;
        break;
    case 0x0d:///ori
        write_0(t);
        a = r[s];
        r[t] = r[s] | Cu;
        r[0] = 0;
        break;
    case 0x0e:///nori
        write_0(t);
        a = r[s];
        r[t] = ~(a | Cu);
        r[0] = 0;
        break;
    case 0x0a://slti
        write_0(t);
        r[t] = r[s] < C;
        r[0] = 0;
        break;
    case 0x04://beq
        number_overflow(PC*4, 4*C+4, 1);
        PC_overflow();
        if(r[s] == r[t]) PC = PC + C;
        break;
    case 0x05://bne
        number_overflow(PC*4, 4*C+4, 1);
        PC_overflow();
        if(r[s] != r[t]) PC = PC + C;
        break;
    case 0x07://bgtz
        number_overflow(PC*4, 4*C+4, 1);
        PC_overflow();
        if(r[s] > 0) PC = PC + C;
        break;
    default:
        halt = 1;
        printf("illegal instruction found at 0x%08x",PC * 4 - 4);
        break;
    }
}
