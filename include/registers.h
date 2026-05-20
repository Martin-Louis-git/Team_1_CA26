#pragma once

typedef enum
{
    GPRS,
    ZERO,
    PC
} RegType;

typedef struct
{
    char reg[33];
    RegType regType;
} Reg;

Reg reg_new(char *reg, RegType regType);
const char *getRegType(RegType r);
void reg_set(Reg *r, char *newReg, RegType newType);
Reg reg_get(Reg *r);