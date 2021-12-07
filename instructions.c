#include "headers.h"

//A function for getting an instruction's equivalent Opcode
//TODO add compatibility to check instructions with "+" on the front
//TODO check if all object codes are in
char getOpcode(char* Instr){

		//check if '+' (ACII 43) is at the start, if so remove
		if(Instr[0] == 43){
            Instr = chopPrefix(Instr);
		}//end if


        if(strcmp( Instr, "ADD") == 0 ){
                return 0x18;
        }else if(strcmp( Instr, "AND") == 0 ){
                return 0x40;
        }else if(strcmp( Instr, "COMP") == 0 ){
                return 0x28;
        }else if(strcmp( Instr, "DIV") == 0 ){
                return 0x24;
        }else if(strcmp( Instr, "J") == 0 ){
                return 0x3C;
        }else if(strcmp( Instr, "JEQ") == 0 ){
                return 0x30;
        }else if(strcmp( Instr, "JGT") == 0 ){
                return 0x34;
        }else if(strcmp( Instr, "JLT") == 0 ){
                return 0x38;
        }else if(strcmp( Instr, "JSUB") == 0 ){
                return 0x48;
        }else if(strcmp( Instr, "LDA") == 0 ){
                return 0x00;
        }else if(strcmp( Instr, "LDCH") == 0 ){
                return 0x50;
        }else if(strcmp( Instr, "LDL") == 0 ){
                return 0x08;
        }else if(strcmp( Instr, "LDX") == 0 ){
                return 0x04;
        }else if(strcmp( Instr, "MUL") == 0 ){
                return 0x20;
        }else if(strcmp( Instr, "OR") == 0 ){
                return 0x44;
        }else if(strcmp( Instr, "RD") == 0 ){
                return 0xD8;
        }else if(strcmp( Instr, "RSUB") == 0 ){
                return 0x4C;
        }else if(strcmp( Instr, "STA") == 0 ){
                return 0x0C;
        }else if(strcmp( Instr, "STCH") == 0 ){
                return 0x54;
        }else if(strcmp( Instr, "STL") == 0 ){
                return 0x14;
        }else if(strcmp( Instr, "STSW") == 0 ){
                return 0xE8;
        }else if(strcmp( Instr, "STX") == 0 ){
                return 0x10;
        }else if(strcmp( Instr, "SUB") == 0 ){
                return 0x1C;
        }else if(strcmp( Instr, "TD") == 0 ){
                return 0xE0;
        }else if(strcmp( Instr, "TIX") == 0 ){
                return 0x2C;
        }else if(strcmp( Instr, "WD") == 0 ){
                return 0xDC;
        }else if(strcmp( Instr, "ADDF") == 0 ){
            return 0x58;
        }else if(strcmp( Instr, "ADDR") == 0 ){
            return 0x90;
        }else if(strcmp( Instr, "CLEAR") == 0 ){
            return 0xB4;
        }else if(strcmp( Instr, "COMPF") == 0 ){
            return 0x88;
        }else if(strcmp( Instr, "COMPR") == 0 ){
            return 0xA0;
        }else if(strcmp( Instr, "DIVF") == 0 ){
            return 0x64;
        }else if(strcmp( Instr, "DIVR") == 0 ){
            return 0x9C;
        }else if(strcmp( Instr, "FIX") == 0 ){
            return 0xC4;
        }else if(strcmp( Instr, "FLOAT") == 0 ){
            return 0xC0;
        }else if(strcmp( Instr, "HIO") == 0 ){
            return 0xF4;
        }else if(strcmp( Instr, "LDB") == 0 ){
            return 0x68;
        }else if(strcmp( Instr, "LDF") == 0 ){
            return 0x70;
        }else if(strcmp( Instr, "LDS") == 0 ){
            return 0x6C;
        }else if(strcmp( Instr, "LDT") == 0 ){
            return 0x74;
        }else if(strcmp( Instr, "LPS") == 0 ){
            return 0xD0;
        }else if(strcmp( Instr, "MULF") == 0 ){
            return 0x60;
        }else if(strcmp( Instr, "MULR") == 0 ){
            return 0x98;
        }else if(strcmp( Instr, "NORM") == 0 ){
            return 0xC8;
        }else if(strcmp( Instr, "RMO") == 0 ){
            return 0xAC;
        }else if(strcmp( Instr, "SHIFTL") == 0 ){
            return 0xA4;
        }else if(strcmp( Instr, "SHIFTR") == 0 ){
            return 0xA8;
        }else if(strcmp( Instr, "SIO") == 0 ){
            return 0xF0;
        }else if(strcmp( Instr, "SSK") == 0 ){
            return 0xEC;
        }else if(strcmp( Instr, "STB") == 0 ){
            return 0x78;
        }else if(strcmp( Instr, "STF") == 0 ){
            return 0x80;
        }else if(strcmp( Instr, "STI") == 0 ){
            return 0xD4;
        }else if(strcmp( Instr, "STS") == 0 ){
            return 0x7C;
        }else if(strcmp( Instr, "STT") == 0 ){
            return 0x84;
        }else if(strcmp( Instr, "SUBF") == 0 ){
            return 0x5C;
        }else if(strcmp( Instr, "SUBR") == 0 ){
            return 0x94;
        }else if(strcmp( Instr, "SVC") == 0 ){
            return 0xB0;
        }else if(strcmp( Instr, "TIO") == 0 ){
            return 0xF8;
        }else if(strcmp( Instr, "TIXR") == 0 ){
            return 0xB8;
        }else{
            printf("\nunrecognized instruction found\n\n%s\n\n",Instr);
            return 0;
       }
}//end function

//Wasn't able to be called for some reason, so moved to main.c
//returns 1 if the input is an instruction and 0 if it isnt
//int IsAnInstruction(char* Instr){
//
//    printf("\n\nIsAnInstruction called\n\n") == 0;//TODO REMOVE THIS
//
//	if(
//        strcmp( Instr, "ADD") == 0    || strcmp( Instr, "ADDF") == 0   || strcmp( Instr, "AND") == 0   || strcmp( Instr, "COMP") == 0  ||
//        strcmp( Instr, "COMPF") == 0  || strcmp( Instr, "DIV") == 0    || strcmp( Instr, "DIVF") == 0  || strcmp( Instr, "J") == 0     ||
//        strcmp( Instr, "JEQ") == 0    || strcmp( Instr, "JGT") == 0    || strcmp( Instr, "JLT") == 0   || strcmp( Instr, "JSUB") == 0  ||
//        strcmp( Instr, "LDA") == 0    || strcmp( Instr, "LDB") == 0    || strcmp( Instr, "LDCH") == 0  || strcmp( Instr, "LDF") == 0   ||
//        strcmp( Instr, "LDL") == 0    || strcmp( Instr, "LDS") == 0    || strcmp( Instr, "LDT") == 0   || strcmp( Instr, "LDX") == 0   ||
//        strcmp( Instr, "LPS") == 0    || strcmp( Instr, "MUL") == 0    || strcmp( Instr, "MULF") == 0  || strcmp( Instr, "OR") == 0    ||
//        strcmp( Instr, "RD") == 0     || strcmp( Instr, "RSUB") == 0   || strcmp( Instr, "SSK") == 0   || strcmp( Instr, "STA") == 0   ||
//        strcmp( Instr, "STB") == 0    || strcmp( Instr, "STCH") == 0   || strcmp( Instr, "STF") == 0   || strcmp( Instr, "STI") == 0   ||
//        strcmp( Instr, "STL") == 0    || strcmp( Instr, "STS") == 0    || strcmp( Instr, "STSW") == 0  || strcmp( Instr, "STT") == 0   ||
//        strcmp( Instr, "STX") == 0    || strcmp( Instr, "SUB") == 0    || strcmp( Instr, "SUBF") == 0  || strcmp( Instr, "TD") == 0    ||
//        strcmp( Instr, "TIX") == 0    || strcmp( Instr, "WD") == 0     || strcmp( Instr, "ADDR") == 0  || strcmp( Instr, "CLEAR") == 0 ||
//        strcmp( Instr, "COMPR") == 0  || strcmp( Instr, "DIVR") == 0   || strcmp( Instr, "MULR") == 0  || strcmp( Instr, "RMO") == 0   ||
//        strcmp( Instr, "SHIFTL") == 0 || strcmp( Instr, "SHIFTR") == 0 || strcmp( Instr, "SUBR") == 0  || strcmp( Instr, "SVC") == 0   ||
//        strcmp( Instr, "TIXR") == 0   || strcmp( Instr, "FIX") == 0    || strcmp( Instr, "FLOAT") == 0 || strcmp( Instr, "HIO") == 0   ||
//        strcmp( Instr, "NORM") == 0   || strcmp( Instr, "SIO") == 0    || strcmp( Instr, "TIO") == 0
//    ){
//        return 1;
//    }//end if
//	//else
//	else{
//		return 0;
//	}//end else
//
//}//end function

//function for getting the equivalent PC movement for SIC XE instruction format
//Can also be used to prove an instruction is not valid
//TODO determine +'s impact on
int getInstrMovement(char* Instr){
	//+ in the front means the PC will move 4 no matter what
	//Must be a format 3 instruction as well
	if(Instr[0] == '+'){
		return 4;
	}//end if

	//format 3, a default SIC compatible instruction
	//these formats are used as a bridge between SIC and SIC XE
	//42 Different format 3 instructions
	if(
        strcmp( Instr, "ADD") == 0  || strcmp( Instr, "ADDF") == 0 || strcmp( Instr, "AND") == 0 || strcmp( Instr, "COMP") == 0 || strcmp( Instr, "COMPF") == 0 || strcmp( Instr, "DIV") == 0 || strcmp( Instr, "DIVF") == 0 ||
        strcmp( Instr, "J") == 0    || strcmp( Instr, "JEQ") == 0  || strcmp( Instr, "JGT") == 0 || strcmp( Instr, "JLT") == 0  || strcmp( Instr, "JSUB") == 0  || strcmp( Instr, "LDA") == 0 || strcmp( Instr, "LDB") == 0  ||
        strcmp( Instr, "LDCH") == 0 || strcmp( Instr, "LDF") == 0  || strcmp( Instr, "LDL") == 0 || strcmp( Instr, "LDS") == 0  || strcmp( Instr, "LDT") == 0   || strcmp( Instr, "LDX") == 0 || strcmp( Instr, "LPS") == 0  ||
        strcmp( Instr, "MUL") == 0  || strcmp( Instr, "MULF") == 0 || strcmp( Instr, "OR") == 0  || strcmp( Instr, "RD") == 0   || strcmp( Instr, "RSUB") == 0  || strcmp( Instr, "SSK") == 0 || strcmp( Instr, "STA") == 0  ||
        strcmp( Instr, "STB") == 0  || strcmp( Instr, "STCH") == 0 || strcmp( Instr, "STF") == 0 || strcmp( Instr, "STI") == 0  || strcmp( Instr, "STL") == 0   || strcmp( Instr, "STS") == 0 || strcmp( Instr, "STSW") == 0 ||
        strcmp( Instr, "STT") == 0  || strcmp( Instr, "STX") == 0  || strcmp( Instr, "SUB") == 0 || strcmp( Instr, "SUBF") == 0 || strcmp( Instr, "TD") == 0    || strcmp( Instr, "TIX") == 0 || strcmp( Instr, "WD") == 0
    ){
        return 3;
    }//end if

	//format 2
	//11 Different format 2 instructions
	//these instructions perform basic modifications of registers
	if(
        strcmp( Instr, "ADDR") == 0   || strcmp( Instr, "CLEAR") == 0 || strcmp( Instr, "COMPR") == 0 ||
        strcmp( Instr, "DIVR") == 0   || strcmp( Instr, "MULR") == 0  || strcmp( Instr, "RMO") == 0   || strcmp( Instr, "SHIFTL") == 0 ||
        strcmp( Instr, "SHIFTR") == 0 || strcmp( Instr, "SUBR") == 0  || strcmp( Instr, "SVC") == 0   || strcmp( Instr, "TIXR") == 0
    ){
		return 2;
	}//end if

	//format 1
	//6 Different format 1 instructions
	//Do not do anything with registers or arithmetic
	if(strcmp( Instr, "FIX") == 0 || strcmp( Instr, "FLOAT") == 0 || strcmp( Instr, "HIO") == 0 || strcmp( Instr, "NORM") == 0 || strcmp( Instr, "SIO") == 0 || strcmp( Instr, "TIO") == 0 ){
		return 1;
	}//end if

	//if it does not fit into any of those parameters, it is an invalid instruction. Will return 0
	//TODO double check that no instructions have no PC movement
	else{
		return 0;
	}//end else

}//end function
