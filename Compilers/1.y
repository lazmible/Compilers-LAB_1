%{
	#include "polynom.h"
	#include "identifiers.h"

    int  yyerror (const char * err);
    int  yylex   ();
%}

%union	
{
	class Variable     *  _var   ;
	class PolynomEntry *  _pe    ;
	class Polynom      *  _poly  ;
	int                   num    ;
	char                  let    ;
	const char         *  str    ;
}


%type <_poly> polynom
%type <_pe>   polynom_entry
%type <_var>  variable
%type <num>   number
%type <num>   DIGIT
%type <let>   LETTER

%token <str>  PRINT IDENTIFIER DECLARATION
%token        DIGIT LETTER 

%left '+' '-'
%left '*'

%right UMINUS
%right '^'

%start source

%%

source:
                  |
    source   '\n' |
	source   '\r' |
	source begin  

begin:
    
	PRINT polynom ';'           { std::cout << *($2) << std::endl;   } |
	IDENTIFIER '=' polynom ';'  { AssignIdentifier($1, (*$3));       } |
	DECLARATION ';'             {}

polynom:

	'('polynom')'                  { ($$) = ($2);                               } |
	polynom '+' polynom            { (*$$) = (*$1) + (*$3);                     } |
	polynom '-' polynom            { (*$$) = (*$1) - (*$3);                     } |
	polynom '*' polynom            { (*$$) = (*$1) * (*$3);                     } |
	polynom '*''*' number          { (*$$) = (*$$) ^ ($4);                      } |
    IDENTIFIER                     { $$ = new Polynom(); (*$$) = GetPolynom($1) } |
	polynom_entry                  { $$ = new Polynom(*$1);                     } 
	;

polynom_entry:

	variable                { $$ = new PolynomEntry((*$1));     } |
	polynom_entry variable  { $$->Append(*$2);                  } |
	number                  { $$ = new PolynomEntry($1);  } 
	;

variable: 

	LETTER                      { $$ = new Variable($1, 1);  } |
	LETTER '^' number           { $$ = new Variable($1, $3); } 
	;

number: 
	
	DIGIT                   { $$ = $1;                           } |
	number DIGIT            { $$ = $1 * 10 + $2;                 }
	;

%%