#include "../include/logger.h"
#include <stdio.h>
#include <stdarg.h>

void logger_log(Logger *logger, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    vsnprintf(
        logger->log[logger->size],
        sizeof(logger->log[logger->size]),
        format,
        args);

    va_end(args);

    logger->size++;
}

void logger_print_memory(Memory *memory)
{
    for (int i = 0; i < 2048; i++)
    {
        printf("Memory Location %d: %s\n", (i + 1), memory->mem[i]);
    }
}

void logger_print_log(Logger *logger)
{
    for (int i = logger->size - 1; i >= 0; i--)
    {
        printf("%s", logger->log[i]);
    }
    printf("\n");
    logger->size = 0;
}