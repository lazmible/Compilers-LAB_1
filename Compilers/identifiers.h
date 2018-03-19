#pragma once

#include "polynom.h"

bool AddIdentifierInDatabase(const char * name);
bool IdentifierExists(std::string name);
void PrintIdentifier(char * name);
void AssignIdentifier(char * name, Polynom value);
Polynom AddIdentifiers(std::string first, std::string second);
Polynom SubIdentifiers(std::string first, std::string second);
Polynom MulIdentifiers(std::string first, std::string second);

