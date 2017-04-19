#include <stdio.h>
#include <stdlib.h>
FILE *ii, *di, *iid, *did;
fpos_t pos;
unsigned int readfile(int rst, FILE *f) {
    if(rst) pos = 0;
    unsigned int a;
    fsetpos(f, &pos);
    fread(&a, 4, 1, f);
    pos += 4;
    return (a&0x000000ff)<<24|(a&0x0000ff00)<<8|(a&0x00ff0000)>>8|(a&0xff000000)>>24;
}
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

void Rti(unsigned int func, unsigned int s, unsigned int t, unsigned int d, unsigned int C){
    long long t1, t2, temp;
    unsigned int sign;
    int n;
    switch(func){
    case 0x20:///add
        fprintf(iid, "add %d, %d, %d\n", d, s, t);
        break;
    case 0x21:///addu
        fprintf(iid, "addu %d, %d, %d\n", d, s, t);
        break;
    case 0x22:///sub
        fprintf(iid, "sub %d, %d, %d\n", d, s, t);
        break;
    case 0x24://and
        fprintf(iid, "and %d, %d, %d\n", d, s, t);
        break;
    case 0x25://or
        fprintf(iid, "or %d, %d, %d\n", d, s, t);
        break;
    case 0x26://xor
        fprintf(iid, "xor %d, %d, %d\n", d, s, t);
        break;
    case 0x27://nor
        fprintf(iid, "nor %d, %d, %d\n", d, s, t);
        break;
    case 0x28://nand
        fprintf(iid, "nand %d, %d, %d\n", d, s, t);
        break;
    case 0x2a://slt
        fprintf(iid, "slt %d, %d, %d\n", d, s, t);
        break;
    case 0x00://sll
        fprintf(iid, "sll %d, %d, %d\n", d, t, C);
        break;
    case 0x02://srl
        fprintf(iid, "srl %d, %d, %d\n", d, t, C);
        break;
    case 0x03://sra
        fprintf(iid, "sra %d, %d, %d\n", d, t, C);
        break;
    case 0x08://jr
        fprintf(iid, "jr %d\n", s);
        break;
    case 0x18:///mult
        fprintf(iid, "mult %d, %d\n", s, t);
        break;
    case 0x19:///multu
        fprintf(iid, "multu %d, %d\n", s, t);
        break;
    case 0x10://mfhi
        fprintf(iid, "mfhi %d\n", d);
        break;
    case 0x12://mflo
        fprintf(iid, "mflo %d\n", d);
        break;
    default:
        printf("err\n");
        break;
    }

}

void Iti(unsigned int op, unsigned int s, unsigned int t, int C){
    switch(op){
    case 0x08://addi
        fprintf(iid, "addi %d, %d, %d\n", t, s, C);
        break;
    case 0x09://addiu
        fprintf(iid, "addiu %d, %d, %d\n", t, s, C);
        break;
    case 0x23://lw
        fprintf(iid, "lw %d, %d(%d)\n", t, C, s);
        break;
    case 0x21://lh
        fprintf(iid, "lh %d, %d(%d)\n", t, C, s);
        break;
    case 0x25://lhu
        fprintf(iid, "lhu %d, %d(%d)\n", t, C, s);
        break;
    case 0x20://lb
        fprintf(iid, "lb %d, %d(%d)\n", t, C, s);
        break;
    case 0x24://lbu
        fprintf(iid, "lbu %d, %d(%d)\n", t, C, s);
        break;
    case 0x2b://sw
        fprintf(iid, "sw %d, %d(%d)\n", t, C, s);
        break;
    case 0x29://sh
        fprintf(iid, "sh %d, %d(%d)\n", t, C, s);
        break;
    case 0x28://sb
        fprintf(iid, "sb %d, %d(%d)\n", t, C, s);
        break;
    case 0x0f:///lui
        fprintf(iid, "lui %d, %d\n", t, C);
        break;
    case 0x0c:///andi
        fprintf(iid, "andi %d, %d, %d\n", t, s, C);
        break;
    case 0x0d:///ori
        fprintf(iid, "ori %d, %d, %d\n", t, s, C);
        break;
    case 0x0e:///nori
        fprintf(iid, "nori %d, %d, %d\n", t, s, C);
        break;
    case 0x0a://slti
        fprintf(iid, "slti %d, %d, %d\n", t, s, C);
        break;
    case 0x04://beq
        fprintf(iid, "beq %d, %d, %d\n", t, s, C);
        break;
    case 0x05://bne
        fprintf(iid, "bne %d, %d, %d\n", t, s, C);
        break;
    case 0x07://bgtz
        fprintf(iid, "bgtz %d, %d\n", s, C);
        break;
    default: //wrong
        printf("err\n");
        break;
    }
}

void JSti(unsigned int op, unsigned C){
    switch(op){
    case 0x02://j
        fprintf(iid, "j %d\n", C);
        break;
    case 0x03://jal
        fprintf(iid, "jal %d\n", C);
        break;
    case 0x3f://halt
        fprintf(iid, "halt\n");
        break;
    default:
        printf("err\n");
        break;
    }
}

int main() {
    int i;
    unsigned int code, PC, iin;
    ii = fopen("iimage.bin", "r");
    iid = fopen("mips_out.rpt", "w");

    PC = readfile(1, ii);
    fprintf(iid, "%08x\n", PC);
    iin = readfile(0, ii);
    fprintf(iid, "%08x\n", iin);
    printf("PC: %08x, num: %d",PC,iin);
    for(i = 0; i < iin; ++i){
        code = readfile(0, ii);
        switch(type(get_op(code))) {
        case 'R':
            Rti(get_func(code), get_rs(code), get_rt(code), get_rd(code), get_sha(code));
            break;
        case 'J':
            JSti(get_op(code), get_addr(code));
            break;
        default:
            Iti(get_op(code), get_rs(code), get_rt(code), get_imm(code));
            break;
    }
    }
    return 0;
}
