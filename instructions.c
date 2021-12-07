#include "headers.h"

//A function for getting a instruction's equivalent Opcode
//TODO add compatibility to check instructions with "+" on the front
char getOpcode(char* Instr){
		
		//check if a + is at the start, if so remove
		if(Instr[0] == +){
			//TODO add a way to remove + from the front of a function
		}//end if
		
		
        if(strcmp( Instr, "ADD") == 0){
                return 0x18;
        }
        else if(strcmp( Instr, "AND") == 0){
                return 0x40;
        }else if(strcmp( Instr, "COMP") == 0){
                return 0x28;
        }else if(strcmp( Instr, "DIV") == 0){
                return 0x24;
        }else if(strcmp( Instr, "J") == 0){
                return 0x3C;
        }else if(strcmp( Instr, "JEQ") == 0){
                return 0x30;
        }else if(strcmp( Instr, "JGT") == 0){
                return 0x34;
        }else if(strcmp( Instr, "JLT") == 0){
                return 0x38;
        }else if(strcmp( Instr, "JSUB") == 0){
                return 0x48;
        }else if(strcmp( Instr, "LDA") == 0){
                return 0x00;
        }else if(strcmp( Instr, "LDCH") == 0){
                return 0x50;
        }else if(strcmp( Instr, "LDL") == 0){
                return 0x08;
        }else if(strcmp( Instr, "LDX") == 0){
                return 0x04;
        }else if(strcmp( Instr, "MUL") == 0){
                return 0x20;
        }else if(strcmp( Instr, "OR") == 0){
                return 0x44;
        }else if(strcmp( Instr, "RD") == 0){
                return 0xD8;
        }else if(strcmp( Instr, "RSUB") == 0){
                return 0x4C;
        }else if(strcmp( Instr, "STA") == 0){
                return 0x0C;
        }else if(strcmp( Instr, "STCH") == 0){
                return 0x54;
        }else if(strcmp( Instr, "STL") == 0){
                return 0x14;
        }else if(strcmp( Instr, "STSW") == 0){
                return 0xE8;
        }else if(strcmp( Instr, "STX") == 0){
                return 0x10;
        }else if(strcmp( Instr, "SUB") == 0){
                return 0x1C;
        }else if(strcmp( Instr, "TD") == 0){
                return 0xE0;
        }else if(strcmp( Instr, "TIX") == 0){
                return 0x2C;
        }else if(strcmp( Instr, "WD") == 0){
                return 0xDC;
<<<<<<< Updated upstream
=======
        }else if(instCmp("ADDF") ){
            return 0x58;
        }else if(instCmp("ADDR") ){
            return 0x90;
        }else if(instCmp("CLEAR") ){
            return 0xB4;
        }else if(instCmp("COMPF") ){
            return 0x88;
        }else if(instCmp("COMPR") ){
            return 0xA0;
        }else if(instCmp("DIVF") ){
            return 0x64;
        }else if(instCmp("DIVR") ){
            return 0x9C;
        }else if(instCmp("FIX") ){
            return 0xC4;
        }else if(instCmp("FLOAT") ){
            return 0xC0;
        }else if(instCmp("HIO") ){
            return 0xF4;
        }else if(instCmp("LDB") ){
            return 0x68;
        }else if(instCmp("LDF") ){
            return 0x70;
        }else if(instCmp("LDS") ){
            return 0x6C;
        }else if(instCmp("LDT") ){
            return 0x74;
        }else if(instCmp("LPS") ){
            return 0xD0;
        }else if(instCmp("MULF") ){
            return 0x60;
        }else if(instCmp("MULR") ){
            return 0x98;
        }else if(instCmp("NORM") ){
            return 0xC8;
        }else if(instCmp("RMO") ){
            return 0xAC;
        }else if(instCmp("SHIFTL") ){
            return 0xA4;
        }else if(instCmp("SHIFTR") ){
            return 0xA8;
        }else if(instCmp("SIO") ){
            return 0xF0;
        }else if(instCmp("SSK") ){
            return 0xEC;
        }else if(instCmp("STB") ){
            return 0x78;
        }else if(instCmp("STF") ){
            return 0x80;
        }else if(instCmp("STI") ){
            return 0xD4;
        }else if(instCmp("STS") ){
            return 0x7C;
        }else if(instCmp("STT") ){
            return 0x84;
        }else if(instCmp("SUBF") ){
            return 0x5C;
        }else if(instCmp("SUBR") ){
            return 0x94;
        }else if(instCmp("SVC") ){
            return 0xB0;
        }else if(instCmp("TIO") ){
            return 0xF8;
        }else if(instCmp("TIXR") ){
            return 0xB8;
>>>>>>> Stashed changes
        }else{
                printf("\nunrecognized instruction found\n\n%s\n\n",Instr);
		return 0;
       }
}//end function


//TODO find IsAnInstruction function and place here


//function for getting the equavalent PC movement for SIC XE instruction format
//Can also be used to prove an instruction is not valid
//TODO determine +'s impact on
int getInstrMovement(char* Instr){
	//+ in the front means the PC will move 4 no matter what
	//TODO
	if(Instr[0] == '+'){
		return 4;
	}//end if
	
	//format 3 or 4, a default SIC compatible instruction
	//these formats are used as a bridge between SIC and SIC XE
	//42 Different format 3 or 4 instructions
	if(strcmp( Instr, "ADD") == 0 || strcmp( Instr, "ADDF") == 0 || strcmp( Instr, "AND") == 0 || strcmp( Instr, "COMP") == 0 || strcmp( Instr, "COMPF") == 0 || strcmp( Instr, "DIV") == 0 || strcmp( Instr, "DIVF") == 0 || 
	strcmp( Instr, "J") == 0 || strcmp( Instr, "JEQ") == 0 || strcmp( Instr, "JGT") == 0 || strcmp( Instr, "JLT") == 0 || strcmp( Instr, "JSUB") == 0 || strcmp( Instr, "LDA") == 0 || strcmp( Instr, "LDB") == 0 || 
	strcmp( Instr, "LDCH") == 0 || strcmp( Instr, "LDF") == 0 || strcmp( Instr, "LDL") == 0 || strcmp( Instr, "LDS") == 0 || strcmp( Instr, "LDT") == 0 || strcmp( Instr, "LDX") == 0 || strcmp( Instr, "LPS") == 0 || 
	strcmp( Instr, "MUL") == 0 || strcmp( Instr, "MULF") == 0 || strcmp( Instr, "OR") == 0 || strcmp( Instr, "RD") == 0 || strcmp( Instr, "RSUB") == 0 || strcmp( Instr, "SSK") == 0 || strcmp( Instr, "STA") == 0 || 
	strcmp( Instr, "STB") == 0 || strcmp( Instr, "STCH") == 0 || strcmp( Instr, "STF") == 0 || strcmp( Instr, "STI") == 0 || strcmp( Instr, "STL") == 0 || strcmp( Instr, "STS") == 0 || strcmp( Instr, "STSW") == 0 || 
	strcmp( Instr, "STT") == 0 || strcmp( Instr, "STX") == 0 || strcmp( Instr, "SUB") == 0 || strcmp( Instr, "SUBF") == 0 || strcmp( Instr, "TD") == 0 || strcmp( Instr, "TIX") == 0 || strcmp( Instr, "WD") == 0 || ){
        return 3;
    }//end if
	
	//format 2
	//11 Different format 2 instructions
	if(strcmp( Instr, "ADDR") == 0 || strcmp( Instr, "CLEAR") == 0 || strcmp( Instr, "COMPR") == 0 || strcmp( Instr, "DIVR") == 0 || strcmp( Instr, "MULR") == 0 || strcmp( Instr, "RMO") == 0 || strcmp( Instr, "SHIFTL") == 0 || 
	strcmp( Instr, "SHIFTR") == 0 || strcmp( Instr, "SUBR") == 0 || strcmp( Instr, "SVC") == 0 || strcmp( Instr, "TIXR") == 0)
		return 2;
	}//end if
	
	//format 1
	//6 Different format 1 instructions
	if(strcmp( Instr, "FIX") == 0 || strcmp( Instr, "FLOAT") == 0 || strcmp( Instr, "HIO") == 0 || strcmp( Instr, "NORM") == 0 || strcmp( Instr, "SIO") == 0 || strcmp( Instr, "TIO") == 0){
		return 1;
	}//end if
	
	//if it does not fit into any of those parameters, it is an invalid instruction. Will return 0
	//TODO double check that no instructions have no PC movement
	else{
		return 0;
	}//end else
	
}//end function
