#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *f, *f_out;
int turn = 1;
void print(FILE *f, unsigned int a){
    fwrite(&a, sizeof(int), 1, f);
}
void write_R(unsigned int func, unsigned int s, unsigned int t, unsigned int d, unsigned int C){
unsigned int code = (0x0000003f & func) | ((0x0000001f & C) << 6) | ((0x0000001f & d) << 11) | ((0x0000001f & t) << 16) | ((0x0000001f & s) << 21);
if(turn) code = (code&0x000000ff)<<24|(code&0x0000ff00)<<8|(code&0x00ff0000)>>8|(code&0xff000000)>>24;
print(f_out, code);
}
void write_I(unsigned int op, unsigned int s, unsigned int t, unsigned int C){
unsigned int code = (0x0000ffff & C) | ((0x0000001f & t) << 16) | ((0x0000001f & s) << 21) | ((0x0000003f & op) << 26);
if(turn) code = (code&0x000000ff)<<24|(code&0x0000ff00)<<8|(code&0x00ff0000)>>8|(code&0xff000000)>>24;
print(f_out, code);
}
void write_J(unsigned int op, unsigned int addr){
unsigned int code = (addr & 0x03ffffff) | ((0x0000003f & op) << 26);
if(turn) code = (code&0x000000ff)<<24|(code&0x0000ff00)<<8|(code&0x00ff0000)>>8|(code&0xff000000)>>24;
print(f_out, code);
}
void write(unsigned int code){
if(turn) code = (code&0x000000ff)<<24|(code&0x0000ff00)<<8|(code&0x00ff0000)>>8|(code&0xff000000)>>24;
print(f_out, code);
}

int main(){
f = fopen("mips.rpt","r");
//f = fopen("d.rpt","r");
f_out = fopen("iimage.bin","wb");
//f_out = fopen("dimage.bin","wb");
unsigned int s, t, d, sh, fun, addr, PC, num;
int C;
char op[6];
fscanf(f, "%08x", &PC);
write(PC);
fscanf(f, "%08x", &num);
write(num);
printf("%d\n", PC);
printf("%d\n", num);
int upper = 50;
/**
while(num-- && upper--){
    fscanf(f, "%d", &C);
    write(C);
}
return 0;
**/
while(num-- && upper--){
fscanf(f, "%s", op);
if(0 == strcmp(op, "/*")) { //µù¸Ñ
    num++;
    while(1) {
        fscanf(f, "%s", op);
        if(0 == strcmp(op, "*/")) break;
    }
} else if(0 == strcmp(op, "add")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x20, s, t, d, 0);
} else if(0 == strcmp(op, "addu")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x21, s, t, d, 0);

} else if(0 == strcmp(op, "sub")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x22, s, t, d, 0);

} else if(0 == strcmp(op, "and")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x24, s, t, d, 0);

} else if(0 == strcmp(op, "or")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x25, s, t, d, 0);

} else if(0 == strcmp(op, "xor")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x26, s, t, d, 0);

} else if(0 == strcmp(op, "nor")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x27, s, t, d, 0);

} else if(0 == strcmp(op, "nand")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x28, s, t, d, 0);

} else if(0 == strcmp(op, "slt")){
    fscanf(f, "%d, %d, %d", &d, &s, &t);
    write_R(0x2a, s, t, d, 0);

} else if(0 == strcmp(op, "sll")){
    fscanf(f, "%d, %d, %d", &d, &t, &sh);
    write_R(0x00, 0, t, d, sh);

} else if(0 == strcmp(op, "srl")){
    fscanf(f, "%d, %d, %d", &d, &t, &sh);
    write_R(0x02, 0, t, d, sh);

} else if(0 == strcmp(op, "sra")){
    fscanf(f, "%d, %d, %d", &d, &t, &sh);
    write_R(0x03, s, t, 0, sh);

} else if(0 == strcmp(op, "jr")){
    fscanf(f, "%d", &s);
    write_R(0x08, s, 0, 0, 0);

} else if(0 == strcmp(op, "mult")){
    fscanf(f, "%d, %d", &s, &t);
    write_R(0x18, s, t, 0, 0);

} else if(0 == strcmp(op, "multu")){
    fscanf(f, "%d, %d", &s, &t);
    write_R(0x19, s, t, 0, 0);

} else if(0 == strcmp(op, "mfhi")){
    fscanf(f, "%d", &d);
    write_R(0x10, 0, 0, d, 0);

} else if(0 == strcmp(op, "mflo")){ /**R type finish**/
    fscanf(f, "%d", &d);
    write_R(0x12, 0, 0, d, 0);
} else if(0 == strcmp(op, "addi")){
    fscanf(f, "%d, %d, %d", &t, &s, &C);
    write_I(0x08, s, t, C);
} else if(0 == strcmp(op, "addiu")){
    fscanf(f, "%d, %d, %d", &t, &s, &C);
    write_I(0x09, s, t, C);
} else if(0 == strcmp(op, "lw")){
    fscanf(f, "%d, %d(%d)", &t, &C, &s);
    write_I(0x23, s, t, C);
} else if(0 == strcmp(op, "lh")){
    fscanf(f, "%d, %d(%d)", &t, &C, &s);
    write_I(0x21, s, t, C);
} else if(0 == strcmp(op, "lhu")){
    fscanf(f, "%d, %d(%d)", &t, &C, &s);
    write_I(0x25, s, t, C);
} else if(0 == strcmp(op, "lb")){
    fscanf(f, "%d, %d(%d)", &t, &C, &s);
    write_I(0x20, s, t, C);
} else if(0 == strcmp(op, "lbu")){
    fscanf(f, "%d, %d(%d)", &t, &C, &s);
    write_I(0x24, s, t, C);
} else if(0 == strcmp(op, "sw")){
    fscanf(f, "%d, %d(%d)", &t, &C, &s);
    write_I(0x2b, s, t, C);
} else if(0 == strcmp(op, "sh")){
    fscanf(f, "%d, %d(%d)", &t, &C, &s);
    write_I(0x29, s, t, C);
} else if(0 == strcmp(op, "sb")){
    fscanf(f, "%d, %d(%d)", &t, &C, &s);
    write_I(0x28, s, t, C);
} else if(0 == strcmp(op, "lui")){
    fscanf(f, "%d, %d", &t, &C);
    write_I(0x0f, 0, t, C);
} else if(0 == strcmp(op, "andi")){
    fscanf(f, "%d, %d, %d", &t, &s, &C);
    write_I(0x0c, s, t, C);
} else if(0 == strcmp(op, "ori")){
    fscanf(f, "%d, %d, %d", &t, &s, &C);
    write_I(0x0d, s, t, C);
} else if(0 == strcmp(op, "nori")){
    fscanf(f, "%d, %d, %d", &t, &s, &C);
    write_I(0x0e, s, t, C);
} else if(0 == strcmp(op, "slti")){
    fscanf(f, "%d, %d, %d", &t, &s, &C);
    write_I(0x0a, s, t, C);
} else if(0 == strcmp(op, "beq")){
    fscanf(f, "%d, %d, %d", &s, &t, &C);
    write_I(0x04, s, t, C);
} else if(0 == strcmp(op, "bne")){
    fscanf(f, "%d, %d, %d", &s, &t, &C);
    write_I(0x05, s, t, C);
} else if(0 == strcmp(op, "bgtz")){ /** I type finish**/
    fscanf(f, "%d, %d", &s, &C);
    write_I(0x07, s, 0, C);
} else if(0 == strcmp(op, "halt")){ /** halt **/
    print(f_out, 0xffffffff);
} else if(0 == strcmp(op, "j")){
    fscanf(f, "%d", &addr);
    write_J(0x02, addr);
} else if(0 == strcmp(op, "jal")){
    fscanf(f, "%d", &addr);
    write_J(0x03, addr);
} else if(0 == strcmp(op, "end"))break;
  else {
    break;
  }
}

return 0;
}
