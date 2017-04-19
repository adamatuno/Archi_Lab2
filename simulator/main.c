#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

unsigned int readfile(FILE *f) {
    unsigned int a;
    fread(&a, 4, 1, f);
    return (a&0x000000ff)<<24|(a&0x0000ff00)<<8|(a&0x00ff0000)>>8|(a&0xff000000)>>24;
}

void init() {
    int i;
    unsigned int word;
    halt = 0;
    ii = fopen("iimage.bin", "rb");
    di = fopen("dimage.bin", "rb");
    sn = fopen("snapshot.rpt", "wb");
    err = fopen("error_dump.rpt", "wb");

    err_overwrite_HiLo = 0;
    PCin = PC = readfile(ii) / 4;
    PCl = PC;
    iin = readfile(ii);
    for(i = 0; i < 256; ++i) {
        if(i < PCin + iin && i >= PCin) I[i] = readfile(ii);
        else I[i] = 0x00000000;
    }
    r[29] = rl[29] = rB[29] = spin = readfile(di);
    din = readfile(di);
    for(i = 0; i < din * 4; i += 4) {
        word = readfile(di);
        D[i] = word >> 24;
        D[i + 1] = (word >> 16) & 0x000000ff;
        D[i + 2] = (word >> 8) & 0x000000ff;
        D[i + 3] = word & 0x000000ff;
    }
    for(i = din * 4; i < 1024; ++i) D[i] = 0x00000000;
    for(i = 0; i < 32; ++i) {
        rS[i] = 0;
        if(i != 29) r[i] = rl[i] = rB[i] = 0x00000000;
    }
    Hi = Hil = 0x00000000;
    Lo = Lol = 0x00000000;
    IF = I[PC];
    ID = EX = DM = WB = 0x00000000;
}

void next() {
    IF = IF_next;
    ID = ID_next;
    EX = EX_next;
    DM = DM_next;
    WB = WB_next;
    PC = PC_next;
    ++Cycle;
}

int checkHalt() {
    if(IF == 0xffffffff && ID == 0xffffffff && EX == 0xffffffff && DM == 0xffffffff && WB == 0xffffffff)  return 1;
    else return 0;        
}

int main(){
    int i;
    init();
    cycle_0();
    Cycle = 0;
    while(Cycle <= 500000) {
        WB_stage();
        IF_stage();
        ID_stage();
        EX_stage();
        DM_stage();
        snap(Cycle);
        if(checkHalt()) break;
        next();
    }
return 0;
}