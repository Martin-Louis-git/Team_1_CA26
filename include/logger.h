#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "registers.h"

typedef struct
{
    char log[100][256];
    int size;
} Logger;

void logger_log(Logger *logger, const char *format, ...);
void logger_save_memory(Memory *memory, const char *filename);
void logger_save_registers(Reg *registers, Reg *pc, const char *filename);
void logger_print_log(Logger *logger);