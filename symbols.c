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
//returns a 0 if it doesent exist already
int symbolExists(struct symbol* Tab[], char* sName){
	//printf("Symbol exists entered \n\n");
	int result = 0;
	int index = 0;
	while(Tab[index] != NULL){
        	if(strcmp(sName, Tab[index]->Name) == 0){
                	result = -1;
			//printf("Dup found in symbol exists\n");
                	break;
        	}//end if
		else{
			//printf("\nSymbol exists else entered %d times\n",index);
        		index++;
			continue;
		}//end else
	}//end while

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
