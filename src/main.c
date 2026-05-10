#include <stdio.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/instruction.h"
#include "../include/cpu.h"
#include "../constants.h"

int main()
{
    char instruction[MAX_INSTRUCTIONS][5][5] = {};
    int size = parse(instruction);

    char encodedInstructions[size][ENCODED_INSTRUCTION_LENGTH];
    memset(encodedInstructions, 0, sizeof(encodedInstructions));

    encode(instruction, encodedInstructions, size);

    CPU cpu = createCPU(encodedInstructions, size);
    (void)cpu;

    return 0;
}
