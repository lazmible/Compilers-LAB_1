%{
	#include "polynom.h"

    int  yyerror (const char * err);
    int  yylex   ();
%}

%union	
{
	class Variable     *  _var   ;
	class PolynomEntry *  _pe    ;
	class Polynom      *  _poly  ;
	int                 num      ;
	char                let      ;
}

%type <_poly> polynom
%type <_pe>   polynom_entry
%type <_var>  variable
%type <num>   number
%type <num>   DIGIT
%type <let>   LETTER

%token DIGIT LETTER

%start variable

%%

polynom:

	'('polynom')'           { (*$$) = (*$2);                     } |
	polynom '+' polynom     { (*$$) = (*$1) + (*$3);             } |
	polynom '-' polynom     { (*$$) = (*$1) - (*$3);             } |
	polynom '*' polynom     { (*$$) = (*$1) * (*$3);             } |
	polynom_entry           { $$ = new Polynom(*$1);             } |

polynom_entry:

	variable                { $$ = new PolynomEntry((*$1));      } |
	number variable         { $$ = new PolynomEntry($1, (*$2));  } |
	'-' variable            { $$ = new PolynomEntry(-1, (*$2));  } |
	'-' number variable     { $$ = new PolynomEntry($2, (*$3));  } |
	polynom_entry variable  { $$->Append(*$2);                   } |

variable: 

	LETTER                  { $$ = new Variable($1, 1);          } |
	LETTER '^' number       { $$ = new Variable($1, $3);         }

number: 
	
	DIGIT                   { $$ = $1;                           } |
	number DIGIT            { $$ = $1 * 10 + $2;                 }