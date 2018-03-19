#include <iostream>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>

#include "y_tab.cpp.h"
#include "polynom.h"
#include "identifiers.h"


typedef char INPUT_TYPE;

INPUT_TYPE       CurrentSymbol;
extern FILE    * yyin;

std::map<std::string, Polynom> IdentifiersDatabase;

std::string GlobalBuf;

void SkipGarbage()
{
	while 
	(
	   (CurrentSymbol = std::fgetc(yyin)) == ' ' ||
		CurrentSymbol == '\t'                    ||
		CurrentSymbol == '\n'
	);
}

int FoundToken(int signature, INPUT_TYPE symb)
{
	switch (signature)
	{
		case (DIGIT):  { yylval.num = symb - '0';  break; }
		case (LETTER): { yylval.let = symb;        break; }
		//case (IDENTIFIER): { yylval.str}
	}
	return (signature);
}

int Error(std::string msg)
{
	std::cout << msg << std::endl;
	return (CurrentSymbol);
}

void ReadAllLettersAfterCurrentSymbol(std::string & buf)
{
	buf += CurrentSymbol;
	CurrentSymbol = std::fgetc(yyin);

	while (std::isalnum(CurrentSymbol))
	{
		buf += CurrentSymbol;
		CurrentSymbol = std::fgetc(yyin);
	}

	std::ungetc(CurrentSymbol, yyin);
	//buf.erase(--buf.end());
}

void ReturnLettersToSTDIN(std::string & buf)
{
	for (auto it = --buf.end(); it != buf.begin(); it--)
	{
		std::ungetc(*it, yyin);
	}
}

int yyerror(const char * err)
{
	std::cout << err << std::endl;
	return -1;
}

int yylex()
{
	SkipGarbage();

	if (std::isdigit(CurrentSymbol)) { return FoundToken(DIGIT, CurrentSymbol); }

	else if (std::isalpha(CurrentSymbol) || CurrentSymbol == '$')
	{
		std::string buf;
		ReadAllLettersAfterCurrentSymbol(buf);

		std::cout << "";

		if      (buf == "print")             
		{
			return FoundToken(PRINT, NULL); 
		}
		else if (*buf.begin() == '$') 
		{
			buf.erase(buf.begin());
			if (AddIdentifierInDatabase(buf.c_str())) 
			{
				return FoundToken(DECLARATION, NULL); 
			}
			else                              { return Error("Redeclaration");        }
		}
		else if (IdentifierExists(buf))      
		{
			GlobalBuf = buf;
			yylval.str = (char*)GlobalBuf.c_str();
			return FoundToken(IDENTIFIER, NULL); 
		}
		else
		{
			ReturnLettersToSTDIN(buf);
			return FoundToken(LETTER, *buf.begin());
		}
	}

	else { return (CurrentSymbol); }
}