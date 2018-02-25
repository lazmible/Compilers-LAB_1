#include "polynom.h"

Polynom::Polynom(std::vector<int> coeff)
{
	for (size_t i = 0; i < coeff.size(); i++)
	{
		this->coeff.push_back(std::make_pair(coeff[i], i));
	}
}

Polynom::Polynom(std::vector<std::pair<int, int>> coeff)
{
	this->coeff = coeff;
}

std::ostream & operator << (std::ostream & stream, const Polynom & poly)
{
	auto fst = poly.coeff.rbegin();
	stream << (fst->first >= 0 ? "" : " - ") 
		<< (fst->first != 0 ? std::to_string(std::abs(fst->first)) + "x^" + std::to_string(fst->second) : "");

	for (auto it = ++poly.coeff.rbegin(); it != poly.coeff.rend(); it++)
	{
		stream << (it->first != 0 ? (it->first >= 0 ? " + " : " - ") : "")
		<< (it->first != 0 ? 
		std::to_string(std::abs(it->first)) + (it->second != 0 ? "x^" + std::to_string(it->second) : "") : "");
	}

	return stream;
}

Polynom Polynom::operator+(const Polynom && other)
{
	std::vector<std::pair<int, int>> ret;
	// TODO: Подобные слагаемые приведены.
	for (auto it : this->coeff)
	{
		for (auto it_oth : other.coeff)
		{
			if (it.second == it_oth.second) 
			{
				ret.push_back(std::make_pair(it.first + it_oth.first, it.second)); 
			}
		}
	}
	// TODO: Сортировка по степеням
	return Polynom(ret);
}