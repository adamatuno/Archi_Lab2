#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

void newIF(int pc) {
    if(pc >= 0 && pc < 1024) IF_next = I[pc];
    else halt = 1;
}

void IF_stage(){
    if(!stalled && !flushed){
        PC_next = PC + 1;
        newIF(PC_next);
    }
}