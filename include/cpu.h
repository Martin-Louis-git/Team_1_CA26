#pragma once

#include "../constants.h"

typedef struct CPU
{
    int registers[32];
    char pc[ENCODED_INSTRUCTION_LENGTH];
    int clock;
    char memory[MEMORY_SIZE][ENCODED_INSTRUCTION_LENGTH];
} CPU;

CPU createCPU(char encodedInstructions[][ENCODED_INSTRUCTION_LENGTH], int instructionCount);
void loadMemory(CPU *cpu, char encodedInstructions[][ENCODED_INSTRUCTION_LENGTH], int instructionCount);
