//Generates and returns object code for all formats (1-4), which will later be appended to end of T records
#include "headers.h"
#include "stdlib.h"
#include "stdbool.h"

char * generateObjectcode(char *instr, char *token, int operandAdd, int nextPCValue, int base)//function will handle formats 1, 2, 3, and 4 for sic xe
{
    //char * hexToBin(char value); //will remove
    //char binToHex(char *bin);//will remove

    char buff[1024];
    if(token == NULL) //format 1, where object code = 'OPcode' (e.g. C0)
    {
        char *finalObjectcode = malloc(6 * sizeof(char)); //will store final object code
        snprintf(buff, sizeof(buff), "%02X", getOpcode(instr) & 0xff); //gets opcode
        strcpy(finalObjectcode, buff); //stores opcode
        strcat(finalObjectcode, ",01");//adds the length
        return finalObjectcode;

    }//end if
    else if((token[0] == 'A') ||
    (token[0] == 'X') ||
    (token[0] == 'L') ||
    (token[0] == 'B') ||
    (token[0] == 'S') ||
    (token[0] == 'T') ||
    (token[0] == 'F')) //format 2, where object code = 'OPcode + register 1 + register 2' (e.g. B404)

    {
        char *finalObjectcode = malloc(7 * sizeof(char)); //will store final object code
        char *registers[2];//will store register values
        snprintf(buff, sizeof(buff), "%02X", getOpcode(instr) & 0xff); //gets opcode
        strcpy(finalObjectcode, buff);//opcode is stored in final

       registers[0] = strtok(token, " ,\r\t\n"); //register 1
        registers[1] = strtok(NULL, " ,\r\t\n"); //register 2
        for(int i = 0; i < 2 && registers[i] != NULL; i++) //goes thru registers and adds proper value to object code
        {
            if(strcmp(registers[i], "A") == 0)//need to add other registers
            {
                strcat(finalObjectcode, "0");
            }
            else if(strcmp(registers[i], "X") == 0)
            {
                strcat(finalObjectcode, "1");
            }
            else if(strcmp(registers[i], "L") == 0)
            {
                strcat(finalObjectcode, "2");
            }
            else if(strcmp(registers[i], "B") == 0)
            {
                strcat(finalObjectcode, "3");
            }
            else if(strcmp(registers[i], "S") == 0)
            {
                strcat(finalObjectcode, "4");
            }
            else if(strcmp(registers[i], "T") == 0)
            {
                strcat(finalObjectcode, "5");
            }
            else if(strcmp(registers[i], "F") == 0)
            {
                strcat(finalObjectcode, "6");
            }
            else//the second register is not null but is invalid
            {
                return "-2";
            }
        }//end of for loop
        if(registers[1] == NULL)//if there is only 1 register, the second is 0
        {
            strcat(finalObjectcode, "0");
        }
        strcat(finalObjectcode, ",02");//adds the length
        return finalObjectcode;
    }

    else if(instr[0] == '+') //format 4
    {
        char *tempObjectcode = malloc(33 * sizeof(char)); //will store the binary
        char *finalObjectcode = malloc(12 * sizeof(char)); //will store final object code

        char *registers[2];//will store register values
        snprintf(buff, sizeof(buff), "%02X", getOpcode(instr) & 0xff); //gets opcode
        strcpy(tempObjectcode, hexToBin(buff[0]));//converts first hex opcode to binary and stores

        strncat(tempObjectcode, hexToBin(buff[1]), 2); //converts second hex value in opcode to binary and stores
         //n and i are 1s for format 4
        strcat(tempObjectcode, "11");

        //below handles x

         for(int i = 0; i < strlen(token); i++)
        {
            if(token[i] == ',')
            {
                 registers[0] = strtok(token, " ,\r\t\n"); //register 1
                 registers[1] = strtok(NULL, " ,\r\t\n"); //register 2
                 if(strcmp(registers[1], "X") == 0)
                 {
                     strcat(tempObjectcode, "1"); //x is 1
                 }
            }
        }
        if(registers[0] == NULL)
        {
            strcat(tempObjectcode, "0"); //x is 0
        }


        //b and p are 0 for format 4
        strcat(tempObjectcode, "00");

        //below handles e
        strcat(tempObjectcode, "1");

        int current = 0;//current place in tempObjectcode
        char *currentBinary = malloc(5 * sizeof(char)); //will store current binary being converted
        int iterator = strlen(tempObjectcode) / 4; //divides tempObjectcode into groups of 4
        for(int i = 0; i < iterator; i++) //goes through each group of four
        {
            for(int j = 0; j < 4; j++)//adds binary to currentBinary
            {
                currentBinary[j] = tempObjectcode[current];
                current += 1;
            }
            finalObjectcode[i] = binToHex(currentBinary); //converts binary to hex and adds to finalObjectcode
        }

        snprintf(buff, sizeof(buff), "%05X", operandAdd);//converts operand address to hex
        strcat(finalObjectcode, buff); // adds to the end of finalObjectcode
        strcat(finalObjectcode, ",04");//adds the length

        return finalObjectcode;

    }//end format 4

    else //format 3
    {
        char *registers[2];//will store register values
        char *tempObjectcode = malloc(25 * sizeof(char));//will store the binary
        char *finalObjectcode = malloc(10 * sizeof(char)); //will store final object code
        snprintf(buff, sizeof(buff), "%02X", getOpcode(instr) & 0xff); //gets opcode

        strcpy(tempObjectcode, hexToBin(buff[0]));//converts first hex opcode to binary and stores
        strncat(tempObjectcode, hexToBin(buff[1]), 2); //converts second hex value in opcode to binary and stores

        //below handles n and i
        if(token[0] == '#')//for immediate addressing
        {
            strcat(tempObjectcode, "01");
        }
        else if(token[0] == '@') //for indirect addressing
        {
            strcat(tempObjectcode, "10");
        }
        else //for those without the label of either immediate/indirect
        {
            strcat(tempObjectcode, "11");
        }
        //below handles x
        for(int i = 0; i < strlen(token); i++)
        {
            if(token[i] == ',')
            {
                 registers[0] = strtok(token, " ,\r\t\n"); //register 1
                 registers[1] = strtok(NULL, " ,\r\t\n"); //register 2
                 if(strcmp(registers[1], "X") == 0)
                 {
                     strcat(tempObjectcode, "1"); //x is 1
                 }
            }
        }
        if(registers[0] == NULL)
        {
            strcat(tempObjectcode, "0"); //x is 0
        }

        //below handles b and p as well
        //strcat(tempObjectcode, "0"); //b is 0 for format 3 and is used with base register FACT CHECK


        //gets the displacement
        if(operandAdd == -1)//if the variable being referenced is not found in the symbol table
        {
            if((token[0] == '#') || (token [0] == '@'))
            {

                //below handles b

                strcat(tempObjectcode, "0"); //b is 0 for this regardless
                //p is 0 if the pc counter is not used
                strcat(tempObjectcode, "0");//converts first hex opcode to binary and stores
                //below handles e

                strcat(tempObjectcode, "0");


                strcat(tempObjectcode, "0000");
                for(int i = 1; i < strlen(token); i++) //goes through every number and gets binary, bin is stored in tempObjectcode
                {

                    strcat(tempObjectcode, hexToBin(token[i]));//converts first hex opcode to binary and stores

                }
            }
            else //unacceptable operand address
            {
                return "-1";
            }
        }
        else //operand is acceptable
        {

           int dis = operandAdd - nextPCValue; //gets displacement

            if(base == 1)//if BASE directive is in affect
            {
                if(dis < 0 && dis >= -2048)
                {
                    //b is 0 is the displacement is negative
                    strcat(tempObjectcode, "0");
                    //p is 1
                    strcat(tempObjectcode, "1");
                }
                else if(dis > 4095 || dis < -2048)//out of bounds regardless
                {
                    return "-1";
                }
                else
                {
                    //below handles b
                    strcat(tempObjectcode, "1"); //b is used if it is outside -2048 - 2047
                    //p is 0 if b is 1
                    strcat(tempObjectcode, "0");
                }
            }
            else
            {
                if(dis > 2047 && dis <= 4095)//if out of bounds for PC, used base
                {
                    //below handles b
                    strcat(tempObjectcode, "1"); //b is used if it is outside PC bounds
                    //p is 0 if b is 1
                    strcat(tempObjectcode, "0");
                }
                else if(dis > 4095 || dis < -2048)
                {
                    return "-1";
                }
                else//default is PC relative
                {
                    //b is 0 and p is 1
                    strcat(tempObjectcode, "0");
                    //p is 1
                    strcat(tempObjectcode, "1");
                }
            }
            //below handles e
            strcat(tempObjectcode, "0");


            snprintf(buff, sizeof(buff), "%02X", dis); //stores as hex
            for(int i = 0; i < strlen(buff); i++) //goes through every number and gets binary, bin is stored in tempObjectcode
            {

                strcat(tempObjectcode, hexToBin(buff[i]));//converts first hex opcode to binary and stores
            }
        }


        int current = 0;//current place in tempObjectcode
        char *currentBinary = malloc(5 * sizeof(char)); //will store current binary being converted
        int iterator = strlen(tempObjectcode) / 4; //divides tempObjectcode into groups of 4
        for(int i = 0; i < iterator; i++) //goes through each group of four
        {
            for(int j = 0; j < 4; j++)//adds binary to currentBinary
            {
                currentBinary[j] = tempObjectcode[current];
                current += 1;
            }
            finalObjectcode[i] = binToHex(currentBinary); //converts binary to hex and adds to finalObjectcode
        }
        strcat(finalObjectcode, ",03");//adds the length

        return finalObjectcode;
    }//end of format 3
}

char * hexToBin(char value) //function converts hex to bin
{
    if(value == '0')
    {
        return "0000";
    }
    else if(value == '1')
    {
        return "0001";
    }
    else if(value == '2')
    {
        return "0010";
    }
    else if(value == '3')
    {
        return "0011";
    }
    else if(value == '4')
    {
        return "0100";
    }
    else if(value == '5')
    {
        return "0101";
    }
    else if(value == '6')
    {
        return "0110";
    }
    else if(value == '7')
    {
        return "0111";
    }
    else if(value == '8')
    {
        return "1000";
    }
    else if(value == '9')
    {
        return "1001";
    }
    else if(value == 'A')
    {
        return "1010";
    }
    else if(value == 'B')
    {
        return "1011";
    }
    else if(value == 'C')
    {
        return "1100";
    }
    else if(value == 'D')
    {
        return "1101";
    }
    else if(value == 'E')
    {
        return "1110";
    }
    else if(value == 'F')
    {
        return "1111";
    }
    else
    {
        return "-1";
    }
}

char binToHex(char *bin) //function converts bin to hex
{
    if(strcmp(bin, "0000") == 0)
    {
        return '0';
    }
    else if(strcmp(bin, "0001") == 0)
    {
        return '1';
    }
    else if(strcmp(bin, "0010") == 0)
    {
        return '2';
    }
    else if(strcmp(bin, "0011") == 0)
    {
        return '3';
    }
    else if(strcmp(bin, "0100") == 0)
    {
        return '4';
    }
    else if(strcmp(bin, "0101") == 0)
    {
        return '5';
    }
    else if(strcmp(bin, "0110") == 0)
    {
        return '6';
    }
    else if(strcmp(bin, "0111") == 0)
    {
        return '7';
    }
    else if(strcmp(bin, "1000") == 0)
    {
        return '8';
    }
    else if(strcmp(bin, "1001") == 0)
    {
        return '9';
    }
    else if(strcmp(bin, "1010") == 0)
    {
        return 'A';
    }
    else if(strcmp(bin, "1011") == 0)
    {
        return 'B';
    }
    else if(strcmp(bin, "1100") == 0)
    {
        return 'C';
    }
    else if(strcmp(bin, "1101") == 0)
    {
        return 'D';
    }
    else if(strcmp(bin, "1110") == 0)
    {
        return 'E';
    }
    else if(strcmp(bin, "1111") == 0)
    {
        return 'F';
    }
    else
    {
        return '0';
    }
}
