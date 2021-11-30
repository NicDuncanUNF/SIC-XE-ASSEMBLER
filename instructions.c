#include "headers.h"

//A function for getting an instruction's equivalent Opcode
//TODO add compatibility to check instructions with "+" on the front
char getOpcode(char* Instr){

		//check if '+' (ACII 43) is at the start, if so remove
		if(Instr[0] == 43){
            Instr = chopPrefix(Instr);
		}//end if


        if(instCmp("ADD") ){
                return 0x18;
        }
        else if(instCmp("AND") ){
                return 0x40;
        }else if(instCmp("COMP") ){
                return 0x28;
        }else if(instCmp("DIV") ){
                return 0x24;
        }else if(instCmp("J") ){
                return 0x3C;
        }else if(instCmp("JEQ") ){
                return 0x30;
        }else if(instCmp("JGT") ){
                return 0x34;
        }else if(instCmp("JLT") ){
                return 0x38;
        }else if(instCmp("JSUB") ){
                return 0x48;
        }else if(instCmp("LDA") ){
                return 0x00;
        }else if(instCmp("LDCH") ){
                return 0x50;
        }else if(instCmp("LDL") ){
                return 0x08;
        }else if(instCmp("LDX") ){
                return 0x04;
        }else if(instCmp("MUL") ){
                return 0x20;
        }else if(instCmp("OR") ){
                return 0x44;
        }else if(instCmp("RD") ){
                return 0xD8;
        }else if(instCmp("RSUB") ){
                return 0x4C;
        }else if(instCmp("STA") ){
                return 0x0C;
        }else if(instCmp("STCH") ){
                return 0x54;
        }else if(instCmp("STL") ){
                return 0x14;
        }else if(instCmp("STSW") ){
                return 0xE8;
        }else if(instCmp("STX") ){
                return 0x10;
        }else if(instCmp("SUB") ){
                return 0x1C;
        }else if(instCmp("TD") ){
                return 0xE0;
        }else if(instCmp("TIX") ){
                return 0x2C;
        }else if(instCmp("WD") ){
                return 0xDC;
        }else{
                printf("\nunrecognized instruction found\n\n%s\n\n",Instr);
		return 0;
       }
}//end function


//returns 1 if the input is an instruction and 0 if it isnt
int IsAnInstruction (char* Instr){
	if(
        instCmp("ADD") ||
        instCmp("ADDF") ||
        instCmp("AND") ||
        instCmp("COMP") ||
        instCmp("COMPF") ||
        instCmp("DIV") ||
        instCmp("DIVF") ||
        instCmp("J") ||
        instCmp("JEQ") ||
        instCmp("JGT") ||
        instCmp("JLT") ||
        instCmp("JSUB") ||
        instCmp("LDA") ||
        instCmp("LDB") ||
        instCmp("LDCH") ||
        instCmp("LDF")||
        instCmp("LDL") ||
        instCmp("LDS") ||
        instCmp("LDT") ||
        instCmp("LDX") ||
        instCmp("LPS") ||
        instCmp("MUL") ||
        instCmp("MULF") ||
        instCmp("OR") ||
        instCmp("RD") ||
        instCmp("RSUB") ||
        instCmp("SSK") ||
        instCmp("STA") ||
        instCmp("STB") ||
        instCmp("STCH") ||
        instCmp("STF") ||
        instCmp("STI") ||
        instCmp("STL") ||
        instCmp("STS") ||
        instCmp("STSW") ||
        instCmp("STT") ||
        instCmp("STX") ||
        instCmp("SUB") ||
        instCmp("SUBF") ||
        instCmp("TD") ||
        instCmp("TIX") ||
        instCmp("WD") ||
        instCmp("ADDR") ||
        instCmp("CLEAR") ||
        instCmp("COMPR") ||
        instCmp("DIVR") ||
        instCmp("MULR") ||
        instCmp("RMO") ||
        instCmp("SHIFTL") ||
        instCmp("SHIFTR") ||
        instCmp("SUBR") ||
        instCmp("SVC") ||
        instCmp("TIXR") ||
        instCmp("FIX") ||
        instCmp("FLOAT") ||
        instCmp("HIO") ||
        instCmp("NORM") ||
        instCmp("SIO") ||
        instCmp("TIO")
    ){
        return 1;
    }//end if
	//else
	else{
		return 0;
	}//end else

}//end function

//function for getting the equavalent PC movement for SIC XE instruction format
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
	if(instCmp("ADD") || instCmp("ADDF") || instCmp("AND") || instCmp("COMP") || instCmp("COMPF") || instCmp("DIV") || instCmp("DIVF") ||
	instCmp("J") || instCmp("JEQ") || instCmp("JGT") || instCmp("JLT") || instCmp("JSUB") || instCmp("LDA") || instCmp("LDB") ||
	instCmp("LDCH") || instCmp("LDF") || instCmp("LDL") || instCmp("LDS") || instCmp("LDT") || instCmp("LDX") || instCmp("LPS") ||
	instCmp("MUL") || instCmp("MULF") || instCmp("OR") || instCmp("RD") || instCmp("RSUB") || instCmp("SSK") || instCmp("STA") ||
	instCmp("STB") || instCmp("STCH") || instCmp("STF") || instCmp("STI") || instCmp("STL") || instCmp("STS") || instCmp("STSW") ||
	instCmp("STT") || instCmp("STX") || instCmp("SUB") || instCmp("SUBF") || instCmp("TD") || instCmp("TIX") || instCmp("WD") ){
        return 3;
    }//end if

	//format 2
	//11 Different format 2 instructions
	//these instructions perform basic modifications of registers
	if(instCmp("ADDR") || instCmp("CLEAR") || instCmp("COMPR") || instCmp("DIVR") || instCmp("MULR") || instCmp("RMO") || instCmp("SHIFTL") ||
	instCmp("SHIFTR") || instCmp("SUBR") || instCmp("SVC") || instCmp("TIXR") ){
		return 2;
	}//end if

	//format 1
	//6 Different format 1 instructions
	//Do not do anything with registers or arithmetic
	if(instCmp("FIX") || instCmp("FLOAT") || instCmp("HIO") || instCmp("NORM") || instCmp("SIO") || instCmp("TIO") ){
		return 1;
	}//end if

	//if it does not fit into any of those parameters, it is an invalid instruction. Will return 0
	//TODO double check that no instructions have no PC movement
	else{
		return 0;
	}//end else

}//end function
