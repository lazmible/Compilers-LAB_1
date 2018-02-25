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
	//std::vector<std::pair<int, int>> lol;

	//lol.push_back(std::make_pair(1, 0));
	//lol.push_back(std::make_pair(3, 0));
	//lol.push_back(std::make_pair(1, 1));
	//lol.push_back(std::make_pair(5, 1));
	//lol.push_back(std::make_pair(1, 2));
	//lol.push_back(std::make_pair(7, 2));
	//lol.push_back(std::make_pair(1, 3));
	//lol.push_back(std::make_pair(2, 3));
	//lol.push_back(std::make_pair(1, 4));
	//lol.push_back(std::make_pair(1, 4));
	//lol.push_back(std::make_pair(1, 5));
	//lol.push_back(std::make_pair(3, 5));

	Polynom kek({ 1,2 });
	Polynom lol({ 1,2 });

	std::cout << kek << std::endl;
	std::cout << kek * lol << std::endl;

//	std::cout <<  Polynom({1,-2,-3}) + Polynom({ 1,2,-3 }) << std::endl;



	system("pause");
}