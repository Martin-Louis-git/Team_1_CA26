#include <stdio.h>
#include "../include/registers.h"
#include "../include/parser.h"
#include "../include/Instruction.h"
#include "../constants.h"

int main()
{
    
    char instruction[MAX_INSTRUCTIONS][5][5] = {};
    int size = parse(instruction);

    char encodedInstruction[MAX_INSTRUCTIONS][33] = {};
    encode(instruction, encodedInstruction, size);

    /*

    // Create registers
    Reg r1 = reg_new("x1", GPRS);
    Reg r0 = reg_new("x0", ZERO);
    Reg pc = reg_new("pc", PC);

    // Print using reg_get
    Reg r1_copy = reg_get(&r1);
    printf("r1: %s, type: %s\n", r1_copy.reg, getRegType(r1_copy.regType));

    Reg r0_copy = reg_get(&r0);
    printf("r0: %s, type: %s\n", r0_copy.reg, getRegType(r0_copy.regType));

    Reg pc_copy = reg_get(&pc);
    printf("pc: %s, type: %s\n", pc_copy.reg, getRegType(pc_copy.regType));

    // Modify r1 (allowed)
    reg_set(&r1, "x2", GPRS);
    printf("r1 after set: %s, type: %s\n", reg_get(&r1).reg, getRegType(reg_get(&r1).regType));

    // Try to modify r0 (blocked)
    reg_set(&r0, "x5", GPRS);
    printf("r0 after attempted set: %s, type: %s\n", reg_get(&r0).reg, getRegType(reg_get(&r0).regType));

    */

    return 0;
}