#include "PersonProfile.h"
PersonProfile::PersonProfile(std::string name, std::string email) : m_name(name), m_email(email), numAttVals(0) {
}
PersonProfile::~PersonProfile() {
	for (std::unordered_set<AttValPair*>::iterator it = totalAtt.begin(); it != totalAtt.end();) {
		if (*it != nullptr) {			// For each dynamically allocated AttValPair to keep track of and maintain,
			delete* it;					// delete them.  ... unnecessary dynamic allocation?
			it = totalAtt.erase(it);
		}
		else {
			it++;
		}
	}
};

std::string PersonProfile::GetName() const {
	return m_name;
}

std::string PersonProfile::GetEmail() const {
	return m_email;
}

void PersonProfile::AddAttVAlPair(const AttValPair& attval) {				
	std::unordered_set<std::string>* holder = attTree.search(attval.attribute);		// If the attribute-value pair tree doesn't already
	if (holder != nullptr) {														// contain the 
		std::unordered_set<std::string>::iterator it = holder->find(attval.value);
		if (it == holder->end()) {
			holder->insert(attval.value);
			AttValPair* newPair = new AttValPair(attval.attribute, attval.value);
			totalAtt.insert(newPair);
			numAttVals += 1;
		}
		return;
	}
	std::unordered_set<std::string> temp;
	temp.insert(attval.value);
	AttValPair* newPair = new AttValPair(attval.attribute, attval.value);
	attTree.insert(attval.attribute, temp);
	totalAtt.insert(newPair);
	numAttVals += 1;
}

int PersonProfile::GetNumAttValPairs() const {
	return numAttVals;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
	if (attribute_num >= numAttVals)
		return false;
	std::unordered_set<AttValPair*>::const_iterator it = totalAtt.begin();
	for (int i = 0; i < attribute_num; i++)
		it++;
	attval = *(*it);
	return true;
}