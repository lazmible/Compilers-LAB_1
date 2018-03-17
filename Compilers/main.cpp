#include "polynom.h"
#include "y_tab.cpp.h"

#include <iostream>
#include <cstdlib>
#include <cctype>

#pragma warning ( disable:4996 )

FILE * yyin;

extern int yyparse();
int c;

int yylex()	
{

	while ((c = std::fgetc(yyin)) == ' ' || c == '\t' || c == '\n');

	if (std::isdigit(c)) 
	{
		yylval.num = c - '0'; 
		return (DIGIT);
	}
	else if (std::isalpha(c))
	{
		std::string buf;
		buf += c;
		char temp;
		do
		{
			c = std::fgetc(yyin);
			buf += c;
		} 
		while (std::isalnum(c));

		std::ungetc(c, yyin);
		buf.erase(--buf.end());

		if (buf == "print") { return (PRINT); }
		yylval.let = *buf.begin();
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
	yyin = fopen("input.txt", "r");
	yyparse();
	
	system("pause");
}