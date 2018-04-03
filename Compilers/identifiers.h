#pragma once

#include "polynom.h"

bool     AddIdentifierInDatabase  (const char * name);
bool     IdentifierExists         (std::string name);
void     AssignIdentifier         (const char * name, Polynom value);
void     GenerateError            (const char * message);
Polynom  GetPolynom               (const char * name);

