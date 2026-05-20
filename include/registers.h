#pragma once 

typedef enum{ 
    GPRS,
    ZERO,
    PC
} RegType;

typedef struct{
    char reg[33];
    RegType regType;
} Reg;

Reg    reg_new(const char *reg, RegType regType);
const char   *getRegType(RegType r);
void  reg_set(Reg *r, const char *newReg, RegType newType);
Reg   reg_get(const Reg *r);