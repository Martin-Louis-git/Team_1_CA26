#pragma once
#include "registers.h"
typedef struct
{
    // fetch stage
    int instructionNum;
    char instruction[33];

    // decode stage
    int opcode;
    Reg *r1;
    Reg *r2;
    Reg *r3;
    char type;
    int immediate;
    int shamt;
    int address; // for load/store instructions

    // execute stage
    int result;
    int write_to_reg; // boolean 0 or 1
    int write_to_pc;  // boolean 0 or 1
    int mem_read;     // int 0 for neither, 1 for load, 2 for store
    int memAddress;

    int finished;
    Reg *initialAddress;
} InstructionPacket;