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
    int loop = 1;
    while (loop)
    {
        (cpu->clock)++;
        loop = write_back(cpu);
        memory(cpu);
        execute(cpu);
        decode(cpu);
        fetch(cpu);
        logger_log(&(cpu->logger), "At Clock %d:\n", cpu->clock);
        logger_print_log(&(cpu->logger));
    }

    logger_save_memory(&(cpu->memory), "IO/output_memory.txt");
    logger_save_registers(cpu->registers, &cpu->pc, "IO/output_registers.txt");
}