#pragma once

#include <iostream>
#include <vector>


class Variable
{

private:

	char letter;
	long int degree;

public:

	Variable() 
		: letter('a'), degree(0) {}
	Variable(char l, long int d)
		: letter(l), degree(d) {}
	~Variable()
		{}

	const char     GetLetter() const;
	const long int GetDegree() const;
	void           SetLetter(char l);
	void           IncDegree(long int d);

	bool operator == (const Variable & other) const;
	bool operator != (const Variable & other) const;

	friend std::ostream & operator << (std::ostream & stream, const Variable & var);

};