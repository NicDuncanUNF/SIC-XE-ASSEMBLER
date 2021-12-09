#include "headers.h"
//Preprocessor variables
//maximum PC reach in pass 2 is about 2100 bytes, document and/or find true number
#define MAX_PC_REACH 2100
//max sic xe memory in hex represented as a string
#define MAX_SICXE_MEMORY "100000"
#define MAXTRECORDS 1000
#define MAXMRECORDS 1000

int main( int argc, char* argv[]){

	FILE *fp;
	char line[1024];
	//char* newsym;
	//char* nextoken;
	//char* thirdToken;
	//holds the current line
	char fullline[1024];

	//the location counter
	int loCounter;
	//holds the current line's number (each line from file)
	int lineNum = 0;
	//used in pass 2 to indicate a START directive have been used
	int startFound = 0;
	//array - holds location addresses from each line
	int loArr[1024];
	//index of loArr array
	int loEle = 0;
	//Boolean for BASE(0)/NOBASE(1) operation, done in generateObjectcode
	int isBase = 0;

	if ( argc != 2 ) {
	printf("ERROR: Usage: %s filename\n", argv[0]);
	return 0;
	}


	fp = fopen( argv[1], "r");

	if ( fp == NULL ) {
	printf("ERROR: %s could not be opened for reading,\n", argv[1] );
	return 0;
	}

	char* newsym = malloc(  1024 * sizeof(char)            ); //allocating space
	memset( newsym, '\0', 1024 * sizeof(char)              ); //zeroing it out
	char* nextoken = malloc(  1024 * sizeof(char)          );
	memset( nextoken, '\0', 1024 * sizeof(char)            );
	char* thirdToken = malloc(  1024 * sizeof(char)        );
	memset( thirdToken, '\0', 1024 * sizeof(char)          );
	memset(SymbolTable, '\0', 1024 * sizeof(struct symbol*));

	//Used in condition code for if-else statements pertaining to what type of line is being read
	int lineCondition = 0;

	//Beginning of Pass 1
	while(  fgets( line , 1024 , fp ) != NULL   ) {

        //Increment the counter for current line being read
        lineNum++;

        printf("Line: %s", line);
		strcpy( fullline, line );
		if ( line[0] == 35) {
			//printf("COMMENT:%s", line );
			continue;
		}

		//if the line is empty
		if(line == NULL){
            printError("Line is empty");
			fclose(fp);
            return 0;
		}//end if
		//If line contains an invalid symbol or formatting
        if (!( ((line[0] >= 65) && (line[0] <= 90)) || (line[0] == 9) || (line[0] == 32))){
            printError("Invalid symbol or formatting");
            fclose(fp);
            return 0;
        }
        //If line contains a symbol
        if ((line[0] >= 65 ) && (line[0] <= 90))
            {lineCondition = 1;}
        //Line does not contain a symbol
        if (line[0] == 9 || line[0] == 32)
            {lineCondition = 2;}


		//For lines with symbols
		if (lineCondition == 1){
			//get the symbol
			newsym = strtok( line, " \r\t\n");

			//check if the symbol is a system directive
			if(IsADirective(newsym) == 1){
                printError("Symbol with a directive name.");
				fclose(fp);
				return 0;
			}
			//symbol has instruction name check
			if(IsAnInstruction(newsym) == 1){
			    printError("Symbol with an instruction name.");
                fclose(fp);
                return 0;
            }//end if
			//edit error format
			if ( IsAValidSymbol(newsym) == 0 ) {
			    printError("Invalid symbol found.");
                fclose(fp);
                return 0;
            }//end if
			//symbol has valid length, error check 9
			else{
				for(int i = 0; i < strlen(newsym); i++){
					if(newsym[i] == 32 ||//space
					newsym[i] == 36 ||//$
					newsym[i] == 33 ||//!
					newsym[i] == 61 ||//=
					newsym[i] == 43 ||//+
					newsym[i] == 45 ||//-
					newsym[i] == 40 ||//(
					newsym[i] == 41 ||//)
					newsym[i] == 64 ||//@
					newsym[i] == 37){//%
						printf("\nERROR:\n\n%s\nLine %d, Invalid character used in symbol.\n\n", fullline, lineNum);
                                                fclose(fp);
                                                return 0;
					}//end if
					else{
						continue;
					}//end else
				}//end for
			}//end else

			//Get the instruction/directive from the line
			nextoken = strtok( NULL, " \t\n"  );

			//If the middle token is a directive
			//TODO investigate if directives have any new changes in SICXE
			if(IsADirective(nextoken) == 1){
				//if else branch of directives for location counter movement
				//no need to check if start exists right now
				if(strcmp(nextoken, "START") == 0){
					startFound = 1;
					thirdToken = strtok(NULL, " \r\t\n");
					//error check 5
					int maxMem = strtol("100000", NULL, 16);
					//check if the new location counter exceeds max memory value
					if(strtol(thirdToken, NULL, 16) >= maxMem){
						printf("\nERROR:\n\n%s\nLine %d, SIC program starts outside of memory.\n\n", fullline, lineNum);
						fclose(fp);
						return 0;
					}
					loCounter = strtol(thirdToken, NULL, 16);
					loArr[loEle] = loCounter;
					loEle++;
					//finish lo counter array for each lo counter update and switch symtab in progLen while loop w/ the lo array
					addSymbol(SymbolTable, loCounter, lineNum, newsym);
				}
				//adding symbols after start
				else{
					//save loCounter and symbol into new struct
					thirdToken = strtok(NULL, "\r\t\n");
					//error check 2
					//printf("\n\n\nelse entered: %s\n\n\n", newsym);
					if(symbolExists(SymbolTable, newsym) != 0){ //newsym is just a string at this point
						printf("\nERROR:\n\n%s\nLine %d, Duplicate symbol found.\n\n", fullline, lineNum);
						fclose(fp);
						return 0;
					}
					addSymbol(SymbolTable, loCounter, lineNum, newsym);
					//printf("\n\nLINE 146\n\n");
					loCounter = updateLocation(nextoken, thirdToken, loCounter, fullline, lineNum);
					loArr[loEle] = loCounter;
                    loEle++;
					//check if the new location counter exceeds max memory value
					int maxMem = strtol("100000", NULL, 16);
					if(loCounter >= maxMem){
						printf("\nERROR:\n\n%s\nLine %d, Program exceeded memory.\n\n", fullline, lineNum);
                        fclose(fp);
                        return 0;
					}//end if

				}//end else

			}//end if
			else if(IsAnInstruction(nextoken) == 1){
				//printf("%s is a valid instruction.\n\n", nextoken);
				//move location counter by 3 bytes
				if(symbolExists(SymbolTable, newsym) != 0){ //newsym is just a string at this point
					printf("\nERROR:\n\n%s\nLine %d, Duplicate symbol found.\n\n", fullline, lineNum);
                    fclose(fp);
                    return 0;
                }//end if
				addSymbol(SymbolTable, loCounter, lineNum, newsym);
				//error check 10
				//printf("\n\nLINE 172\n\n");
				loCounter = updateLocation(nextoken, NULL, loCounter, fullline, lineNum);
				loArr[loEle] = loCounter;
                loEle++;
				int maxMem = strtol("100000", NULL, 16);

                if(loCounter >= maxMem){
                    printError("Program exceeded memory");
                    fclose(fp);
                    return 0;
                }//end if

			}//end else if
			//if none of the above are triggered, the middle token is an invalid directive or instruction.
			else{
				if(IsADirective(nextoken) == 0){
                    printError("INVALID DIRECTIVE FOUND, ERROR ONE");//TODO Fix error code
                    fclose(fp);
                    return 0;
				}//end if
				else{
					printError("INVALID INSTRUCTION FOUND");
                    fclose(fp);
                    return 0;
				}//end else
			}//end else


			continue;
		}//end if
		//For lines without symbols
		else if(lineCondition == 2){
            printf("\n\nNON-SYMBOL LINE\n\n");
			nextoken = strtok( line, " \r\t\n"  );
			//printf("\nFULL LINE:%s", fullline );
            //printf("FIRST TOKEN ON LINE IS %s\n", nextoken );
			if(IsADirective(nextoken) == 1){
                //printf("%s is a valid directive.\n\n", nextoken);
                //if else branch of directives for location counter movement
                //error check 10
                //printf("\n\nLINE 211\n\n");
                loCounter = updateLocation(nextoken, NULL, loCounter, fullline, lineNum);
                loArr[loEle] = loCounter;
                loEle++;
                int maxMem = strtol("100000", NULL, 16);
                if(loCounter >= maxMem){
                    printf("\nERROR:\n\n%s\nLine %d, Program exceeded memory.\n\n", fullline, lineNum);
                    fclose(fp);
                    return 0;
                }//end if
			}//end if
            else if(IsAnInstruction(nextoken) == 1){
                //printf("%s is a valid instruction.\n\n", nextoken);
                //move location counter by 3bytes
                //error check 10
                //printf("\n\nLINE 226\n\n");
                loCounter = updateLocation(nextoken, NULL, loCounter, fullline, lineNum);
                loArr[loEle] = loCounter;
                loEle++;
                int maxMem = strtol("100000", NULL, 16);
                if(loCounter >= maxMem){
                    printf("\nERROR:\n\n%s\nLine %d, Program exceeded memory.\n\n", fullline, lineNum);
                    fclose(fp);
                    return 0;
                }
            }//end else if
            else{
                if(IsADirective(nextoken) == 0){
                    printf("|%s|\n",nextoken);
                    printError("INVALID DIRECTIVE FOUND, ERROR TWO");//TODO FIX ERROR CODE
                    fclose(fp);
                    return 0;
                }//end if =
                else{
                    printf("\nERROR. INVALID INSTRUCTION FOUND ON LINE: %d\n\n", lineNum);
                    fclose(fp);
                    return 0;
                }//end else
            }//end else
			continue;
		}//end else if
		//if the line is blank, error out
		else{
			printf("\nERROR:\n\n%s\nLine %d, Blank line found.\n\n", fullline, lineNum+1);
			fclose(fp);
			return 0;
		}//end else if


		printf("\n-----\nPASS 1 DONE\n-----\n");

		//printf("%s", line );


	}//end while
	//error check 25 missing start
	if(startFound == 0){
		printf("\nERROR:\n\nProgram missing START directive.\n\n");
		fclose(fp);
		return 0;
	}

	//print symbol table
	printf("Symbol Table:\n");
	int symIndex = 0;
	while(SymbolTable[symIndex+1] != NULL){
		printf("%s\t%X\n",SymbolTable[symIndex]->Name,SymbolTable[symIndex]->Address);
		symIndex++;
	}//end while

		//--------set up location counter with valid increments
		//--------create symbol array (learn about type def struct)
                //--------output symbol and location


		//--------work for valid SIC file
		//--------check for duplicate symbols (store new symbols into array and check while updating)
		//--------check for invalid hex
		//--------check if symbols have a directive name
		//--------check if program starts outside of memory (>8000 in hex)
		//--------work for valid long byte constant
		//--------check for blank lines
		//--------check if word constant exceeds 24bit limit (2^23 = +/-8388608)
		//--------check for valid symbol name
		//--------check if program exceeds sic memory


/************************************************************************
 *									*
 *------------------------------Pass 2----------------------------------*
 *									*
 ************************************************************************/

	int proLen = (loArr[loEle-1] - loArr[0]);
	//printf("\n\n%X\n\n", proLen);

	//mem sets and allos
	char* hRec = malloc(1024 * sizeof(char));
	char tRec[1024][1024]; //= malloc(1024 * sizeof(char*));
	char mRec[1024][1024]; //= malloc(1024 * sizeof(char*));
	char* eRec = malloc(1024 * sizeof(char));
    memset( hRec, '\0', 1024 * sizeof(char) );
	//memset( tRec, '\0', 1024 * sizeof(char*) );
	//memset( mRec, '\0', 1024 * sizeof(char*) );
	memset( eRec, '\0', 1024 * sizeof(char) );

	rewind(fp);
    lineNum = 0;

	//variable to keep track of t records
	int i = 0;
	//dirInst stores a directive/instruction
    char* dirInst =  malloc(  1024 * sizeof(char) );
    memset( dirInst, '\0', 1024 * sizeof(char) );
    //oper stores the token after dirInst
    char* oper =  malloc(  1024 * sizeof(char ) );
    memset( oper, '\0', 1024 * sizeof(char) );
	char* tokThird = malloc(1024 * sizeof(char) );
    memset( tokThird, '\0', 1024 * sizeof(char) );
    char* genObjAppend = malloc(1024 * sizeof(char) );
	memset( genObjAppend, '\0', 1024 * sizeof(char) );
	char* objAppend = malloc(1024 * sizeof(char) );
	memset( objAppend, '\0', 1024 * sizeof(char) );
	char* sizeAppend = malloc(1024 * sizeof(char) );
	memset( sizeAppend, '\0', 1024 * sizeof(char) );

	while(  fgets( line , 1024 , fp ) != NULL   ) {

        //Increment the counter for current line being read
        lineNum++;
        //Copy line into fullline for error messages
        strcpy( fullline, line );

        //TODO remove debug print statements
        printf("Line number: %d\n", lineNum);
        printf("T record number: %d\n", i);
        printf("Line: %s\n\n", fullline);

		//If line is a comment
		if ( line[0] == 35) {
			continue;
		}//end if
		//If line contains a symbol
        if ((line[0] >= 65 ) && (line[0] <= 90)){
            //Skip symbol part of line
			strtok( line, " \r\t\n");
			//Tokenize the line
            dirInst = strtok( NULL, " \r\t\n");
            //TODO remove debug print statements
            printf("Symbol line, dirInst is: %s\n", dirInst);
        }
        else if (line[0] == 9 || line[0] == 32){
            //Tokenize the line
            dirInst = strtok( line, " \r\t\n");
            //TODO remove debug print statements
            printf("Non-symbol line, dirInst is: %s\n", dirInst);
        }

        //directive start (header record)
        if(strcmp(dirInst, "START") == 0){
            hRec = strcat(hRec, "H");
            hRec = strcat(hRec, SymbolTable[0]->Name);
            char* extraSpace = "      ";
            hRec = strncat(hRec, extraSpace, (6 - strlen(SymbolTable[0]->Name)));
            char buff[1024];
            snprintf(buff, sizeof(buff), "%06X", SymbolTable[0]->Address);
            hRec = strcat(hRec, buff);
            snprintf(buff, sizeof(buff), "%06X", proLen);
            hRec = strcat(hRec, buff);
            //printf("\n\n%s\n",hRec);
            //printf("Start location: %X\n", loArr[i]);
            printf("H record created\n");
			i++;
            continue;
        }//end if
        //directive word (t record)
        else if(strcmp(dirInst, "WORD") == 0){
            strcat(tRec[i], "T");
            char buff[1024];
            snprintf(buff, sizeof(buff), "%06X", loArr[i]);
            strcat(tRec[i], buff);
            //length of word
            strcat(tRec[i], "03");
            tokThird = strtok( NULL, " \r\t\n");
            int wordNum = atoi(tokThird);
            snprintf(buff, sizeof(buff), "%06X",wordNum);
            strcat(tRec[i], buff);
            //printf("Word record:\n");
            //printf("%s\n",tRec[i]);
            //printf("Word location: %X\n", loArr[i]);
            i++;
            continue;
        }//end else if
        //directive byte (t record)
        else if(strcmp(dirInst, "BYTE") == 0){

            strcat(tRec[i], "T");
            char buff[1024];
            snprintf(buff, sizeof(buff), "%06X", loArr[i]);
            strcat(tRec[i], buff);

            char* XorC = strtok( NULL, "'\r\t\n");
            if(strcmp(XorC, "C") == 0){
                tokThird = strtok( NULL, " '\r\t\n");
                //printf("\n\n%s\n\n", tokThird);
                //int stringLen = strlen(tokThird);
                //snprintf(buff, sizeof(buff), "%02X", stringLen);
                //strcat(tRec[i], buff);
                int j = 0;
                /*while(strlen(tRec[i]) > 69){
                    snprintf(buff, sizeof(buff), "%02X", tokThird[j]);
                                            strcat(tRec[i], buff);
                                            j++;
                }
                */
                char* text = malloc(1024 * sizeof(char));
                memset( text, '\0', 1024 * sizeof(char) );
                while(strlen(text) < 60){
                    if(tokThird[j] == '\0'){
                        break;
                    }
                    snprintf(buff, sizeof(buff), "%02X", tokThird[j]);
                    strcat(text, buff);
                    j++;
                }
                int textLen = (strlen(text) / 2);
                snprintf(buff, sizeof(buff), "%02X", textLen);
                strcat(tRec[i], buff);
                snprintf(buff, sizeof(buff), "%s", text);
                strcat(tRec[i], buff);
                //printf("\n\nj is equal to: %d\n\n",j);
                //printf("Byte C record:\n");
                //printf("%s\n",tRec[i]);
                //if there was a cut off, do one more iteration picking up where we left off
                if(j == 30){

                    strcat(tRec[i+1], "T");
                                    char buff[1024];
                                    snprintf(buff, sizeof(buff), "%06X", atoi("30"));
                    strcat(tRec[i+1], buff);
                    char* text = malloc(1024 * sizeof(char));
                                        memset( text, '\0', 1024 * sizeof(char) );
                    while(strlen(text) < 60){
                                                if(tokThird[j] == '\0'){
                                                    break;
                                                }
                                                snprintf(buff, sizeof(buff), "%02X", tokThird[j]);
                                                strcat(text, buff);
                        j++;
                    }
                    textLen = (strlen(text) / 2);
                                        snprintf(buff, sizeof(buff), "%02X", textLen);
                                        strcat(tRec[i+1], buff);
                                        snprintf(buff, sizeof(buff), "%s", text);
                                        strcat(tRec[i+1], buff);
                    //printf("Byte C record:\n");
                                        //printf("%s\n",tRec[i+1]);
                    i++;
                    continue;
                }
                //printf("Byte C location: %X\n", loArr[i]);
                i++;
                continue;
            }
            //simply return the hex value given
            else if(strcmp(XorC, "X") == 0){
                tokThird = strtok( NULL, " '\r\t\n");
                snprintf(buff, sizeof(buff), "%02ld", (strlen(tokThird) / 2));
                strcat(tRec[i], buff);
                //printf("\n\ntok third is %s\n\n",tokThird);
                int hex = strtol(tokThird, NULL, 16);
                snprintf(buff, sizeof(buff), "%02X", hex);
                strcat(tRec[i], buff);
                i++;
                continue;
            }

        }//end else if
        //directive end (e record)
        else if(strcmp(dirInst, "END") == 0){
            tokThird = strtok( NULL, " ,'\r\t\n");
            printf("Reached END directive, with tokThird |%s|\n", tokThird);
            strcat(eRec, "E");
            printf("After strcat E\n");
            char buff[1024];
            int j = 0;

            while(SymbolTable[j+1] != NULL){
                if(strcmp(SymbolTable[j]->Name, tokThird) == 0)
                    {break;}
                j++;
            }

            if(SymbolTable[j+1] == NULL){
                printf("After strcat E\n");
                char buff[1024];
                j = 0;

                printf("Before symbol search\n");

                //Search symbol for END's operand, which specifies the first executable instruction
                //Once found in symbol table,
                while(SymbolTable[j+1] != NULL){
                    if(strcmp(SymbolTable[j]->Name, tokThird) == 0)
                        {break;}
                    j++;
                }

                printf("After symbol search\n");

                if(SymbolTable[j+1] == NULL){
                    printError("Label was not found in Symbol Table, ERROR ONE");
                    printf("Label: |%s|\n", tokThird);
                    fclose(fp);
                    exit(0);
                }

                snprintf(buff, sizeof(buff), "%06X", SymbolTable[j]->Address);
                strcat(eRec, buff);

                continue;
            }
            snprintf(buff, sizeof(buff), "%06X", SymbolTable[j]->Address);
            strcat(eRec, buff);
            continue;
        }
        //BASE does not generate T records, but does flip a boolean that affects future T records
        else if(strcmp(dirInst, "BASE") == 0){
            isBase = 1;
            continue;
        }
        //Also doesn't generate T records. Flips boolean back off
        else if(strcmp(dirInst, "NOBASE") == 0){
            isBase = 0;
            continue;
        }
        //if instruction (t record)
        else if(IsAnInstruction(dirInst) == 1){

            oper = strtok( NULL, " \r\t\n");

            //-------------------------------------------------
            //---------------T RECORD GENERATION---------------
            //-------------------------------------------------
            //Concat 'T' to t record
            strcat(tRec[i], "T");

            char buff[1024];
            //Add location address to a buffer, then append buffer to t record
			//TODO BUFFER IS CURRENTLY FILLING WITH F'S
            snprintf(buff, sizeof(buff), "%06X", loArr[i]);
            strcat(tRec[i], buff);

            //Calls function that returns object code and size of instruction, formatted as 'objectcode,size'
            
			if(symbolExists(SymbolTable, oper) == 0)
            {
				//catches if the symbol does not exist in the symbol table
                printf("\ngenObjAppend Symbol |%s| Not Found\n", oper);
                genObjAppend = generateObjectcode(dirInst, oper, -1, (loArr[i+1]), isBase);
                printf("Object code generated: %s\n", genObjAppend);
            }
            else
            {
				//the symbol does exist in the symbol table.
                printf("\ngenObjAppend\n");
                genObjAppend = generateObjectcode(dirInst, oper, loArr[i], (loArr[i+1]), isBase);
				printf("Object code generated: %s\n", genObjAppend);
            }

            //Error checking
            if (strcmp(genObjAppend, "-1") == 0){
                printError("Label was not found in Symbol Table, ERROR TWO");
				printf("tokThird or label:|%s|\noper:|%s|\n", tokThird, oper);
                fclose(fp);
                exit(0);
            }//end if
            if (strcmp(genObjAppend, "-2") == 0){
                printError("Invalid register");
                fclose(fp);
                exit(0);
            }//end if
            if (strcmp(genObjAppend, "-3") == 0){
                printError("Out of bounds");
                fclose(fp);
                exit(0);
            }//end if

            //Break generateObjectcode's returned string in two with comma delimiter
            sizeAppend = strtok(genObjAppend, " ,");
            objAppend = strtok(NULL, " \r\t\n");

            //Append size to T record
            strcat(tRec[i], sizeAppend);

            //Append object code to T record
            strcat(tRec[i], objAppend);


            //-------------------------------------------------
            //---------------M RECORD GENERATION---------------
            //-------------------------------------------------
            strcat(mRec[i], "M");
            snprintf(buff, sizeof(buff), "%06X", loArr[i] + 1);
            strcat(mRec[i], buff);

            snprintf(buff, sizeof(buff), "05+%s", SymbolTable[0]->Name);
            strcat(mRec[i], buff);

            i++;
            continue;
        }
        else if(strcmp(dirInst, "RESW") == 0 || strcmp(dirInst, "RESB") == 0){
            //printf("Reserve location: %X\n", loArr[i]);
            i++;//TODO is this incrementation necessary if no T record is generated?
            continue;
        }//end else if

	}//end while


	fclose( fp );

	//after the storing done above, print all of the char pointers to the object file below
/*
	int l = 0;
	printf("\n\nlocation array:\n");
	while(l != i+5){
		printf("%X\n",loArr[l]);
		l++;
	}
	printf("\n\nloArr size: %d\n\n", l);
	printf("\n\niteration ammount: %d\n\n", i);
*/


    //-------------------------------------------------
    //--------------WRITE RECORDS TO FILE--------------
    //-------------------------------------------------
        char buf[1024];
        snprintf(buf, sizeof(buf), "%s.obj", argv[1]);
        fp = fopen(buf, "w");

        //Write h record
        fprintf(fp, "%s\n",hRec);

        //Print t records
        for(int j=0; j<i;j++){

            if(tRec[j][0] != 'T')
                {continue;}

            fprintf(fp, "%s\n",tRec[j]);
        }

        //Print m records
        for(int k=0; k<i;k++){

            if(mRec[k][0] != 'M')
                {continue;}

            fprintf(fp, "%s\n",mRec[k]);
        }

        //Print e record
        fprintf(fp, "%s\n",eRec);

        printf("\nOBJECT FILE CREATED!\n");
        //close file
        fclose( fp );


}//end main


//edit this to feed line and line number into parameters for error messages
int updateLocation(char *dirInst, char* tokThird, int currCount, char fullLine[], int lineNumber){
    //printf("\n\nupdateLocation called\n\n");
	//if else for directives that move locounter somewhere other than 3 bytes
        //instruction movement calculation based on format
        //printf("\n\nCalling IsAnInstruction from updateLocation, with instruction |%s|\n\n", dirInst);
		if(IsAnInstruction(dirInst) != 0){
                //different formats move their respective number in bytes

				//if format 4
				if(getInstrMovement(dirInst) == 4){
					return (currCount + 4);
				}//end if
				//if format 3
				else if(getInstrMovement(dirInst) == 3){
					return (currCount + 3);
				}//end if
				//if format 2
				else if(getInstrMovement(dirInst) == 2){
					return (currCount + 2);
				}//end if
				//if format 1
				else if(getInstrMovement(dirInst) == 1){
					return (currCount + 1);
				}//end if

				else{

				}//end if

                return currCount;
        }//end if
	else if(strcmp(dirInst, "BYTE") == 0){
		//parse string for c string(move loCounter stringlength) for x(move loCounter 1 for each pair)
		//5,4,2,10 easiest checks according to fred

		//printf("\n\n%s\n\n", tokThird);
		char* XorC = strtok(tokThird," '");
		//printf("\n\n%s\n\n", XorC);
		if(strcmp(XorC, "C") == 0){
			char* byteCheck = strtok(NULL, " '");
			//printf("\n\n%s\n\n", byteCheck);
                	currCount = currCount + (int)strlen(byteCheck);
			//printf("\n\n%d\n\n", (int)strlen(byteCheck));
                	return currCount;
		}
		else if(strcmp(XorC, "X") == 0){
			char* byteCheck = strtok(NULL, " '");
			//if gate checks for proper use of X constant, should be even number
			if(strlen(byteCheck) % 2 == 0){
				int validHex = 1;
				for(int i = 0; i < strlen(byteCheck); i++){
					if( (byteCheck[i] >= 48 && byteCheck[i] <= 57) ||
                        (byteCheck[i] >= 65 && byteCheck[i] <= 70) )
                        { continue; }
					else{
						validHex = 0;
						break;
					}
				}
				if(validHex == 1){
					currCount = currCount + (strlen(byteCheck) / 2);
					return currCount;
				}
				//test error check 3
				else{
					printf("\nERROR:\n\n%s\nLine %d, Invalid hex constant found.\n\n", fullLine, lineNumber);
					exit(0);
				}
			}
			else{
				printf("ERROR. INVALID BYTE CONSTANT FOUND. FIRST ERROR\n\n");
				exit(0);
			}
		}
		else{
			printf("ERROR. INVALID BYTE CONSTANT FOUND. SECOND ERROR%s\n\n", XorC);
			exit(0);
		}
		char* byteCheck = strtok(NULL, " '");
		printf("\n\nHERE\n%s\n\n%d\n\n", byteCheck, (int)strlen(byteCheck));
		//only works for small byte constant. Should fail test 6 as of right now.
		currCount = currCount + (int)strlen(byteCheck);
		return currCount;
	}
	else if(strcmp(dirInst, "END") == 0){
		return currCount;
	}
	else if(strcmp(dirInst, "RESB") == 0){
		currCount = currCount + atoi(tokThird);
		return currCount;
	}
	else if(strcmp(dirInst, "RESW") == 0){
		currCount = currCount + (atoi(tokThird) * 3);
		return currCount;
	}
	else if(strcmp(dirInst, "WORD") == 0){
		//still move loCounter by 3 but implement check for word constant
		if(atoi(tokThird) > 8388607){ //<-The bit limit
			printf("\nERROR:\n\n%s\nLine %d, Word constant exceeds 24 bit limit.\n\n", fullLine, lineNumber);
			exit(0);
		}
		currCount = currCount + 3;
		return currCount;
	}
	//else means EXPORT
	else{
		currCount = currCount + 3;
		return currCount;
	}

}

int IsAnInstruction(char* Instr){
	if(
        strcmp( Instr, "ADD") == 0   || strcmp( Instr, "ADDF") == 0  || strcmp( Instr, "AND") == 0  || strcmp( Instr, "COMP") == 0 ||
        strcmp( Instr, "COMPF") == 0 || strcmp( Instr, "DIV") == 0   || strcmp( Instr, "DIVF") == 0 || strcmp( Instr, "J") == 0    ||
        strcmp( Instr, "JEQ") == 0   || strcmp( Instr, "JGT") == 0   || strcmp( Instr, "JLT") == 0  || strcmp( Instr, "JSUB") == 0 ||
        strcmp( Instr, "LDA") == 0   || strcmp( Instr, "LDB") == 0   || strcmp( Instr, "LDCH") == 0 || strcmp( Instr, "LDF") == 0  ||
        strcmp( Instr, "LDL") == 0   || strcmp( Instr, "LDS") == 0   || strcmp( Instr, "LDT") == 0  || strcmp( Instr, "LDX") == 0  ||
        strcmp( Instr, "LPS") == 0   || strcmp( Instr, "MUL") == 0   || strcmp( Instr, "MULF") == 0 || strcmp( Instr, "OR") == 0   ||
        strcmp( Instr, "RD") == 0    || strcmp( Instr, "RSUB") == 0  || strcmp( Instr, "SSK") == 0  || strcmp( Instr, "STA") == 0  ||
        strcmp( Instr, "STB") == 0   || strcmp( Instr, "STCH") == 0  || strcmp( Instr, "STF") == 0  || strcmp( Instr, "STI") == 0  ||
        strcmp( Instr, "STL") == 0   || strcmp( Instr, "STS") == 0   || strcmp( Instr, "STSW") == 0 || strcmp( Instr, "STT") == 0  ||
        strcmp( Instr, "STX") == 0   || strcmp( Instr, "SUB") == 0   || strcmp( Instr, "SUBF") == 0 || strcmp( Instr, "TD") == 0   ||
        strcmp( Instr, "TIX") == 0   || strcmp( Instr, "WD") == 0    || strcmp( Instr, "ADDR") == 0 || strcmp( Instr, "CLEAR") == 0||
        strcmp( Instr, "COMPR") == 0 || strcmp( Instr, "DIVR") == 0  || strcmp( Instr, "MULR") == 0 || strcmp( Instr, "RMO") == 0  ||
        strcmp( Instr, "SHIFTL") == 0|| strcmp( Instr, "SHIFTR") == 0|| strcmp( Instr, "SUBR") == 0 || strcmp( Instr, "SVC") == 0  ||
        strcmp( Instr, "TIXR") == 0  || strcmp( Instr, "FIX") == 0   || strcmp( Instr, "FLOAT") == 0|| strcmp( Instr, "HIO") == 0  ||
        strcmp( Instr, "NORM") == 0  || strcmp( Instr, "SIO") == 0   || strcmp( Instr, "TIO") == 0
    ){
        return 1;
    }//end if
	//else
	else{
		return 0;
	}//end else

}//end function

//removes the addressing identifier from a provided instruction or operand
//key symbols are:
//@ - Indirect addressing - operand bound - essentially a pointer
//# - Immediate addressing -  operand bound - ?
//+ - Name? - instruction bound - causes a format 3 instruction to be a format 4
//Be sure to check in main if the result is valid for it's respective format
char* chopPrefix(char* chop){

    //Temporary string that stores chop w/o the prefix
    char copyChop[strlen(chop) - 1];

	//check if instruction has a prefix (+ (43), # (35), @ (64)), if so remove
    if(chop[0] == 43 || chop[0] == 64 || chop[0] == 35){
        //Copies chop into temp string, starting at index after prefix
        strcpy(copyChop, &chop[1]);
        //Copy it back into original string so that we're not returning an address of a local variable
        strcpy(chop, copyChop);

        //return string w/o prefix
        return chop;
    }//end if

    //return original string if there never was a prefix
    return chop;
	//printf("\n Newly chopped token is: %s", temp);

}//end function
