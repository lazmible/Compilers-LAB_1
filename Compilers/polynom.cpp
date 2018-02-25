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

void Polynom::AddSuchTerms()
{
	int degree = this->GetDegree();
	std::vector<std::pair<int, int>> TempVector;

	for (int i = 0; i <= degree; i++)
	{
		std::pair<int, int> temp = { 0, 0 };
		for (auto it : this->coeff)
		{
			temp.second = i;
			if (it.second == i) { temp.first += it.first; }
		}
		TempVector.push_back(temp);
	}
	std::sort(TempVector.begin(), TempVector.end(), 
		[](std::pair<int, int> & first, std::pair<int, int> & second) { return first.second < second.second; });
	coeff = TempVector;
}

int Polynom::GetDegree()
{
	int ret = coeff.begin()->second;
	for (auto it = ++coeff.begin(); it != coeff.end(); it++)
	{
		if (ret < it->second) { ret = it->second; }
	}
	return ret;
}

std::ostream & operator << (std::ostream & stream, const Polynom & poly)
{
	// TODO: Fix x^1 to print as x.
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

Polynom Polynom::operator + (const Polynom & other)
{
	std::vector<std::pair<int, int>> ret;
	
	this->AddSuchTerms();

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

	std::sort(ret.begin(), ret.end(),
		[](std::pair<int, int> & first, std::pair<int, int> & second) { return first.second < second.second; });

	return Polynom(ret);
}

Polynom Polynom::operator - (const Polynom & other)
{
	std::vector<std::pair<int, int>> ret;
	this->AddSuchTerms();

	for (auto it : this->coeff)
	{
		for (auto it_oth : other.coeff)
		{
			if (it.second == it_oth.second)
			{
				ret.push_back(std::make_pair(it.first - it_oth.first, it.second));
			}
		}
	}
	
	std::sort(ret.begin(), ret.end(),
		[](std::pair<int, int> & first, std::pair<int, int> & second) { return first.second < second.second; });

	return ret;
}

Polynom Polynom::operator * (const Polynom & other)
{
	std::vector<std::pair<int, int>> ret;

	for (auto it : this->coeff)
	{
		for (auto it_oth : other.coeff)
		{
			ret.push_back(std::make_pair(it.first * it_oth.first, it.second + it_oth.second));
		}
	}
	
	Polynom _ret(ret);
	_ret.AddSuchTerms();

	std::sort(_ret.coeff.begin(), _ret.coeff.end(),
		[](std::pair<int, int> & first, std::pair<int, int> & second) { return first.second < second.second; });

	return _ret;
}