#include "../include/memory.h"

char* m_read(Memory *m, int address) {
    if (address < 2048 && address >= 0) {
        return m->mem[address];
    } else {
        printf("Error: Address out of bounds\n");
        return NULL;
    }
}

void m_write(Memory *m, int address, char *value) {
    if (address < 2048 && address >= 1024) {
        if (strlen(value) > 32) {
            printf("Error: value must be 32 chars or less\n");
            return;
        } else {
            strncpy(m->mem[address], value, 32);
            m->mem[address][32] = '\0';
        }
    } else {
        printf("Error: Address out of editable bounds\n");
        return;
    }
}

void m_fill(Memory *m, char encoded[][33], int size) {
    for (int i = 0; i < size; i++) {
        strncpy(m->mem[i], encoded[i], 32);
        m->mem[i][32] = '\0';
    }
}


