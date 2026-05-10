#include <stdio.h>
#include <string.h>
#include "../include/parser.h"

void parse(char (*instruction)[5][5])
{
    int ch;
    FILE *file = fopen("IO/input.txt", "r");

    char word[5] = "";
    char line[5][5] = {};

    int wordIndex = 0;
    int lineIndex = 0;
    int instructionIndex = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            strcpy(line[lineIndex], word);
            memcpy(instruction[instructionIndex], line, sizeof(line));
            word[0] = '\0';
            wordIndex = 0;
            lineIndex = 0;
            memcpy(line, (char[5][5]){{}}, sizeof(line));
            instructionIndex++;
        }
        else
        {
            if (ch == ' ')
            {
                strcpy(line[lineIndex], word);
                word[0] = '\0';
                wordIndex = 0;
                lineIndex++;
            }
            else
            {
                word[wordIndex++] = ch;
                word[wordIndex] = '\0';
            }
        }
    }

    if (ch == EOF && wordIndex > 0)
    {
        strcpy(line[lineIndex], word);
        memcpy(instruction[instructionIndex], line, sizeof(line));
    }

    fclose(file);
}