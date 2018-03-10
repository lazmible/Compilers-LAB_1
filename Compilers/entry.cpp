#include "entry.h"

const std::string alphabet =
{
	"abcdefghijklmnopqrstuvwxyz"
};

std::ostream & operator << (std::ostream & stream, const PolynomEntry & entry)
{
	if (entry.coeff != 1 && entry.coeff != -1) { stream << std::abs(entry.coeff); }
	for (auto it : entry.var) { stream << it; }
	return (stream);
}

void PolynomEntry::AddSuch()
{
	std::vector<Variable> ret_var;

	for (auto alph : alphabet)
	{
		Variable temp;
		bool flag = false;
		for (auto letter : this->GetVar())
		{
			if (letter.GetLetter() == alph)
			{
				temp.SetLetter(alph);
				temp.IncDegree(letter.GetDegree());
				flag = true;
			}
		}
		if (flag) 
		{
			ret_var.push_back(temp); 
		}
	}

	this->var = ret_var;
}

void PolynomEntry::IncCoeff(long c)
{
	this->coeff += c;
}

void PolynomEntry::Append(Variable var)
{
	this->var.push_back(var);
	this->AddSuch();
}

bool PolynomEntry::operator == (const PolynomEntry & other) const 
{
	return (this->var == other.var && this->GetCoeff() == other.GetCoeff()); 
}

bool PolynomEntry::operator != (const PolynomEntry & other) const 
{
	return (!((*this) == other));
}

const long PolynomEntry::GetCoeff() const
{
	return (this->coeff);
}

const std::vector<Variable> PolynomEntry::GetVar() const
{
	return (this->var);
}

const long PolynomEntry::GetDegree() const
{
	long int result = 0;
	
	for (auto it : this->GetVar())
	{
		result += it.GetDegree();
	}
	return (result);
}

PolynomEntry PolynomEntry::operator * (const PolynomEntry & other) const
{
	std::vector<Variable> ret_var_temp;
	std::vector<Variable> ret_var;
	long ret_coeff = this->GetCoeff() * other.GetCoeff();

	for (auto it : this->GetVar()) { ret_var_temp.push_back(it); }
	for (auto it : other.GetVar()) { ret_var_temp.push_back(it); }

	PolynomEntry ret(ret_coeff, ret_var_temp);
	ret.AddSuch();

	return (ret);
}
