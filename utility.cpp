//...
#include "utility.h"
bool operator<(const AttValPair& att, const AttValPair& att2) {
	if (att.attribute < att2.attribute)
		return true;
	else if (att.attribute == att2.attribute) {
		return att.value < att2.value;
	}
	return false;
}

std::string AttValToString(const AttValPair& att) {
    return att.attribute + "," + att.value;
}

AttValPair StringToAttval(const std::string& str) {
    std::istringstream i(str);
    std::string att, val;
    std::getline(i, att, ',');
    val = str.substr(att.size() + 1);
    return AttValPair(att, val);
}

namespace std
{
    template <>
    struct hash<AttValPair>
    {
        size_t operator()(const AttValPair& k) const
        {
            return hash<std::string>() (k.attribute + "," + k.value);
        }
    };
}