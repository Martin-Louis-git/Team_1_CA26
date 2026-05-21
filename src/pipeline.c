#include <instruction_packet.h>
#include "../include/cpu.h"
#include <stdio.h>
#include <string.h>
#include <pipeline.h>
#include "../include/pipeline.h"
#include "../include/instruction_packet.h"
#include "../include/registers.h"

InstructionPacket *fetch_decode;
InstructionPacket *decode_execute;
InstructionPacket *execute_memory;
InstructionPacket *memory_write_back;

void fetch(CPU *cpu)
{
    if (cpu->clock % 2 == 0)
    {
        return;
    }
    InstructionPacket ip;
    int value = reg_get(&(cpu->pc));
    reg_set(&(cpu->pc), value + 1, PC);
    logger_log(&(cpu->logger), "Fetch instruction: %d", (cpu->pc).value);
    fetch_decode = &ip;
}

void decode(CPU* cpu){

    char bits[33];
    strncpy(bits, fetch_decode->instruction, 32);
    bits[32] = '\0';
    
    unsigned int instruction = (unsigned int)strtol(bits, NULL, 2);

    int op = (instruction) & 0b11110000000000000000000000000000;
    op = op >> 28;
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


    Reg *passR1 = &cpu->registers[r1];
            decode_execute->r1 = passR1;
            Reg *passR2 = &cpu->registers[r2];
            decode_execute->r2 = passR2;
            Reg *passR3 = &cpu->registers[r3];
            decode_execute->r3 = passR3;

    switch(op){
        case(0):
        case(1):
        case(2):
        case(5):
        case(8):
        case(9):
            //R
            decode_execute->type = 'r';
            break;
        case(3):
        case(4):
        case(6):
        case(10):
        case(11):
            //i
            decode_execute->type = 'i';
            break;
        case(7):
            //j
            decode_execute->type = 'j';
            break;
        default:
        break;
    }
}

void execute(CPU *cpu)
{
    InstructionPacket *packet = decode_execute;
    switch (packet->opcode)
    {
    case 0:
        // Add the values in R2 and R3, then store the result in R1
        packet->result = reg_get(packet->r2) + reg_get(packet->r3);
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = 0;
        break;

    case 1:
        // Subtract the value in R3 from R2, then store the result in R1
        packet->result = reg_get(packet->r2) - reg_get(packet->r3);
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = 0;
        break;

    case 2:
        // Multiply the values in R2 and R3, then store the result in R1
        packet->result = reg_get(packet->r2) * reg_get(packet->r3);
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = 0;
        break;

    case 3:
        // Move the immediate value (IMM) directly into R1
        packet->result = packet->immediate;
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = 0;
        break;

    case 4:
        // Compare R1 and R2, and if they are equal, jump by IMM instructions
        if (reg_get(packet->r1) == reg_get(packet->r2))
        {
            packet->result = reg_get(&(cpu->pc)) + packet->immediate;
            packet->write_to_reg = 0;
            packet->write_to_pc = 1;
            packet->mem_read = 0;
            packet->memAddress = 0;

            // CLEAR EVERYTHING BEFORE THAT
            fetch_decode = NULL;
            decode_execute = NULL;
        }
        else
        {
            packet->result = 0; // No jump
            packet->write_to_reg = 0;
            packet->write_to_pc = 0; // boolean 0 or 1
            packet->mem_read = 0;    // int 0 for neither, 1 for load, 2 for store
            packet->memAddress = 0;
        }
        break;

    case 5:
        // Perform bitwise AND between R2 and R3, then store the result in R1
        packet->result = reg_get(packet->r2) & reg_get(packet->r3);
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = 0;
        break;

    case 6:
        // Perform bitwise XOR between R2 and IMM, then store the result in R1
        packet->result = reg_get(packet->r2) ^ packet->immediate;
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = 0;
        break;

    case 7:
        // Jump to the specified address
        packet->result = (reg_get(&(cpu->pc)) & 0xF0000000) | (packet->address & 0x0FFFFFFF);
        ;
        packet->write_to_reg = 0;
        packet->write_to_pc = 1;
        packet->mem_read = 0;
        packet->memAddress = 0;
        // CLEAR EVERYTHING BEFORE THAT
        fetch_decode = NULL;
        decode_execute = NULL;
        break;

    case 8:
        // Shift the value in R2 left by SHAMT bits, then store the result in R1
        packet->result = reg_get(packet->r2) << packet->shamt;
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = 0;
        break;

    case 9:
        // Shift the value in R2 right logically by SHAMT bits, then store the result in R1
        packet->result = reg_get(packet->r2) >> packet->shamt;
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 0; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = 0;
        break;

    case 10:
        // Load data from memory at address (R2 + IMM) into R1
        // packet->result FOR HABASHY TO UPDATE IN MEMORY STAGE
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 1; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = reg_get(packet->r2) + packet->immediate;
        break;

    case 11:
        // Store the value in R1 into memory at address (R2 + IMM)
        packet->result = reg_get(packet->r1);
        packet->write_to_reg = 1;
        packet->write_to_pc = 0;
        packet->mem_read = 2; // int 0 for neither, 1 for load, 2 for store
        packet->memAddress = reg_get(packet->r2) + packet->immediate;
        break;
    }
    execute_memory = packet;
}


void write_back(CPU *cpu)
{
    if (memory_write_back == NULL)
    {
        return;
    }

    logger_log(&(cpu->logger), "Write back: %s", memory_write_back->instruction);

    if (memory_write_back->write_to_reg == 1)
    {
        if (memory_write_back->r1 != NULL)
        {
            int oldValue = reg_get(memory_write_back->r1);
            reg_set(memory_write_back->r1, memory_write_back->result, memory_write_back->r1->regType);
            logger_log(
                &(cpu->logger),
                "Register write: %d -> %d",
                oldValue,
                reg_get(memory_write_back->r1));
        }
        else
        {
            logger_log(&(cpu->logger), "Register write skipped: destination register is NULL");
        }
    }

    if (memory_write_back->write_to_pc == 1)
    {
        int oldPc = reg_get(&(cpu->pc));
        reg_set(&(cpu->pc), memory_write_back->result, PC);
        logger_log(&(cpu->logger), "PC write: %d -> %d", oldPc, reg_get(&(cpu->pc)));
    }

    memory_write_back = NULL;
}

