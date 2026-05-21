#include "../include/pipeline.h"
#include "../include/instruction_packet.h"
void fetch(CPU *cpu)
{
    InstructionPacket ip;
    int value = reg_get(&(cpu->pc));
    reg_set(&(cpu->pc), value + 1, PC);
    fetch_decode = &ip;
}



void execute(CPU *cpu)
{
    InstructionPacket* packet = &decode_execute;
    switch (packet->opcode){
        case 0:
            // Add the values in R2 and R3, then store the result in R1
            packet->result = reg_get(packet->r2) + reg_get(packet->r3);
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =0;
            break;

        case 1:
            // Subtract the value in R3 from R2, then store the result in R1
            packet->result = reg_get(packet->r2) - reg_get(packet->r3);
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =0;
            break;

        case 2:
            // Multiply the values in R2 and R3, then store the result in R1
            packet->result = reg_get(packet->r2) * reg_get(packet->r3);
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =0;
            break;

        case 3:
            // Move the immediate value (IMM) directly into R1
            packet->result = packet->immediate;
            packet->write_to_reg = 1;
            packet->write_to_pc = 0; 
            packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =0;
            break;

        case 4:
            // Compare R1 and R2, and if they are equal, jump by IMM instructions
            if (reg_get(packet->r1) == reg_get(packet->r2)) {
                packet->result = reg_get(&(cpu->pc))+packet->immediate; 
                packet->write_to_reg = 0;
                packet->write_to_pc = 1;  
                packet->mem_read =0;     
                packet->memAddress =0;

                // CLEAR EVERYTHING BEFORE THAT
                fetch_decode = NULL;
                decode_execute = NULL;
            } else {
                packet->result = 0; // No jump
                packet->write_to_reg = 0;
                packet->write_to_pc = 0;  // boolean 0 or 1
                packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
                packet->memAddress =0;
            }    
            break;

        case 5:
            // Perform bitwise AND between R2 and R3, then store the result in R1
            packet->result = reg_get(packet->r2) & reg_get(packet->r3);
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =0;
            break;
            

        case 6:
            // Perform bitwise XOR between R2 and IMM, then store the result in R1
            packet->result = reg_get(packet->r2) ^ packet->immediate;
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =0;
            break;

        case 7:
            // Jump to the specified address
            packet->result = (reg_get(&(cpu->pc)) & 0xF0000000) | (packet->address & 0x0FFFFFFF);; 
            packet->write_to_reg = 0;
            packet->write_to_pc = 1;  
            packet->mem_read =0;     
            packet->memAddress =0;
            // CLEAR EVERYTHING BEFORE THAT
            fetch_decode = NULL;
            decode_execute = NULL;  
            break;

        case 8:
            // Shift the value in R2 left by SHAMT bits, then store the result in R1
            packet->result = reg_get(packet->r2) << packet->shamt;
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =0;
            break;


        case 9:
            // Shift the value in R2 right logically by SHAMT bits, then store the result in R1     
            packet->result = reg_get(packet->r2) >> packet->shamt;
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =0;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =0;
            break;

        case 10:
            // Load data from memory at address (R2 + IMM) into R1
            // packet->result FOR HABASHY TO UPDATE IN MEMORY STAGE
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =1;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =reg_get(packet->r2) + packet->immediate;
            break;
            
        case 11:
            // Store the value in R1 into memory at address (R2 + IMM)
            packet->result = reg_get(packet->r1);
            packet->write_to_reg = 1;
            packet->write_to_pc = 0;  
            packet->mem_read =2;     // int 0 for neither, 1 for load, 2 for store
            packet->memAddress =reg_get(packet->r2) + packet->immediate;
            break;  
    }
    execute_memory = &packet;
}

