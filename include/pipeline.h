#pragma once

#include "cpu.h"
#include "instruction_packet.h"

extern InstructionPacket *fetch_decode;
extern InstructionPacket *decode_execute;
extern InstructionPacket *execute_memory;
extern InstructionPacket *memory_write_back;

void fetch(CPU *cpu);
void decode(CPU *cpu);
void execute(CPU *cpu);
void memory(CPU *cpu);
int write_back(CPU *cpu);