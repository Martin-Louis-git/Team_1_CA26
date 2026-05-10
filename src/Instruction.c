#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/instruction.h"

char* BinaryReg(char* Reg){
    if (strcmp(Reg, "R1") == 0)
        return "00001";
    else if (strcmp(Reg, "R2") == 0)
        return "00010";
    else if (strcmp(Reg, "R3") == 0)
        return "00011";
    else if (strcmp(Reg, "R4") == 0)
        return "00100";
    else if (strcmp(Reg, "R5") == 0)
        return "00101";
    else if (strcmp(Reg, "R6") == 0)
        return "00110";
    else if (strcmp(Reg, "R7") == 0)
        return "00111";
    else if (strcmp(Reg, "R8") == 0)
        return "01000";
    else if (strcmp(Reg, "R9") == 0)
        return "01001";
    else if (strcmp(Reg, "R10") == 0)
        return "01010";
    else if (strcmp(Reg, "R11") == 0)
        return "01011";
    else if (strcmp(Reg, "R12") == 0)
        return "01100";
    else if (strcmp(Reg, "R13") == 0)
        return "01101";
    else if (strcmp(Reg, "R14") == 0)
        return "01110";
    else if (strcmp(Reg, "R15") == 0)
        return "01111";
    else if (strcmp(Reg, "R16") == 0)
        return "10000";
    else if (strcmp(Reg, "R17") == 0)
        return "10001";
    else if (strcmp(Reg, "R18") == 0)
        return "10010";
    else if (strcmp(Reg, "R19") == 0)
        return "10011";
    else if (strcmp(Reg, "R20") == 0)
        return "10100";
    else if (strcmp(Reg, "R21") == 0)
        return "10101";
    else if (strcmp(Reg, "R22") == 0)
        return "10110";
    else if (strcmp(Reg, "R23") == 0)
        return "10111";
    else if (strcmp(Reg, "R24") == 0)
        return "11000";
    else if (strcmp(Reg, "R25") == 0)
        return "11001";
    else if (strcmp(Reg, "R26") == 0)
        return "11010";
    else if (strcmp(Reg, "R27") == 0)
        return "11011";
    else if (strcmp(Reg, "R28") == 0)
        return "11100";
    else if (strcmp(Reg, "R29") == 0)
        return "11101";
    else if (strcmp(Reg, "R30") == 0)
        return "11110";
    else if (strcmp(Reg, "R31") == 0)
        return "11111";
    return "";

}

char* BinaryOpCode(char* Op){
    if (strcmp(Op,"ADD")==0)
        return "0000";
    if (strcmp(Op,"SUB")==0)
        return "0001";
    if (strcmp(Op,"MUL")==0)
        return "0010";
    if (strcmp(Op,"MOVI")==0)
        return "0011";
    if (strcmp(Op,"JEQ")==0)
        return "0100";
    if (strcmp(Op,"AND")==0)
        return "0101";
    if (strcmp(Op,"XORI")==0)
        return "0110";
    if (strcmp(Op,"JMP")==0)
        return "0111";
    if (strcmp(Op,"LSL")==0)
        return "1000";
    if (strcmp(Op,"LSR")==0)
        return "1001";
    if (strcmp(Op,"MOVR")==0)
        return "1010";
    if (strcmp(Op,"MOVM")==0)
        return "1011";
}

char Type(char* Op){
    if (strcmp(Op,"ADD")==0 ||
        strcmp(Op,"SUB")==0 ||
        strcmp(Op,"MUL")==0 ||
        strcmp(Op,"AND")==0 ||
        strcmp(Op,"LSL")==0 ||
        strcmp(Op,"LSR")==0 
    ){
        return 'R';
    }        
    if (strcmp(Op,"MOVI")==0 ||
        strcmp(Op,"JEQ")==0 ||
        strcmp(Op,"XORI")==0 ||
        strcmp(Op,"MOVR")==0 ||
        strcmp(Op,"MOVM")==0 
    ){
        return 'I';
    }
    if(strcmp(Op,"JMP")==0)
        return 'J';
}

char* toBinary18(char* numStr) {
    int num = atoi(numStr);
    static char binary[19];
    binary[18] = '\0';
    for (int i = 17; i >= 0; i--) {
        binary[i] = (num % 2) + '0';
        num /= 2;
    }
    return binary;
}
char* toBinary28(char* numStr) {
    int num = atoi(numStr);
    static char binary[29];
    binary[28] = '\0';
    for (int i = 27; i >= 0; i--) {
        binary[i] = (num % 2) + '0';
        num /= 2;
    }
    return binary;
}
char* toBinary13(char* numStr) {
    int num = atoi(numStr);
    static char binary[14];
    binary[13] = '\0';
    for (int i = 12; i >= 0; i--) {
        binary[i] = (num % 2) + '0';
        num /= 2;
    }
    return binary;
}



void encode(char instructions[][5][5],char Encoded[][33], int size) {
    
    
    for (int i = 0; i<size ; i++){
        //R Format
        if(Type(instructions[i][0]) == 'R'){
            strcpy(Encoded[i],BinaryOpCode(instructions[i][0]));
            strcat(Encoded[i],BinaryReg(instructions[i][1])); // R1
            strcat(Encoded[i],BinaryReg(instructions[i][2])); // R2
            if (strcmp(instructions[i][0],"LSL") ==0 || strcmp(instructions[i][0],"LSR") ==0 ){
                strcat(Encoded[i],"00000"); // R3 kolo 0
                strcat(Encoded[i],toBinary13(instructions[i][3])); // SHAMT
            }
            else{
                strcat(Encoded[i],BinaryReg(instructions[i][3]));
                strcat(Encoded[i],"0000000000000"); // SHAMT kolo 0
            }
        }
        if(Type(instructions[i][0]) == 'I'){
                strcpy(Encoded[i],BinaryOpCode(instructions[i][0]));
                strcat(Encoded[i],BinaryReg(instructions[i][1]));
            if (strcmp(instructions[i][0],"MOVI") ==0 ){
                strcat(Encoded[i],"00000"); 
                strcat(Encoded[i],toBinary18(instructions[i][2]));
            }
            else
            {
                strcat(Encoded[i],BinaryReg(instructions[i][2]));
                strcat(Encoded[i],toBinary18(instructions[i][3]));
            }
        }
        if(Type(instructions[i][0]) == 'J'){
            strcpy(Encoded[i],BinaryOpCode(instructions[i][0]));
            strcat(Encoded[i],toBinary28(instructions[i][1]));
        }

    }
    
}