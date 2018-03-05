#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "variable.h"
#include "entry.h"

class Polynom
{
private:
	std::vector<PolynomEntry> entries;

public:
	Polynom() {}
	Polynom(Polynom & other)
		: entries(other.entries) {}
	Polynom(std::vector<PolynomEntry> & other)
		: entries(other) {}
	Polynom(PolynomEntry & other)
	{ entries.push_back(other); }
	~Polynom() {}

	Polynom operator = (const Polynom &);
	Polynom operator + (const Polynom &);
	Polynom operator - (const Polynom &);
	Polynom operator * (const Polynom &);
	Polynom operator / (const Polynom &);

	friend std::ostream & operator << (std::ostream & stream, const Polynom & poly);
};