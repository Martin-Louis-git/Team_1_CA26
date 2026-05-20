#include <stdio.h>
#include <string.h>
#include "../include/registers.h"
#include "../include/parser.h"
#include "../include/instruction.h"
#include "../include/cpu.h"
#include "../constants.h"

int main()
{

    char instruction[MAX_INSTRUCTIONS][5][5] = {};
    int size = parse(instruction);

    char encodedInstruction[MAX_INSTRUCTIONS][33] = {};
    encode(instruction, encodedInstruction, size);

    return 0;
}
