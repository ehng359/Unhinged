//
#include <sstream>
#include <string>
#include "provided.h"
#ifndef UTILITY
#define UTILITY
bool operator<(const AttValPair& att, const AttValPair& att2);
std::string AttValToString(const AttValPair& att);
AttValPair StringToAttval(const std::string& str);
#endif