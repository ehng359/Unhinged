//...
#include "utility.h"
bool operator<(const AttValPair& att, const AttValPair& att2) {	// If the attribute is "less" than the other, return true.
	if (att.attribute < att2.attribute)
		return true;
	else if (att.attribute == att2.attribute) {		// If they're equal, return the if the first value is lesser than the second value.
		return att.value < att2.value;
	}
	return false;		// Else return false.
}

std::string AttValToString(const AttValPair& att) {
    return att.attribute + "," + att.value;		// Return the format of an attribute-value pair in string-form.
}

AttValPair StringToAttVal(const std::string& str) {	// Accept a string and then transform it into a AttValPair.
    std::istringstream i(str);
    std::string att, val;
    std::getline(i, att, ',');			// Uses getline up to the first ',' to retrieve the attribute name.
    val = str.substr(att.size() + 1);	// Use substring in order to separate the two aspects of the AttValPair.
    return AttValPair(att, val);
}