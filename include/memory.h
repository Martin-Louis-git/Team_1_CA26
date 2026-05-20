#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char mem[2048][33];
} Memory;

char* m_read(Memory *m, int address);
void m_write(Memory *m, int address, char *value);
void m_fill(Memory *m, char encoded[][33], int size);