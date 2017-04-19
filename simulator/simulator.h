#include <stdio.h>
#include <stdlib.h>

fpos_t pos;
int r[32], rl[32], Cycle, err_overwrite_HiLo, rS[32], rB[32];
int stalled, flushed, EXtoID, EXtoID_case, EXtoEX, EXtoEX_case, DMtoEX, DMtoEX_case;
unsigned int Hi, Hil, Lo, Lol, PC, PCin, PCl, D[1024], I[256], iin, din, halt, spin;
unsigned int IF, ID, EX, DM, WB, IF_next, ID_next, EX_next, DM_next, WB_next, PC_next, mem_addr;
FILE *ii, *di, *sn, *err;
//decode
unsigned int get_op(unsigned int i);
unsigned int get_rs(unsigned int i);
unsigned int get_rt(unsigned int i);
unsigned int get_rd(unsigned int i);
unsigned int get_sha(unsigned int i);
unsigned int get_func(unsigned int i);
int get_imm(unsigned int i);
int get_addr(unsigned int i);
char type(unsigned int op);
//stages
void newIF();
void IF_stage();
void ID_stage();
void EX_stage();
void CheckForward();
void REX();
void IEX();
void JSEX();
void DM_stage();
void WB_stage();
//error
void write_0(unsigned int r);
long long itl(int a);
void number_overflow(int a, int b, int c);
void overwrite_HiLo(int rst);
void mem_overflow(int addr, int range);
int mem_out(int addr, int range);
void data_misaligned(int C, int type);
void PC_overflow();
//output
void cycle_0();
void snap(int cycle);
void messageReset();
void printfIFMessage();
void printfIDMessage();
void printfEXMessage();
void printfMIPS(unsigned int code);

