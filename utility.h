//
#include <sstream>
#include <string>
#include "provided.h"
#ifndef UTILITY
#define UTILITY
bool operator<(const AttValPair& att, const AttValPair& att2);	// Defines the < operator for attribute-value pairs.
std::string AttValToString(const AttValPair& att);	// Allows conversion between attribute-values and strings.
AttValPair StringToAttVal(const std::string& str);	// Allows backward conversion between strings and attribute-values.
#endif