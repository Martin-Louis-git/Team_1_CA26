#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    // Add fields as needed
} Logger;

Logger logger_new();
void logger_log(Logger *logger);
void logger_print_memory(Logger *logger);