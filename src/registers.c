#include <stdio.h>
#include <string.h>
#include "../include/registers.h"

const char *getRegType(Reg *r)
{
    switch (r->regType)
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

int reg_get(Reg *r)
{
    return r->value;
}

void reg_set(Reg *r, int newValue)
{
    if (r->regType == ZERO)
    {
        r->value =0;
        return;
    }
    r->value = newValue;
}
