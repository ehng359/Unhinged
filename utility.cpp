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