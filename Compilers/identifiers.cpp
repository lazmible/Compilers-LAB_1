#include "identifiers.h"

#include <map>

extern std::map<std::string, Polynom> IdentifiersDatabase;

bool AddIdentifierInDatabase(const char * name)
{
	std::pair<std::string, Polynom> data;
	data.first = name;
	return (IdentifiersDatabase.insert(data).second);
}

bool IdentifierExists(std::string name)
{
	return (IdentifiersDatabase.find(name) != IdentifiersDatabase.end());
}

void PrintIdentifier(char * name)
{
	std::cout << (*IdentifiersDatabase.find(name)).second << std::endl;
}

void AssignIdentifier(char * name, Polynom value) // name - NULL
{
	IdentifiersDatabase.erase(name); 
	IdentifiersDatabase.insert(std::make_pair(std::string(name), value));
}

Polynom AddIdentifiers(std::string first, std::string second)
{
	return (*IdentifiersDatabase.find(first)).second + (*IdentifiersDatabase.find(second)).second;
}

Polynom SubIdentifiers(std::string first, std::string second)
{
	return (*IdentifiersDatabase.find(first)).second - (*IdentifiersDatabase.find(second)).second;
}

Polynom MulIdentifiers(std::string first, std::string second)
{
	return (*IdentifiersDatabase.find(first)).second * (*IdentifiersDatabase.find(second)).second;
}