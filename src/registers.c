#include <stdio.h>
#include <string.h>
#include "../include/registers.h"

const char *getRegType(RegType r)
{
    switch (r)
    {
    case GPRS:
        return "GPRS";
    case ZERO:
        return "ZERO";
    case PC:
        return "PC";
    default:
        return "UNKNOWN";
    }
}

Reg reg_new(int value, RegType regType)
{
    Reg r;
    r.value = value;
    r.regType = regType;
    return r;
}

Reg reg_get(Reg *r)
{
    return *r;
}

void reg_set(Reg *r, int newValue, RegType newType)
{
    if (r->regType == ZERO)
    {
        printf("Error: cannot modify the zero register\n");
        return;
    }
    r->value = newValue;
    r->regType = newType;
}
