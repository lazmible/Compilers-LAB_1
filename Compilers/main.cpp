#include <iostream>
#include <vector>
#include <string>

#pragma warning  ( disable:4996 )

#define FILENAME ( "input.txt"  )

FILE * yyin;

extern int yyparse();
int yylex();
int yyerror(const char * err);

extern std::vector<std::string> GlobalBuffers;

int main()
{
	GlobalBuffers.reserve(1000000);
	yyin = fopen(FILENAME, "r");
	yyparse();
	
	system("pause");
}