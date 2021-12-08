#include "headers.h"

//checks if the input is a valid system directive
int IsADirective( char *Test ){

return		( 	! ( 
		 strcmp( Test, "START" )  &&
		 strcmp( Test, "END" )   &&
		 strcmp( Test, "RESB" )  &&
		 strcmp( Test, "RESW" )  &&
		 strcmp( Test, "RESR" )  &&
		 strcmp( Test, "BYTE" )  &&
		 strcmp( Test, "WORD" )  &&
		 strcmp( Test, "EXPORTS" )   

		 ) ) ;
}