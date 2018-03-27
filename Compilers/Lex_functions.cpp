#include <iostream>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>

#include "y_tab.cpp.h"
#include "polynom.h"
#include "identifiers.h"


typedef int INPUT_TYPE;

INPUT_TYPE                       CurrentSymbol;
extern FILE                    * yyin;
std::size_t                      Lines = 1;
std::map<std::string, Polynom>   IdentifiersDatabase;
std::vector<std::string>         GlobalBuffers;

void SkipGarbage()
{
	while 
    (
	   (CurrentSymbol = std::fgetc(yyin)) == ' ' ||
	    CurrentSymbol == '\t'                    ||
	    CurrentSymbol == '\n'
    )

	{
		if (CurrentSymbol == '\n') 
		{
			Lines++; 
		}
	}
}

void SkipComment()
{
	Lines++;
	while ((CurrentSymbol = std::fgetc(yyin)) != '\n' && CurrentSymbol != EOF);
	SkipGarbage();
}

int FoundToken(int signature, INPUT_TYPE symb)
{
	switch (signature)
	{
		case (DIGIT)      : { yylval.num = symb - '0';                       break; }
		case (LETTER)     : { yylval.let = symb;                             break; }
		case (IDENTIFIER) : { yylval.str = (--GlobalBuffers.end())->c_str(); break; }
		case (DECLARATION): { yylval.str = (--GlobalBuffers.end())->c_str(); break; }
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

	while (std::isalnum(CurrentSymbol) || CurrentSymbol == '$')
	{
		buf += CurrentSymbol;
		CurrentSymbol = std::fgetc(yyin);
	}

	std::ungetc(CurrentSymbol, yyin);
}

void ReturnLettersToSTDIN(std::string & buf)
{
	for (auto it = --buf.end(); it != buf.begin(); it--)
	{
		if (*it == '\n') { Lines--; }
		std::ungetc(*it, yyin);
	}
}

int yyerror(const char * err)
{
	std::cout << err << " on line: " << Lines << std::endl;
	return -1;
}

int yylex()
{
	SkipGarbage();
	std::string buf;

	if (std::isdigit(CurrentSymbol)) { return FoundToken(DIGIT, CurrentSymbol); }

	else if (std::isalpha(CurrentSymbol) || CurrentSymbol == '$' || CurrentSymbol == '#')
	{
		if (CurrentSymbol == '#') 
		{
			while (CurrentSymbol == '#') 
			{ 
				SkipComment(); 
			}
		}

		ReadAllLettersAfterCurrentSymbol(buf);

		if (buf == "print") { return FoundToken(PRINT, NULL); }

		else if (*buf.begin() == '$' && *(++buf.begin()) == '$') 
		{
			buf.erase(buf.begin());
			buf.erase(buf.begin());

			for (auto it : buf) { if (it == '$') { return Error("Invalid symbol <$> in variable name"); } }

			if (buf == "print") { return Error("name <print> is reserved"); }

			if (AddIdentifierInDatabase(buf.c_str())) 
			{
				GlobalBuffers.push_back(buf);
				return FoundToken(DECLARATION, NULL); 
			}
			else { return Error("Redeclaration of variable: " + buf); }
		}
		else if (*buf.begin() == '$')
		{
			buf.erase(buf.begin());
			if (IdentifierExists(buf))
			{
				GlobalBuffers.push_back(buf);
				return FoundToken(IDENTIFIER, NULL);
			}
			else { return Error("Undeclared identifier: " + buf); }
		}
		else if (CurrentSymbol == EOF) { return 0; }
		else
		{
			ReturnLettersToSTDIN(buf);
			return FoundToken(LETTER, *buf.begin());
		}
	}

	else 
	{
		if (CurrentSymbol == '\n') { Lines++;  }
		if (CurrentSymbol == EOF)  { return 0; }
		return (CurrentSymbol); 
	}
}