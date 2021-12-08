#include "headers.h"

//checks if the input is a valid system directive
int IsADirective( char *Test ){

    //check if '+' (ACII 43) is at the start, if so remove
		if(Test[0] == 43){
        Test = chopPrefix(Test);
    }//end if

return		( 	! (
		 strcmp( Test, "START" )  &&
		 strcmp( Test, "END" )    &&
		 strcmp( Test, "RESB" )   &&
		 strcmp( Test, "RESW" )   &&
		 strcmp( Test, "RESR" )   &&
		 strcmp( Test, "BYTE" )   &&
		 strcmp( Test, "WORD" )   &&
		 strcmp( Test, "EXPORTS" ) &&
         strcmp( Test, "BASE" )   &&
         strcmp( Test, "NOBASE")

		 ) ) ;
}
