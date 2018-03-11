#define _CRT_SECURE_NO_WARNINGS

#include "y_tab.cpp.h"
#include "polynom.h"

#include <iostream>
#include <cstdlib>
#include <cctype>

FILE * yyin;

extern int yyparse();
extern YYSTYPE yyval;

int yylex()	
{
	int c = std::fgetc(yyin);

	if (std::isdigit(c)) 
	{
		yylval.num = c - '0'; 
		return (DIGIT);
	}
	else if (std::isalpha(c))
	{
		yyval.let = c;
		return (LETTER);
	}

	return (c);	
}

int yyerror(const char * err)
{
	std::cout << "Error: " << err << std::endl;
	return -1;
}


int main()

{
	//yyin = fopen("my.txt", "r");
	yyin = stdin;
	yyparse();
	//printf("\n");

	// You can build a variable letter from all english alphabet.

	Variable v1('a', -1); 
	Variable v2('b', 2); 
	Variable v3('c', 3); 
	Variable v4('c', 3); 

	PolynomEntry e1( 6,  { v1 } ); 
	PolynomEntry e2( -5, { v2 } ); 
	PolynomEntry e3( 2,  { v3 } ); 
//	PolynomEntry e3( 7, { v3 } ); 
//	PolynomEntry e4( 2, { v4 } ); 

	Polynom p1( { e1,e2 } ); // Create a polynom 5x^2 - 4xy^2
	Polynom p2( { e3, e1 } ); // Create a polynom 7y^2 - 2z

	std::cout << "Polynom 1: " << p1 << std::endl << "Polynom 2: " << p2 << std::endl;

	std::cout << "Summary: "        << p1 + p2 << std::endl;
	std::cout << "Subtraction: "    << p1 - p2 << std::endl;
	std::cout << "Multiplication: " << p1 * p2 << std::endl;
	
	system("pause");
}