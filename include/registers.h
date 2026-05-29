#pragma once

typedef enum
{
    GPRS,
    ZERO,
    PC
} RegType;

typedef struct
{
    int value;
    RegType regType;
} Reg;

Reg reg_new(int value, RegType regType);
const char *getRegType(Reg *r);
void reg_set(Reg *r, int newValue);
int reg_get(Reg *r);