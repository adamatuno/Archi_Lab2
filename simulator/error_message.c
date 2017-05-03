#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

void write_0(unsigned int r){
    if(r == 0){
        w0 = 1;
    }
    else w0 = 0;
}

long long itl(int a){
    long long b = a;
    return b;
}

void number_overflow(int a, int b, int c){/**c=1 add, c=0 multi **/
    long long A = a, B = b;
    if(c && ((a > 0 && b > 0 && a + b <= 0) || (a < 0 && b < 0 && a + b >= 0))) no = 1;
    else if(!c && ((((a > 0 && b < 0) || (a < 0 && b > 0)) && A * B > 0) || (a < 0 && b < 0 && A * B < 0))) no = 1;
    else no = 0;
}

void overwrite_HiLo(int rst){
    if(rst) err_overwrite_HiLo = 0;
    if(err_overwrite_HiLo) hlo = 1;
    else hlo = 0;
    if(!rst) err_overwrite_HiLo = 1;
}

void mem_overflow(int addr, int range){
    if(addr < 0 || addr + range < 0 ||addr > 1023 || addr + range > 1023){
        dmo = 1;
        halt = 1;
        bigError = 1;
    }
    else dmo = 0;
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
        dmm = 1;
        halt = 1;
        bigError = 1;
    }
    else if(!type && C%2 != 0) {
        dmm = 1;
        halt = 1;
        bigError = 1;
    }
    else dmm = 0;
}
