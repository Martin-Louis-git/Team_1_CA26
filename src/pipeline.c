#include <instruction_packet.h>
#include "../include/cpu.h"
#include <stdio.h>
#include <string.h>
#include <pipeline.h>
#include "../include/registers.h"

void decode(CPU* cpu){

    char bits[33];
    strncpy(bits, fetch_decode->instruction, 32);
    bits[32] = '\0';
    
    unsigned int instruction = (unsigned int)strtol(bits, NULL, 2);

    int op = (instruction) & 0b11110000000000000000000000000000;
    op = op >> 28;
    decode_execute->opcode = op;

    int r1 = (instruction) & 0b00001111100000000000000000000000;
    r1 = r1 >> 23;
    int r2 = (instruction) & 0b00000000011111000000000000000000;
    r2 = r2 >> 18;
    int r3 = (instruction) & 0b00000000000000111110000000000000;
    r3 = r3 >> 13;
    int sh = (instruction) & 0b00000000000000000001111111111111;
    decode_execute->shamt = sh;

    int im = (instruction) & 0b00000000000000111111111111111111;
    decode_execute->immediate = im;
    int ad = (instruction) & 0b00001111111111111111111111111111;
    decode_execute->memAddress = ad;


    Reg *passR1 = &cpu->registers[r1];
            decode_execute->r1 = passR1;
            Reg *passR2 = &cpu->registers[r2];
            decode_execute->r2 = passR2;
            Reg *passR3 = &cpu->registers[r3];
            decode_execute->r3 = passR3;

    switch(op){
        case(0):
        case(1):
        case(2):
        case(5):
        case(8):
        case(9):
            //R
            decode_execute->type = 'r';
            break;
        case(3):
        case(4):
        case(6):
        case(10):
        case(11):
            //i
            decode_execute->type = 'i';
            break;
        case(7):
            //j
            decode_execute->type = 'j';
            break;
        default:
        break;
    }
}


