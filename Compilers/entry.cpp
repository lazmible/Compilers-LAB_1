#include "entry.h"

const std::string alphabet =
{
	"abcdefghijklmnopqrstuvwxyz"
};


bool PolynomEntry::operator == (const PolynomEntry & other) const 
{
	return this->var == other.var; 
}

bool PolynomEntry::operator != (const PolynomEntry & other) const 
{
	return this->var != other.var; 
}

const long int PolynomEntry::GetCoeff() const
{
	return this->coeff;
}

const std::vector<Variable> PolynomEntry::GetVar() const
{
	return this->var;
}

PolynomEntry PolynomEntry::operator * (const PolynomEntry & other) const
{
	std::vector<Variable> ret_var_temp;
	std::vector<Variable> ret_var;
	long int ret_coeff = this->GetCoeff() * other.GetCoeff();

	for (auto it : this->GetVar()) { ret_var_temp.push_back(it); }
	for (auto it : other.GetVar()) { ret_var_temp.push_back(it); }

	for (auto alph : alphabet)
	{
		for (auto letter : ret_var_temp)
		{
			Variable temp;
			bool flag = false;
			if (letter.GetLetter() == alph)
			{
				temp.SetLetter(alph);
				temp.IncDegree(letter.GetDegree());
				flag = true;
			}
			if (flag) { ret_var.push_back(temp); }
		}
	}
	return PolynomEntry(ret_coeff, ret_var);
}