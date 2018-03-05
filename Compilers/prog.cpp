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

	Variable x1('x', 3);
	Variable x2('y', 2);
	Variable x3('x', 4);
	Variable x4('y', 4);


	PolynomEntry p1(-5, { x1, x2, });
	PolynomEntry p2(1, { x3, x4, });

	std::vector<PolynomEntry> ppp;
	ppp.push_back(p1);
	ppp.push_back(p2);

	Polynom _p1(p1);
	Polynom _p2(p2);

	std::cout << _p1 << std::endl << _p2 << std::endl;

	std::cout << _p1 * _p2 << std::endl;


	
	system("pause");
}