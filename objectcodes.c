//will be used for generating objectcodes for format 2, 3, and 4 for TRecords
//Will update with code later
#include "headers.h"

char * generateObjectcode(char *instr, char *token, char *operandAdd, char *nextPCValue)//function will handle formats 1, 2, 3, and 4 for sic xe
{
    char buff[1024];
    if(token == NULL) //format 1
    {
        char *finalObjectcode = malloc(3 * sizeof(char)); //will store final object code
        snprintf(buff, sizeof(buff), "%02X", getOpcode(instr) & 0xff); //gets opcode
        strcpy(finalObjectcode, buff); //stores opcode
        return finalObjectcode;
    }
    else if(token[1] == ',') //format 2
    {
        char *finalObjectcode = malloc(4 * sizeof(char)); //will store final object code
        char *registers = malloc(3 * sizeof(char)); //will store original register chars
        snprintf(buff, sizeof(buff), "%02X", getOpcode(instr) & 0xff); //gets opcode
        strcpy(finalObjectcode, buff);//opcode is stored
        registers[0] = strtok(token, " ,\r\t\n"); //register 1
        registers[1] = strtok(NULL, " ,\r\t\n"); //register 2
        for(int i = 0; i < 2; i++) //goes thru registers and adds proper value to object code
        {
            if(registers[i] == 'B')
            {
                strcat(finalObjectcode, '3');
            }
            else if(registers[i] == 'S')
            {
                strcat(finalObjectcode, '4');
            }
            else if(registers[i] == 'T')
            {
                strcat(finalObjectcode, '5');
            }
            else if(registers[i] == 'F')
            {
                strcat(finalObjectcode, '6');
            }
            else
            {
                return "-1";
            }
        }//end of for loop
        return finalObjectcode;
    }
    else if(instr[0] == '+') //format 4
    {
        char *tempObjectcode = malloc(33 * sizeof(char)); //will store the binary
        char *finalObjectcode = malloc(8 * sizeof(char)); //will store final object code

        return finalObjectcode;
    }
    else //format 3
    {
        char *tempObjectcode = malloc(25 * sizeof(char));//will store the binary
        char *finalObjectcode = malloc(4 * sizeof(char)); //will store final object code

        return finalObjectcode;
    }
}

char * hexToBin(char value) //function converts hex to bin
{
    if(strcmp(value, "0") == 0)
    {
        return "0000";
    }
    else if(strcmp(value, "1") == 0)
    {
        return "0001";
    }
    else if(strcmp(value, "2") == 0)
    {
        return "0010";
    }
    else if(strcmp(value, "3") == 0)
    {
        return "0011";
    }
    else if(strcmp(value, "4") == 0)
    {
        return "0100";
    }
    else if(strcmp(value, "5") == 0)
    {
        return "0101";
    }
    else if(strcmp(value, "6") == 0)
    {
        return "0110";
    }
    else if(strcmp(value, "7") == 0)
    {
        return "0111";
    }
    else if(strcmp(value, "8") == 0)
    {
        return "1000";
    }
    else if(strcmp(value, "9") == 0)
    {
        return "1001";
    }
    else if(strcmp(value, "A") == 0)
    {
        return "1010";
    }
    else if(strcmp(value, "B") == 0)
    {
        return "1011";
    }
    else if(strcmp(value, "C") == 0)
    {
        return "1100";
    }
    else if(strcmp(value, "D") == 0)
    {
        return "1101";
    }
    else if(strcmp(value, "E") == 0)
    {
        return "1110";
    }
    else if(strcmp(value, "F") == 0)
    {
        return "1111";
    }
    else
    {
        return "-1";
    }
}
