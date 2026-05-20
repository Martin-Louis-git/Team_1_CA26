#include "../include/memory.h"
#include "../constants.h"

char *m_read(Memory *m, int address)
{
    if (address < MEMORY_SIZE && address >= 0)
    {
        return m->mem[address];
    }
    else
    {
        printf("Error: Address out of bounds\n");
        return NULL;
    }
}

void m_write(Memory *m, int address, char *value)
{
    if (address < MEMORY_SIZE && address >= 1024)
    {
        if (strlen(value) > 33)
        {
            printf("Error: value must be 32 chars or less\n");
            return;
        }
        else
        {
            strncpy(m->mem[address], value, 33);
        }
    }
    else
    {
        printf("Error: Address out of editable bounds\n");
        return;
    }
}

void m_fill(Memory *m, char encoded[][33], int size)
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        if (i < size)
        {
            strncpy(m->mem[i], encoded[i], 33);
        }
        else
        {
            m->mem[i][0] = '\0';
        }
    }
}
