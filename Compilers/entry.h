#pragma once

#include <vector>

#include "variable.h"

class PolynomEntry
{
private:
	long int coeff;
	std::vector<Variable> var;

public:
	PolynomEntry() = default;
	PolynomEntry(long c, Variable v) : coeff(c) { var.push_back(v); }
	PolynomEntry(long c, std::vector<Variable> v) : coeff(c), var(v) {}

	const long int GetCoeff() const;
	const std::vector<Variable> GetVar() const;

	bool         operator == (const PolynomEntry & other) const;
	bool         operator != (const PolynomEntry & other) const;
	PolynomEntry operator *  (const PolynomEntry & other) const;

	friend std::ostream & operator << (std::ostream & stream, const PolynomEntry & entry);

};