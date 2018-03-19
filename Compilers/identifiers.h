#pragma once

#include "polynom.h"

bool     AddIdentifierInDatabase  (const char * name);
bool     IdentifierExists         (std::string name);
void     PrintIdentifier          (const char * name);
void     AssignIdentifier         (const char * name, Polynom value);
Polynom  GetPolynom               (const char * name);
Polynom  AddIdentifiers           (const char * first, const char * second);
Polynom  SubIdentifiers           (const char * first, const char * second);
Polynom  MulIdentifiers           (const char * first, const char * second);

