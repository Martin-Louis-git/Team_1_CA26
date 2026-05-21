#pragma once

#include "cpu.h"
#include "instruction_packet.h"

InstructionPacket *fetch_decode;
InstructionPacket *decode_execute;
InstructionPacket *execute_memory;
InstructionPacket *memory_write_back;

void fetch(CPU *cpu);
void decode(CPU *cpu);
void execute(CPU *cpu);
void memory(CPU *cpu);
void write_back(CPU *cpu);