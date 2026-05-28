#include "../include/cpu.h"
#include <stdio.h>
#include <string.h>
#include "../include/pipeline.h"
#include "../include/instruction_packet.h"
#include "../include/memory.h"
#include "../include/registers.h"

InstructionPacket *fetch_decode = NULL;
InstructionPacket *decode_execute = NULL;
InstructionPacket *execute_memory = NULL;
InstructionPacket *memory_write_back = NULL;

void fetch(CPU *cpu)
{
    if (cpu->clock % 2 == 0)
    {
        return;
    }

    char *instruction = m_read(&(cpu->memory), reg_get(&(cpu->pc)));

    if (instruction == NULL || instruction[0] == '\0')
    {
        return;
    }

    fetch_decode = malloc(sizeof(InstructionPacket));
    strncpy(fetch_decode->instruction, instruction, 33);

    fetch_decode->instruction[32] = '\0';

    int value = reg_get(&(cpu->pc));

    reg_set(&(cpu->pc), value + 1, PC);

    fetch_decode->instructionNum = value + 1;
    fetch_decode->finished = 1;
    fetch_decode->initialAddress = cpu->registers; // initial memory address of registers
    logger_log(&(cpu->logger), "Fetch instruction: %d.\n", (cpu->pc).value);
}

void decode(CPU *cpu)
{
    if (fetch_decode == NULL || cpu->clock < 2)
    {
        return;
    }

    logger_log(&(cpu->logger), "Decode instruction: %d.\n", fetch_decode->instructionNum);

    if (fetch_decode->finished > 0)
    {
        fetch_decode->finished--;
        return;
    }

    decode_execute = fetch_decode;
    decode_execute->finished = 1;

    char bits[33];
    strncpy(bits, decode_execute->instruction, 33);
    bits[32] = '\0';

    unsigned int instruction = (unsigned int)strtoul(bits, NULL, 2);

    unsigned int op =
        ((unsigned int)instruction & 0xF0000000) >> 28;
    decode_execute->opcode = op;

    int r1 = (instruction) & 0b00001111100000000000000000000000;
    r1 = r1 >> 23;
    int r2 = (instruction) & 0b00000000011111000000000000000000;
    r2 = r2 >> 18;
    int r3 = (instruction) & 0b00000000000000111110000000000000;
    r3 = r3 >> 13;
    int sh = (instruction) & 0b00000000000000000001111111111111;
    decode_execute->shamt = sh;

    int im = (instruction) & 0b00000000000000111111111111111111;
    decode_execute->immediate = im;
    int ad = (instruction) & 0b00001111111111111111111111111111;
    decode_execute->memAddress = ad;

    Reg *passR1 = &(cpu->registers[r1]);
    decode_execute->r1 = passR1;
    Reg *passR2 = &(cpu->registers[r2]);
    decode_execute->r2 = passR2;
    Reg *passR3 = &(cpu->registers[r3]);
    decode_execute->r3 = passR3;
    switch (op)
    {
    case (0):
    case (1):
    case (2):
    case (5):
    case (8):
    case (9):
        // R
        decode_execute->type = 'r';
        break;
    case (3):
    case (4):
    case (6):
    case (10):
    case (11):
        // i
        decode_execute->type = 'i';
        break;
    case (7):
        // j
        decode_execute->type = 'j';
        break;
    default:
        break;
    }
    fetch_decode = NULL;
}

void execute(CPU *cpu)
{

    if (decode_execute == NULL || cpu->clock < 4)
    {
        return;
    }

    logger_log(&(cpu->logger), "Execute instruction: %d.\n", decode_execute->instructionNum);

    if (decode_execute->finished > 0)
    {
        decode_execute->finished--;
        return;
    }

    execute_memory = decode_execute;
    execute_memory->finished = 1;
    switch (execute_memory->opcode)
    {
    case 0:
        // Add the values in R2 and R3, then store the result in R1
        execute_memory->result = reg_get(execute_memory->r2) + reg_get(execute_memory->r3);
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = 0;
        break;

    case 1:
        // Subtract the value in R3 from R2, then store the result in R1
        execute_memory->result = reg_get(execute_memory->r2) - reg_get(execute_memory->r3);
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = 0;
        break;

    case 2:
        // Multiply the values in R2 and R3, then store the result in R1
        execute_memory->result = reg_get(execute_memory->r2) * reg_get(execute_memory->r3);
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = 0;
        break;

    case 3:
        // Move the immediate value (IMM) directly into R1
        execute_memory->result = execute_memory->immediate;
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = 0;
        break;

    case 4:
        // Compare R1 and R2, and if they are equal, jump by IMM instructions
        if (reg_get(execute_memory->r1) == reg_get(execute_memory->r2))
        {
            execute_memory->result = reg_get(&(cpu->pc)) + execute_memory->immediate;
            execute_memory->write_to_reg = 0;
            execute_memory->write_to_pc = 1;
            execute_memory->mem_read = 0;
            execute_memory->memAddress = 0;

            // CLEAR EVERYTHING BEFORE THAT
            fetch_decode = NULL;
            decode_execute = NULL;
        }
        else
        {
            execute_memory->result = 0; // No jump
            execute_memory->write_to_reg = 0;
            execute_memory->write_to_pc = 0; // boolean 0 or 1
            execute_memory->mem_read = 0;    // int 0 for neither, 1 for load, 2 for store
            execute_memory->memAddress = 0;
        }
        break;

    case 5:
        // Perform bitwise AND between R2 and R3, then store the result in R1
        execute_memory->result = reg_get(execute_memory->r2) & reg_get(execute_memory->r3);
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = 0;
        break;

    case 6:
        // Perform bitwise XOR between R2 and IMM, then store the result in R1
        execute_memory->result = reg_get(execute_memory->r2) ^ execute_memory->immediate;
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = 0;
        break;

    case 7:
        // Jump to the specified address
        execute_memory->result = (reg_get(&(cpu->pc)) & 0xF0000000) | (execute_memory->address & 0x0FFFFFFF);
        ;
        execute_memory->write_to_reg = 0;
        execute_memory->write_to_pc = 1;
        execute_memory->mem_read = 0;
        execute_memory->memAddress = 0;
        // CLEAR EVERYTHING BEFORE THAT
        fetch_decode = NULL;
        decode_execute = NULL;
        break;

    case 8:
        // Shift the value in R2 left by SHAMT bits, then store the result in R1
        execute_memory->result = reg_get(execute_memory->r2) << execute_memory->shamt;
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = 0;
        break;

    case 9:
        // Shift the value in R2 right logically by SHAMT bits, then store the result in R1
        execute_memory->result = reg_get(execute_memory->r2) >> execute_memory->shamt;
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = 0;
        break;

    case 10:
        // Load data from memory at address (R2 + IMM) into R1
        // execute_memory->result FOR HABASHY TO UPDATE IN MEMORY STAGE
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 1; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = reg_get(execute_memory->r2) + execute_memory->immediate;
        break;

    case 11:
        // Store the value in R1 into memory at address (R2 + IMM)
        execute_memory->result = reg_get(execute_memory->r1);
        execute_memory->write_to_reg = 1;
        execute_memory->write_to_pc = 0;
        execute_memory->mem_read = 2; // int 0 for neither, 1 for load, 2 for store
        execute_memory->memAddress = reg_get(execute_memory->r2) + execute_memory->immediate;
        break;
    }
    decode_execute = NULL;
}

void memory(CPU *cpu)
{
    if (execute_memory == NULL || cpu->clock % 2 != 0)
        return;

    if (execute_memory->mem_read == 1)
    {
        char *val = m_read(&(cpu->memory),
                           execute_memory->memAddress);

        if (val != NULL && val[0] != '\0')
        {
            execute_memory->result =
                (int)strtol(val, NULL, 2);

            logger_log(&(cpu->logger),
                       "Memory read at address %d: %d.\n",
                       execute_memory->memAddress,
                       execute_memory->result);
        }
        else
        {
            execute_memory->result = 0;
        }
    }

    else if (execute_memory->mem_read == 2)
    {
        char binary[33];
        int val = execute_memory->result;

        for (int i = 31; i >= 0; i--)
        {
            binary[31 - i] =
                ((val >> i) & 1) ? '1' : '0';
        }

        binary[32] = '\0';

        m_write(&(cpu->memory),
                execute_memory->memAddress,
                binary);

        logger_log(&(cpu->logger),
                   "Memory write at address %d: %d.\n",
                   execute_memory->memAddress,
                   execute_memory->result);

        logger_log(&(cpu->logger), "Memory instruction: %d.\n",
                   execute_memory->instructionNum);
    }

    memory_write_back = execute_memory;
    execute_memory = NULL;
}

int write_back(CPU *cpu)
{
    if (memory_write_back == NULL)
    {
        return 1;
    }

    if (memory_write_back->write_to_reg == 1)
    {
        if (memory_write_back->r1 != NULL)
        {
            int oldValue = reg_get(memory_write_back->r1);
            reg_set(memory_write_back->r1, memory_write_back->result, memory_write_back->r1->regType);
            logger_log(
                &(cpu->logger),
                "R%d old value: %d -> new value: %d.\n",
                (int)(memory_write_back->r1 - memory_write_back->initialAddress),
                oldValue,
                reg_get(memory_write_back->r1));
        }
        else
        {
            logger_log(&(cpu->logger), "Register write skipped: destination register is NULL.\n");
        }
    }

    if (memory_write_back->write_to_pc == 1)
    {
        int oldPc = reg_get(&(cpu->pc));
        reg_set(&(cpu->pc), memory_write_back->result, PC);
        logger_log(&(cpu->logger), "PC old Value: %d -> PC new Value %d.\n", oldPc, reg_get(&(cpu->pc)));
    }

    logger_log(&(cpu->logger), "Write back Instruction: %d.\n", memory_write_back->instructionNum);
    memory_write_back = NULL;

    if (fetch_decode == NULL && decode_execute == NULL && execute_memory == NULL)
    {
        return 0;
    }
    return 1;
}
