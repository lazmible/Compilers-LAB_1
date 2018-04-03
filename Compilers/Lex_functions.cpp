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

inline bool is_operator(INPUT_TYPE c)
{
	return (c == '+' || c == '-' || c == '*' || c == '=' || c == '^');
}

inline bool is_key_symbol(INPUT_TYPE c)
{
	return (c == '$' || c == ';' || c == '#');
}

void SkipGarbage()
{
	while 
    (
	   (CurrentSymbol = fgetc(yyin)) == ' ' ||
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
	while ((CurrentSymbol = fgetc(yyin)) != '\n' && CurrentSymbol != EOF);
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
	CurrentSymbol = fgetc(yyin);

	while (isalnum(CurrentSymbol) || CurrentSymbol == '$')
	{
		buf += CurrentSymbol;
		CurrentSymbol = fgetc(yyin);
	}

	ungetc(CurrentSymbol, yyin);
}

void ReturnLettersToSTDIN(std::string & buf)
{
	for (auto it = --buf.end(); it != buf.begin(); it--)
	{
		if (*it == '\n') { Lines--; }
		ungetc(*it, yyin);
	}
}

int yyerror(const char * err)
{
	std::cout << err << " on line " << Lines << ": " << std::endl;
	return -1;
}

int yylex()
{
	SkipGarbage();
	std::string buf;

	if (isdigit(CurrentSymbol)) { return FoundToken(DIGIT, CurrentSymbol); }

	else if (isalpha(CurrentSymbol) || CurrentSymbol == '$' || CurrentSymbol == '#')
	{
		if (CurrentSymbol == '#') 
		{
			while (CurrentSymbol == '#') 
			{ 
				SkipComment(); 
			}
		}
		if (CurrentSymbol == ';') { goto KOSTIL; }

		ReadAllLettersAfterCurrentSymbol(buf);

		if (buf == "print") { return FoundToken(PRINT, 0); }

		else if (*buf.begin() == '$' && *(++buf.begin()) == '$') 
		{
			buf.erase(buf.begin());
			buf.erase(buf.begin());

			for (auto it : buf) { if (!isalnum(it)) { return Error("Invalid symbols in variable name"); } }

			if (buf == "print") { return Error("name <print> is reserved"); }

			if (AddIdentifierInDatabase(buf.c_str())) 
			{
				GlobalBuffers.push_back(buf);
				return FoundToken(DECLARATION, 0); 
			}
			else { return Error("Redeclaration of variable: " + buf); }
		}
		else if (*buf.begin() == '$')
		{
			buf.erase(buf.begin());
			if (IdentifierExists(buf))
			{
				GlobalBuffers.push_back(buf);
				return FoundToken(IDENTIFIER, 0);
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
		KOSTIL:
		if (CurrentSymbol == '\n') { Lines++;  }
		if (CurrentSymbol == EOF)  { return 0; }
		return (CurrentSymbol); 
	}
}