#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//my edit test


struct symbol {
	int	DefinedOnSourceLine;
	int	Address; 
	char	Name[7]; };

typedef struct symbols	SYMBOL;

struct symbol* SymbolTable[ 1024 ];

struct opcodes {
	char	OpCode;	
	char	Name[8];

};

typedef struct opcodes OPCODES;


OPCODES OpcodeTable[ 32 ];



int updateLocation(char *dirInst, char* tokThird, int currCount, char fullLine[], int lineNumber);
void addSymbol(struct symbol* Tab[], int addr, int src, char* symName);
int symbolExists(struct symbol* Tab[], char* sName);

//function from directives.c
int IsADirective( char *Test );

//Functions from Symbols.c
int IsAValidSymbol( char *TestSymbol );

//Functions from instructions.c
char getOpcode(char* Instr);
int IsAnInstruction( char *Test ); //TODO find function and place into file
