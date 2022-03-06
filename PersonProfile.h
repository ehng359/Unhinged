#include <string>
#include <unordered_set>
#include "provided.h"
#include "RadixTree.h"
// MAY use the STL list, vector, set, and unordered_set classes
// MAY have any private member functions or variables you choose to add
#ifndef PERSON_PROFILE
#define PERSON_PROFILE
class PersonProfile {
public:
	PersonProfile(std::string name, std::string email);
	~PersonProfile();
	std::string GetName() const;
	std::string GetEmail() const;
	void AddAttVAlPair(const AttValPair& attval);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	std::string m_name;
	std::string m_email;
	int numAttVals;
	// One or more attribute-value pairs that describe the member.
	std::unordered_set<AttValPair*> totalAtt;
	RadixTree<std::unordered_set<std::string>> attTree;
};
#endif