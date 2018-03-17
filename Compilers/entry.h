#pragma once

#include "variable.h"

class PolynomEntry
{

private:

	long coeff;
	std::vector<Variable> var;

public:

	PolynomEntry()
		{}
	PolynomEntry(long c) 
		: coeff(c) {}
	PolynomEntry(Variable v)
		: coeff(1) { var.push_back(v); }
	PolynomEntry(long c, Variable v) 
		: coeff(c) { var.push_back(v); }
	PolynomEntry(long c, std::vector<Variable> v) 
		: coeff(c), var(v) {}
	~PolynomEntry()
		{}

	const long                   GetCoeff  ()  const  ;
	const std::vector<Variable>  GetVar    ()  const  ;
	const long                   GetDegree ()  const  ;
	void                         AddSuch   ()         ; 
	void                         IncCoeff  (long)     ;
	void                         Append    (Variable) ; 

	bool         operator == (const PolynomEntry & other) const;
	bool         operator != (const PolynomEntry & other) const;
	PolynomEntry operator *  (const PolynomEntry & other) const;

	friend std::ostream & operator << (std::ostream & stream, const PolynomEntry & entry);
};