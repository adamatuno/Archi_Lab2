#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"
void cycle_0() {
    int i;
    printReg = -1;
    printHi = printLo = 0;
    w0_l = w0 = hlo_l = hlo = no_l = no = dmm = dmo = 0;
    messageReset();
    fprintf(sn, "cycle 0\n");
    for(i = 0; i < 32; ++i) fprintf(sn, "$%02d: 0x%08X\n", i, r[i]);
    fprintf(sn, "$HI: 0x00000000\n$LO: 0x00000000\n");
}

void snap(int cycle) {
    int i;
    if(Cycle != 0) fprintf(sn, "cycle %d\n", cycle);

    if(printReg > -1) {
        fprintf(sn, "$%02d: 0x%08X\n",printReg , rl[printReg]);
        printReg = -1;
    }
    if(printHi) {
        fprintf(sn, "$HI: 0x%08X\n", Hil);
        printHi = 0;
    }
    if(printLo) {
        fprintf(sn, "$LO: 0x%08X\n", Lol);
        printLo = 0;
    }
    for(i = 0; i < 32; ++i) {
        if(r[i] != rl[i]) {
            printReg = i;
            rl[i] = r[i];
        }
    }
    if(Hi != Hil) {
        printHi = 1;
        Hil = Hi;
    }
    if(Lo != Lol) {
        printLo = 1;
        Lol = Lo;
    }
    fprintf(sn, "PC: 0x%08X\n", PC * 4);
    fprintf(sn, "IF: 0x%08X", IF);
    printfIFMessage();
    fprintf(sn, "ID: ");
    printfMIPS(ID);
    printfIDMessage();
    fprintf(sn, "EX: ");
    printfMIPS(EX);
    printfEXMessage();
    fprintf(sn, "DM: ");
    printfMIPS(DM);
    fprintf(sn, "\n");
    fprintf(sn, "WB: ");
    printfMIPS(WB);
    fprintf(sn, "\n\n\n");
    messageReset();
}


void writeError_small() {
    if(w0_l) {
        fprintf(err, "In cycle %d: Write $0 Error\n", Cycle);
    }
    if(hlo_l) {
        fprintf(err, "In cycle %d: Overwrite HI-LO registers\n", Cycle);
    }
    if(no_l) {
        fprintf(err, "In cycle %d: Number Overflow\n", Cycle);
    }
    w0_l = w0;
    hlo_l = hlo;
    no_l = no;
    w0 = 0;
    hlo = 0;
    no = 0;
}

void writeError_big() {
    if(dmo) {
        fprintf(err, "In cycle %d: Address Overflow\n", Cycle + 1);
        bigError = 1;
    }
    if(dmm) {
        fprintf(err, "In cycle %d: Misalignment Error\n", Cycle + 1);
        bigError = 1;
    }
}

void messageReset() {
    stalled = 0;
    EXtoID = EXtoEX = DMtoEX = -1;
    EXtoID_case = EXtoEX_case = DMtoEX_case = 0;
}

void printfIFMessage() {
    if(stalled) fprintf(sn, " to_be_stalled");
    if(flushed) fprintf(sn, " to_be_flushed");
    fprintf(sn, "\n");
}

void printfIDMessage() {
    if(stalled) fprintf(sn, " to_be_stalled");
    if(EXtoID > -1 && EXtoID_case == 1) fprintf(sn, " fwd_EX-DM_rs_$%d", EXtoID);
    if(EXtoID > -1 && EXtoID_case == 2) fprintf(sn, " fwd_EX-DM_rt_$%d", EXtoID);
    if(EXtoID > -1 && EXtoID_case == 3) fprintf(sn, " fwd_EX-DM_rs_$%d fwd_EX-DM_rt_$%d", EXtoID, EXtoID);
    fprintf(sn, "\n");
}

void printfEXMessage() {
    if(EXtoEX > -1 && EXtoEX_case == 1) fprintf(sn, " fwd_EX-DM_rs_$%d", EXtoEX);
    if(DMtoEX > -1 && DMtoEX_case == 1) fprintf(sn, " fwd_DM-WB_rs_$%d", DMtoEX);
    if(EXtoEX > -1 && EXtoEX_case == 2) fprintf(sn, " fwd_EX-DM_rt_$%d", EXtoEX);
    if(DMtoEX > -1 && DMtoEX_case == 2) fprintf(sn, " fwd_DM-WB_rt_$%d", DMtoEX);

    if(EXtoEX > -1 && EXtoEX_case == 3) fprintf(sn, " fwd_EX-DM_rs_$%d fwd_EX-DM_rt_$%d", EXtoEX, EXtoEX);
    if(DMtoEX > -1 && DMtoEX_case == 3) fprintf(sn, " fwd_DM-WB_rs_$%d fwd_DM-WB_rt_$%d", DMtoEX, DMtoEX);
    fprintf(sn, "\n");
}

void de(int a, int b) {
    printf("Cycle: %d, %d, %d\n", Cycle, a, b);
}

void printfMIPS(unsigned int code) {
    unsigned int op = get_op(code), fun = get_func(code);
    if(type(op) == 'R') {
        switch(fun){
            case 0x20://add
                fprintf(sn, "ADD");
                break;
            case 0x21://addu
                fprintf(sn, "ADDU");
                break;
            case 0x22://sub
                fprintf(sn, "SUB");
                break;
            case 0x24://and
                fprintf(sn, "AND");
                break;
            case 0x25://or
                fprintf(sn, "OR");
                break;
            case 0x26://xor
                fprintf(sn, "XOR");
                break;
            case 0x27://nor
                fprintf(sn, "NOR");
                break;
            case 0x28://nand
                fprintf(sn, "NAND");
                break;
            case 0x2a://slt
                fprintf(sn, "SLT");
                break;
            case 0x00://sll or nop
                if(get_rt(code) == 0 && get_rd(code) == 0 && get_sha(code) == 0) fprintf(sn, "NOP");//nop
                else fprintf(sn, "SLL"); // sll
                break;
            case 0x02://srl
                fprintf(sn, "SRL");
                break;
            case 0x03://sra
                fprintf(sn, "SRA");
                break;
            case 0x08://jr
                fprintf(sn, "JR");
                break;
            case 0x18:///mult
                fprintf(sn, "MULT");
                break;
            case 0x19:///multu
                fprintf(sn, "MULTU");
                break;
            case 0x10://mfhi
                fprintf(sn, "MFHI");
                break;
            case 0x12://mflo
                fprintf(sn, "MFLO");
                break;
            default:
                break;
            }
    }
    else if(type(op) == 'I') {
        switch(op){
            case 0x08://addi
                fprintf(sn, "ADDI");
                break;
            case 0x09://addiu
                fprintf(sn, "ADDIU");
                break;
            case 0x23://lw
                fprintf(sn, "LW");
                break;
            case 0x21://lh
                fprintf(sn, "LH");
                break;
            case 0x25://lhu
                fprintf(sn, "LHU");
                break;
            case 0x20://lb
                fprintf(sn, "LB");
                break;
            case 0x24://lbu
                fprintf(sn, "LBU");
                break;
            case 0x2b://sw
                fprintf(sn, "SW");
                break;
            case 0x29://sh
                fprintf(sn, "SH");
                break;
            case 0x28://sb
                fprintf(sn, "SB");
                break;
            case 0x0f:///lui
                fprintf(sn, "LUI");
                break;
            case 0x0c:///andi
                fprintf(sn, "ANDI");
                break;
            case 0x0d:///ori
                fprintf(sn, "ORI");
                break;
            case 0x0e:///nori
                fprintf(sn, "NORI");
                break;
            case 0x0a://slti
                fprintf(sn, "SLTI");
                break;
            case 0x04://beq
                fprintf(sn, "BEQ");
                break;
            case 0x05://bne
                fprintf(sn, "BNE");
                break;
            case 0x07://bgtz
                fprintf(sn, "BGTZ");
                break;
            default: //wrong
                break;
            }
    }
    else {
        switch(op){
            case 0x02://j
                fprintf(sn, "J");
                break;
            case 0x03://jal
                fprintf(sn, "JAL");
                break;
            case 0x3f://halt
                fprintf(sn, "HALT");
                break;
            default:
                break;
        }
    }
}
