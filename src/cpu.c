#include <string.h>
#include <stdio.h>
#include "../include/cpu.h"
#include "../include/memory.h"
#include "../include/registers.h"
#include "../include/pipeline.h"
#include "../include/logger.h"

void loadMemory(CPU *cpu, char encodedInstructions[][ENCODED_INSTRUCTION_LENGTH], int instructionCount)
{
    if (instructionCount <= 0)
        return;

    int linesToLoad = instructionCount;

    if (linesToLoad > INSTRUCTION_MEMORY_SIZE)
        linesToLoad = INSTRUCTION_MEMORY_SIZE;

    m_fill(&(cpu->memory), encodedInstructions, linesToLoad);
}

CPU createCPU(char encodedInstructions[][ENCODED_INSTRUCTION_LENGTH], int instructionCount)
{
    CPU cpu;

    char zeroValue[33] = "00000000000000000000000000000000";
    cpu.pc = reg_new(zeroValue, PC);
    for (int i = 0; i < 32; i++)
    {
        if (i == 0)
        {
            cpu.registers[i] = reg_new(zeroValue, ZERO);
        }
        else
        {
            cpu.registers[i] = reg_new(zeroValue, GPRS);
        }
    }
    cpu.clock = 0;
    cpu.logger.size = 0;

    loadMemory(&cpu, encodedInstructions, instructionCount);

    return cpu;
}

void run(CPU *cpu)
{
    logger_print_memory(&(cpu->memory));

    while (1)
    {
        (cpu->clock)++;
        logger_log(&(cpu->logger), "%d", cpu->clock);
        write_back(); // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        memory();     // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        execute();    // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        decode();     // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        fetch();      // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        logger_print(&(cpu->logger));
    }

    logger_print_memory(&(cpu->memory));
}