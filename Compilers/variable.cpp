#include "variable.h"

std::ostream & operator << (std::ostream & stream, const Variable & var)
{
	if      (var.degree != 1) { stream << var.letter << "^" << var.degree; }
	else if (var.degree == 1) { stream << var.letter;                      }
	else if (var.degree == 0) { stream << "";                              }

	return (stream);
}

bool Variable::operator == (const Variable & other) const
{
	return (this->degree == other.degree && this->letter == other.letter);
}

bool Variable::operator != (const Variable & other) const
{ 
	return (!((*this) == other)); 
}

const char Variable::GetLetter() const
{
	return (this->letter);
}

const long Variable::GetDegree() const
{
	return (this->degree);
}

void Variable::SetLetter(char l) 
{
	this->letter = l;
}

void Variable::IncDegree(long d) 
{
	this->degree += d;
}