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
	PersonProfile(std::string name, std::string email);	// Constructor for the PersonProfile class.
	~PersonProfile();									// Destructor for the PersonProfile class.
	std::string GetName() const;	// Retrieve a person's name.
	std::string GetEmail() const;	// Retrieve a person's email.
	void AddAttVAlPair(const AttValPair& attval);	// Adding AttValPairs to a person's list of attributes.
	int GetNumAttValPairs() const;					// Retrieving the number of total attributes one has.
	bool GetAttVal(int attribute_num, AttValPair& attval) const;	// Retrieve a particular AttValPair, provided an index.
private:
	std::string m_name;
	std::string m_email;
	int numAttVals;
	// One or more attribute-value pairs that describe the member.
	std::unordered_set<AttValPair*> totalAtt;
	RadixTree<std::unordered_set<std::string>> attTree;
};
#endif