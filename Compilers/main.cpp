#define _CRT_SECURE_NO_WARNINGS

extern "C" 
{
	#include "y_tab.h"
	extern int yyparse();
	extern int yyval;
}

#include "polynom.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

FILE * yyin;

extern "C"
{
	int yylex()
	
	{
		int c = fgetc(yyin);

		if (c == '+')   { return (PLUS);  }
		if (c == '-')   { return (MINUS); }
		if (isdigit(c)) 
		{
			yylval = c - '0'; 
			return (DIGIT);
			//std::string kek = std::string("abc");
		}

		return (c);	
	}

	int yyerror(char * c)
	{
		puts("error");
		//std::cout << "error" << std::endl;
		return -1;
	}
}

int main()

{
	//yyin = fopen("my.txt", "r");
	//yyparse();
	//printf("\n");

	// You can build a variable letter from all english alphabet.

	Variable v1('x', 2); // Create a variable x^2
	Variable v2('x', 1); // Create a variable x^1
	Variable v3('y', 2); // Create a variable y^2
	Variable v4('z', 1); // Create a variable z^1

	PolynomEntry e1( 5, { v1 }      ); // Create a monom 5x^2
	PolynomEntry e2( -4, { v2, v3 } ); // Create a monom -4xy^2
	PolynomEntry e3( 7, { v3 }      ); // Create a monom 7y^2
	PolynomEntry e4( 2, { v4 }      ); // Create a monom 2z

	Polynom p1( { e1,e2 } ); // Create a polynom 5x^2 - 4xy^2
	Polynom p2( { e3,e4 } ); // Create a polynom 7y^2 - 2z

	std::cout << "Polynom 1: " << p1 << std::endl << "Polynom 2:" << p2 << std::endl;

	std::cout << "Summary: "        << p1 + p2 << std::endl;
	std::cout << "Subtraction: "    << p1 - p2 << std::endl;
	std::cout << "Multiplication: " << p1 * p2 << std::endl;
	
	system("pause");
}