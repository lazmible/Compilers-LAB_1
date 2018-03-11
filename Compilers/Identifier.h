#pragma once

#include <iostream>
#include <string>

#include "polynom.h"

class Identifier
{
private:
	std::string     key;
	Polynom     * value;
public:
	Identifier(std::string k, Polynom * v)
		: key(k), value(v) {}
	~Identifier() 
		{}
};