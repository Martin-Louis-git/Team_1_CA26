#include <stdio.h>
#include "../include/parser.h"
#include "../include/instruction.h"

int main()
{
    char instruction[100][5][5] = {};
    int size = parse(instruction);
    char encodedInstruction[100][33] = {};
    encode(instruction,encodedInstruction,size);
    for (int i=0;i<size;i++)
        printf("%s \n",encodedInstruction[i]);
    return 0;
}