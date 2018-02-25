#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Polynom
{
private:
	std::vector<std::pair<int, int>> coeff;
	void AddSuchTerms();
	int GetDegree();

public:
	Polynom() {}
	Polynom(std::vector<int>);
	Polynom(std::vector<std::pair<int, int>>);
	~Polynom() {}

	Polynom operator = (const Polynom &);
	Polynom operator + (const Polynom &);
	Polynom operator - (const Polynom &);
	Polynom operator * (const Polynom &);
	Polynom operator / (const Polynom &);

	friend std::ostream & operator << (std::ostream & stream, const Polynom & poly);
//	friend std::istream & operator >> (std::istream & stream, const Polynom & poly);
};