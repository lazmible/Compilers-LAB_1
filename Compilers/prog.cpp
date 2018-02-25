#define _CRT_SECURE_NO_WARNINGS

extern "C" 
{
	#include "y_tab.h"
	extern int yyparse();
//	extern int yyval;
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
		}

		return (c);	
	}

	int yyerror(char * c)
	{
		puts("error");
		return -1;
	}
}

int main()

{
	//yyin = fopen("my.txt", "r");
	//yyparse();
	//printf("\n");

	std::cout << std::defaultfloat <<  Polynom({1,-2,-3}) + Polynom({ 1,2,-3 }) << std::endl;

	system("pause");
}