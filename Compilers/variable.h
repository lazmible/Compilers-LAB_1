#pragma once

#include <iostream>
#include <vector>


class Variable
{

private:

	char letter;
	long degree;

public:

	Variable() 
		: letter('a'), degree(0) {}
	Variable(char l, long d)
		: letter(l), degree(d) {}
	~Variable()
		{}

	const char     GetLetter() const;
	const long     GetDegree() const;
	void           SetLetter(char)  ;
	void           IncDegree(long)  ;

	bool operator == (const Variable & other) const;
	bool operator != (const Variable & other) const;

	friend std::ostream & operator << (std::ostream & stream, const Variable & var);

};