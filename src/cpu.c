#include <string.h>
#include "../include/cpu.h"

void loadMemory(CPU *cpu, char encodedInstructions[][ENCODED_INSTRUCTION_LENGTH], int instructionCount)
{
    if (instructionCount <= 0)
        return;

    int linesToLoad = instructionCount;

    //if (linesToLoad > MAX_INSTRUCTIONS)
    //    linesToLoad = MAX_INSTRUCTIONS;

    if (linesToLoad > INSTRUCTION_MEMORY_SIZE)
        linesToLoad = INSTRUCTION_MEMORY_SIZE;

    for (int i = 0; i < linesToLoad; i++)
        strcpy(cpu->memory[i], encodedInstructions[i]);

    strcpy(cpu->pc, cpu->memory[0]);
}

CPU createCPU(char encodedInstructions[][ENCODED_INSTRUCTION_LENGTH], int instructionCount)
{
    CPU cpu;

    memset(cpu.registers, 0, sizeof(cpu.registers));
    memset(cpu.pc, 0, sizeof(cpu.pc));
    cpu.clock = 0;
    memset(cpu.memory, 0, sizeof(cpu.memory));

    loadMemory(&cpu, encodedInstructions, instructionCount);

    return cpu;
}
