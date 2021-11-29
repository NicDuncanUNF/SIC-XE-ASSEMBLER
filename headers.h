#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defining syntax for cleaner code
#define instCmp(instruction)      strcmp( Instr, "instruction") == 0

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


//Functions from main.c
int updateLocation(char *dirInst, char* tokThird, int currCount, char fullLine[], int lineNumber);
char chopPrefix(char* chop);

//function from directives.c
int IsADirective( char *Test );

//Functions from Symbols.c
int IsAValidSymbol( char *TestSymbol );
void addSymbol(struct symbol* Tab[], int addr, int src, char* symName);
int symbolExists(struct symbol* Tab[], char* sName);

//Functions from instructions.c
char getOpcode(char* Instr);
int IsAnInstruction (char* Instr);

//Functions from objectcodes.c
char * generateObjectcode(char *instr, char *token, int operandAdd, int nextPCValue);
char * hexToBin(char value);
char binToHex(char *bin);
