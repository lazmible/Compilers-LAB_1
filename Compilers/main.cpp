#include <iostream>

#pragma warning  ( disable:4996 )

#define FILENAME ( "input.txt"  )

FILE * yyin;

extern int yyparse();
int yylex();
int yyerror(const char * err);


int main()
{
	yyin = fopen(FILENAME, "r");
	yyparse();
	
	system("pause");
}