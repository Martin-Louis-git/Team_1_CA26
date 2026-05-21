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

    cpu.pc = reg_new(0, PC);
    for (int i = 0; i < 32; i++)
    {
        if (i == 0)
        {
            cpu.registers[i] = reg_new(0, ZERO);
        }
        else
        {
            cpu.registers[i] = reg_new(0, GPRS);
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

    while (m_read(&(cpu->memory), reg_get(&(cpu->pc))) != NULL && m_read(&(cpu->memory), reg_get(&(cpu->pc)))[0] != '\0')
    {
        (cpu->clock)++;
        logger_log(&(cpu->logger), "At Clock %d, ", cpu->clock);
        // write_back(&cpu); // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        // memory(&cpu);     // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        // execute(&cpu);    // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        // decode(&cpu);     // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        fetch(cpu); // logs current instructions and registers (before and after execution) and memory (when changed) when allowed and instruction exists
        logger_print_log(&(cpu->logger));
    }

    logger_print_memory(&(cpu->memory));
}