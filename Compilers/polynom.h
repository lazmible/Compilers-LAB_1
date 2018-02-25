#pragma once

#include <iostream>
#include <vector>
#include <string>

class Polynom
{
private:
	std::vector<std::pair<double, size_t>> coeff;
public:
	Polynom() {}
	Polynom(std::vector<double>);
	~Polynom() {}

	size_t GetDegree() { return NULL; /*coeff.size();*/ }

	Polynom operator = (const Polynom &);
	Polynom operator + (Polynom &);
	Polynom operator - (Polynom &);
	Polynom operator * (Polynom &);
	Polynom operator / (Polynom &);

	friend std::ostream & operator << (std::ostream & stream, const Polynom & poly);
	friend std::istream & operator >> (std::istream & stream, const Polynom & poly);
};

struct PairRoutine
{

};