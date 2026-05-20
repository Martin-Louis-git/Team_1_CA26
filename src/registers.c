#include <stdio.h>
#include <string.h>
#include "../include/registers.h"

const char* getRegType (RegType r){
    switch(r){
        case GPRS: return "GPRS";
        case ZERO: return "ZERO";
        case PC: return "PC";
        default:   return "UNKNOWN";
    }
}

Reg reg_new(const char *reg, RegType regType){
    Reg r;
    strcpy(r.reg,reg);
    r.regType = regType;
    return r;
}

Reg reg_get(const Reg *r) {
    return *r;
}

void reg_set(Reg *r, const char *newReg, RegType newType) {
    if (r->regType == ZERO) {
        printf("Error: cannot modify the zero register\n");
        return;
    }
    strncpy(r->reg, newReg, sizeof(r->reg) - 1);
    r->reg[sizeof(r->reg) - 1] = '\0';
    r->regType = newType;
}

