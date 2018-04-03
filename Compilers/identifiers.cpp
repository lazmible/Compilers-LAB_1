#include "identifiers.h"
#include <map>

extern std::map<std::string, Polynom> IdentifiersDatabase;
extern std::size_t Lines;

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

void AssignIdentifier(const char * name, Polynom value) 
{
	IdentifiersDatabase.erase(name); 
	IdentifiersDatabase.insert(std::make_pair(std::string(name), value));
}

Polynom GetPolynom(const char * name)
{
	return (IdentifiersDatabase.find(name)->second);
}

void GenerateError(const char * error)
{
	std::cout << error << ". On line: " << Lines << std::endl;
	system("pause");
	exit(1);
}
