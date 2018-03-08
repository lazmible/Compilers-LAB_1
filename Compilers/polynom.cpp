#include "polynom.h"

std::ostream & operator << (std::ostream & stream, const Polynom & poly)
{
	std::vector<PolynomEntry> entries = poly.GetEntries();

	if (!entries.empty())
	{
		auto first = entries.begin();

		if      (first->GetCoeff() < 0) { stream << " - " << *first; }
		else if (first->GetCoeff() > 0) { stream << *first; }

		entries.erase(first);

		for (auto it : entries)
		{
			if (it.GetCoeff() > 0)      { stream << " + " << it; }
			else if (it.GetCoeff() < 0) { stream << " - " << it; }
		}
	}
	return (stream);
}

const long Polynom::GetDegree() const
{
	long result = 0;
	for (auto it : this->entries)
	{
		result = result > it.GetDegree() ? it.GetDegree() : result;
	}
	return (result);
}

const std::vector<PolynomEntry> Polynom::GetEntries() const
{
	return (this->entries);
}

void Polynom::AddSuch()
{
	std::vector<PolynomEntry> result;
	
	for (auto it : this->entries) { it.AddSuch(); }

	std::vector<PolynomEntry> _entries = this->GetEntries();

	while (!_entries.empty())
	{
		PolynomEntry temp = *(_entries.begin());

		if (_entries.begin() != _entries.end()) { _entries.erase(_entries.begin()); }

		for (auto it = _entries.begin(); it != _entries.end();)
		{
			if (temp.GetVar() == it->GetVar()) 
			{
				temp.IncCoeff(it->GetCoeff());
				it = _entries.erase(it);
			}
			else { it++; }
		}

		if (temp.GetCoeff()) { result.push_back(temp); }
	}

	std::sort(result.begin(), result.end(),
		[](PolynomEntry & first, PolynomEntry & second) { return first.GetDegree() > second.GetDegree(); });

	this->entries = result;
}

Polynom Polynom::operator + (const Polynom & other)
{
	std::vector<PolynomEntry> ret;
	this->AddSuch();

	for (auto it : this->entries) 
	{
		it.AddSuch();
		ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar())); 
	}
	for (auto it : other.entries) 
	{
		it.AddSuch();
		ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar())); 
	}

	Polynom Result(ret);
	Result.AddSuch();

	return (Result);
}

Polynom Polynom::operator - (const Polynom & other)
{
	std::vector<PolynomEntry> ret;
	this->AddSuch();

	for (auto it : this->GetEntries()) 
	{
		it.AddSuch();
		ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar()));  
	}
	for (auto it : other.GetEntries()) 
	{
		it.AddSuch();
		ret.push_back(PolynomEntry(-it.GetCoeff(), it.GetVar())); 
	}

	Polynom Result(ret);
	Result.AddSuch();

	return (Result); 
}

Polynom Polynom::operator * (const Polynom & other)
{
	std::vector<PolynomEntry> ret;
	this->AddSuch();

	for (auto it : this->entries)
	{
		for (auto it_oth : other.entries) { ret.push_back(it * it_oth); }
	}

	Polynom Result(ret);
	Result.AddSuch();

	return (Result);
}