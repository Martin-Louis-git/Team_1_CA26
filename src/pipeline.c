#include "../include/pipeline.h"

void fetch(CPU *cpu)
{
    InstructionPacket ip;
    int value = reg_get(&(cpu->pc));
    reg_set(&(cpu->pc), value + 1, PC);
    fetch_decode = &ip;
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
