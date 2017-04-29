#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

void write_0(unsigned int r){
    if(r == 0){
        w0 = Cycle + 3;
    }
}

long long itl(int a){
    long long b = a;
    return b;
}

void number_overflow(int a, int b, int c){/**c=1 add, c=0 multi **/
    long long A = a, B = b;
    if(c && ((a > 0 && b > 0 && a + b <= 0) || (a < 0 && b < 0 && a + b >= 0)))
    no = Cycle + 1;
    if(!c && ((((a > 0 && b < 0) || (a < 0 && b > 0)) && A * B > 0) || (a < 0 && b < 0 && A * B < 0)))
    no = Cycle + 1;
}

void overwrite_HiLo(int rst){
    if(rst) err_overwrite_HiLo = 0;
    if(err_overwrite_HiLo) hlo = Cycle + 1;
    if(!rst) err_overwrite_HiLo = 1;
}

void mem_overflow(int addr, int range){
    if(addr < 0 || addr + range < 0 ||addr > 1023 || addr + range > 1023){
        dmo = Cycle + 2;
        halt = 1;
        bigError = 1;
    }
}

int mem_out(int addr, int range){
    if(addr < 0 || addr + range < 0 ||addr > 1023 || addr + range > 1023){
        halt = 1;
        bigError = 1;
        return 1;
    }
    return 0;
}

void PC_overflow(){
    if(PC < 0 || PC >= 256){
        halt = 1;
        bigError = 1;
    }
}

void data_misaligned(int C, int type) { /**type=1 word, type=0 half**/
    if(type && C%4 != 0) {
        dmm = Cycle + 2;
        halt = 1;
        bigError = 1;
    }
    if(!type && C%2 != 0) {
        dmm = Cycle + 2;
        halt = 1;
        bigError = 1;
    }
}
