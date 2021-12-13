#include "headers.h"
//TODO ensure proper libraries are added

//function for performing checks that the symbol matches SIC syntax
int IsAValidSymbol( char *TestSymbol ){

	int Result = 1;
	int index = 0;
	int maxlength = 6;
	int done;
	done = 0 ;

	while( !done ) {
		//checks for valid size
		if ( TestSymbol[index] == '\0' ) {
			break;
			}

		if ( index == maxlength ) {
			done = 1;
			Result = 0;
		}

		index++;
	}

	return Result;
}//end function

//returns a -1 if the symbol already exists in the symbol table
//returns a 0 if it doesn't exist already
int symbolExists(struct symbol* Tab[], char* sName){

	int result = 0;
	int index = 0;
	char* choppedsName;
	int sSize = strlen(sName);
	//printf("Last character: %c,%c\n", sName[sSize - 2],sName[sSize - 1]);
	//perform a quick check to see if an operasnd being passed has a ,X
	if(sName[sSize - 2] == ',' && sName[sSize - 1] == 'X'){
		printf("!!!This symbol has a ,X!!!\n");
		choppedsName = strtok(sName, ",");
		strcpy(sName, choppedsName);
	}//end if

	printf("---SYMBOL SEARCH---\n");
	while(Tab[index] != NULL){
		printf("    Looking at |%s| --- Looking for |%s|\n", Tab[index]->Name, sName);
        //If sName matches symbol name at index
        if(strcmp(sName, Tab[index]->Name) == 0){
            result = -1;
            printf("---Symbol found---\n");
            break;
        }//end if
		else{
            index++;
            continue;
		}//end else
	}//end while

	printf("\n");
	return result;
}//end function


//function for adding a symbol to a function table
void addSymbol(struct symbol* Tab[], int addr, int src, char* symName){

	int index;
	index = 0;
	struct symbol* newSym;
	//mallocs a struct
	newSym = malloc(sizeof(struct symbol));
	//assignes values to the new structure
	newSym->Address = addr, newSym->DefinedOnSourceLine = src, strcpy(newSym->Name, symName);
	//search through the table until a valid spot is reached
	while(Tab[index] != NULL){
        	index++;
	}
	//assignes the structure to the table.
	Tab[index] = newSym;

}//end function
