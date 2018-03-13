#include "polynom.h"
#include "y_tab.cpp.h"

#include <iostream>
#include <cstdlib>
#include <cctype>

FILE * yyin;

extern int yyparse();

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
		static std::string buf;
		do
		{
			c = std::fgetc(yyin);
			buf += c;
		} 
		while (std::isalnum(c));

		std::ungetc(c, yyin);
		if (buf == "print") 
		{
			yylval.str = (char *)buf.c_str();
			return (PRINT);
		}
		yylval.let = c;
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
	yyin = /*fopen("my.txt", "r");*/ stdin;
	yyin = stdin;
	yyparse();
	
	system("pause");
}