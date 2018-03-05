#include "polynom.h"

std::ostream & operator << (std::ostream & stream, const Variable & var)
{
	if (var.degree > 1)			{ stream << var.letter << "^" << var.degree; }
	else if (var.degree == 1)   { stream << var.letter;                      }
	else if (var.degree == 0)   { stream << "";                              }
	return stream;
}

std::ostream & operator << (std::ostream & stream, const PolynomEntry & entry)
{
	if (entry.coeff != 1 && entry.coeff != -1) { stream << std::abs(entry.coeff); }
	for (auto it : entry.var) { stream << it; }
	return stream;
}

std::ostream & operator << (std::ostream & stream, const Polynom & poly)
{
	std::vector<PolynomEntry> entries = poly.entries;

	if (!entries.empty())
	{
		auto first = entries.begin();

		if (first->GetCoeff() < 0) { stream << " - " << *first; }
		else if (first->GetCoeff() > 0) { stream << *first; }

		entries.erase(first);

		for (auto it : entries)
		{
			if (it.GetCoeff() > 0) { stream << " + " << it; }
			else if (it.GetCoeff() < 0) { stream << " - " << it; }
		}
	}
	return stream;
}

Polynom Polynom::operator + (const Polynom & other)
{
	std::vector<PolynomEntry> ret;
	
//	this->AddSuchTerms();

	for (auto it : this->entries) { ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar())); }
	for (auto it : other.entries) { ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar())); }

	Polynom _ret(ret);

	//std::sort(ret.begin(), ret.end(),
	//	[](std::pair<int, int> & first, std::pair<int, int> & second) { return first.second < second.second; });

	return _ret;
}

Polynom Polynom::operator - (const Polynom & other)
{
	std::vector<PolynomEntry> ret;
	
	for (auto it : this->entries) { ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar())); }

	for (auto it : other.entries) { ret.push_back(PolynomEntry(-it.GetCoeff(), it.GetVar())); }

	Polynom _ret(ret);
	
	/*std::sort(ret.begin(), ret.end(),
		[](std::pair<int, int> & first, std::pair<int, int> & second) { return first.second < second.second; });*/

	return _ret;
}

Polynom Polynom::operator * (const Polynom & other)
{
	std::vector<PolynomEntry> ret;

	for (auto it : this->entries)
	{
		for (auto it_oth : other.entries)
		{
			ret.push_back(it * it_oth);
		}
	}
	
	Polynom _ret(ret);

	//std::sort(_ret.coeff.begin(), _ret.coeff.end(),
	//	[](std::pair<int, int> & first, std::pair<int, int> & second) { return first.second < second.second; });

	return _ret;
}