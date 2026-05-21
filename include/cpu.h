#pragma once

#include "../constants.h"
#include "registers.h"
#include "memory.h"
#include "logger.h"

typedef struct CPU
{
    Reg registers[32];
    Reg pc;
    int clock;
    Memory memory;
    Logger logger;
} CPU;

CPU createCPU(char encodedInstructions[][ENCODED_INSTRUCTION_LENGTH], int instructionCount);
void loadMemory(CPU *cpu, char encodedInstructions[][ENCODED_INSTRUCTION_LENGTH], int instructionCount);
void run(CPU *cpu);