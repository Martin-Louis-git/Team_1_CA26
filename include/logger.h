#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

typedef struct
{
    char log[100][256];
    int size;
} Logger;

void logger_log(Logger *logger, const char *format, ...);
void logger_print_memory(Memory *memory);
void logger_print_log(Logger *logger);