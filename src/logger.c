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

void logger_save_memory(Memory *memory, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    for (int i = 0; i < 2048; i++)
    {
        fprintf(file, "%d: %s\n", i, memory->mem[i]);
    }

    fclose(file);
}

void logger_save_registers(Reg *registers, Reg *pc, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        perror("Could not open registers file");
        return;
    }

    fprintf(
        file,
        "PC: value = %d\n",
        pc->value);

    for (int i = 0; i < 32; i++)
    {
        fprintf(
            file,
            "R%d: value = %d\n",
            i,
            registers[i].value);
    }

    fclose(file);
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