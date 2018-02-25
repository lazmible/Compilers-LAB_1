#include "polynom.h"

Polynom::Polynom(std::vector<double> coeff)
{
	for (size_t i = 0; i < coeff.size(); i++)
	{
		this->coeff.push_back(std::make_pair(coeff[i], i));
	}
}

std::ostream & operator << (std::ostream & stream, const Polynom & poly)
{
	auto fst = poly.coeff.rbegin();
	stream << (fst->first >= 0 ? "" : " - ") << std::fabs(fst->first) << "x^" << fst->second;

	for (auto it = ++poly.coeff.rbegin(); it != poly.coeff.rend(); it++)
	{
		stream << (it->first >= 0 ? " + " : " - ")
			<< std::fabs(it->first)
			<< (it->second != 0 ? "x^" + std::to_string(it->second) : std::to_string(it->first));
	}

	return stream;
}

std::istream & operator >> (std::istream & stream, const Polynom & poly)
{

}