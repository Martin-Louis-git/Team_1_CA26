#include "../include/pipeline.h"

void fetch(CPU *cpu)
{
    InstructionPacket ip;
    int value = reg_get(&(cpu->pc));
    reg_set(&(cpu->pc), value + 1, PC);
    fetch_decode = &ip;
}