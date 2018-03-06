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

const long int Polynom::GetDegree() const
{
	long int result = 0;
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
	
	for (auto it : this->GetEntries()) { it.AddSuch(); }

	std::vector<PolynomEntry> _entries = this->GetEntries();

	while (!_entries.empty())
	{
		PolynomEntry temp = *(_entries.begin());
		// shitcode start
		for (auto it = _entries.begin(); it != _entries.end();)
		{
			if (*it == temp) { it = _entries.erase(it); }

			else { it++; }
		}
		// shitcode end
		for (auto it = _entries.begin(); it != _entries.end();)
		{
			if (temp.GetVar() == it->GetVar()) 
			{
				temp.IncCoeff(it->GetCoeff());
				it = _entries.erase(it);
			}
			else { it++; }
		}

		result.push_back(temp);
	}	
	this->entries = result;
}

Polynom Polynom::operator + (const Polynom & other)
{
	std::vector<PolynomEntry> ret;

	this->AddSuch();

	for (auto it : this->entries) { ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar())); }
	for (auto it : other.entries) { ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar())); }

	this->AddSuch();

	std::sort(ret.begin(), ret.end(),
		[](PolynomEntry & first, PolynomEntry & second) { return first.GetDegree() > second.GetDegree(); });

	Polynom _ret(ret);

	return (_ret); // TODO: Make a good constructor to - (return Polynom(ret));
}

Polynom Polynom::operator - (const Polynom & other)
{
	std::vector<PolynomEntry> ret;
	
	this->AddSuch();

	for (auto it : this->GetEntries()) { ret.push_back(PolynomEntry(it.GetCoeff(), it.GetVar()));  }
	for (auto it : other.GetEntries()) { ret.push_back(PolynomEntry(-it.GetCoeff(), it.GetVar())); }

	this->AddSuch();
	
	std::sort(ret.begin(), ret.end(),
		[](PolynomEntry & first, PolynomEntry & second) { return first.GetDegree() > second.GetDegree(); });

	Polynom _ret(ret);

	return (_ret); // TODO: Make a good constructor to - (return Polynom(ret));
}

Polynom Polynom::operator * (const Polynom & other)
{
	std::vector<PolynomEntry> ret;

	this->AddSuch();

	for (auto it : this->entries)
	{
		for (auto it_oth : other.entries)
		{
			ret.push_back(it * it_oth);
		}
	}
	Polynom _ret(ret);

	_ret.AddSuch();
	
	std::sort(ret.begin(), ret.end(),
		[](PolynomEntry & first, PolynomEntry & second) { return first.GetDegree() > second.GetDegree(); });

	return _ret;
}