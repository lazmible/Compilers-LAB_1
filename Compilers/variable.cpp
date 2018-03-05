#include "variable.h"

bool Variable::operator == (const Variable & other) const
{
	return this->degree == other.degree && this->letter == other.letter;
}

bool Variable::operator != (const Variable & other) const
{ 
	return !((*this) == other); 
}

const char Variable::GetLetter() const
{
	return this->letter;
}

const long int Variable::GetDegree() const
{
	return this->degree;
}

void Variable::SetLetter(char l) 
{
	this->letter = l;
}

void Variable::IncDegree(long int d) 
{
	this->degree += d;
}