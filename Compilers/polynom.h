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

	Polynom() 
		{}
	Polynom(const Polynom & other)
		: entries(other.entries) {}
	Polynom(const std::vector<PolynomEntry> & other)
		: entries(other) {}
	Polynom(const PolynomEntry & other)
	{ entries.push_back(other); }
	~Polynom() 
		{}

	void                            AddSuch  ()       ;
	const long                      GetDegree()  const;
	const std::vector<PolynomEntry> GetEntries() const;

//	TODO: Polynom operator = (const Polynom &);
	Polynom operator + (const Polynom &);
	Polynom operator - (const Polynom &);
	Polynom operator * (const Polynom &);
//  TODO: Polynom operator / (const Polynom &);

	friend std::ostream & operator << (std::ostream & stream, const Polynom & poly);
};