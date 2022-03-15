#include "PersonProfile.h"
PersonProfile::PersonProfile(std::string name, std::string email) : m_name(name), m_email(email), numAttVals(0) {
}
PersonProfile::~PersonProfile() {
	for (std::unordered_set<AttValPair*>::iterator it = totalAtt.begin(); it != totalAtt.end();) {
		if (*it != nullptr) {			// For each dynamically allocated AttValPair to keep track of and maintain,
			delete* it;					// delete them.
			it = totalAtt.erase(it);
		}
		else {
			it++;						// If the pointer variable is a nullptr already, move to the next item.
		}
	}
};

std::string PersonProfile::GetName() const {
	return m_name;								// Return a person's name.
}

std::string PersonProfile::GetEmail() const {
	return m_email;								// Return a person's email.
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {				
	std::unordered_set<std::string>* holder = attTree.search(attval.attribute);		// If the attribute-value pair tree already
	if (holder != nullptr) {														// contains the particular attribute value pair:
		std::unordered_set<std::string>::iterator it = holder->find(attval.value);	//		Search the container. If the value association
		if (it == holder->end()) {													//		doesn't already exists with the attribute,
			holder->insert(attval.value);											//		insert a new attribute value pair with the
			AttValPair* newPair = new AttValPair(attval.attribute, attval.value);	//		the provided parameter's attribute and value.
			totalAtt.insert(newPair);	// Insert the sasme pair into a container holding all of a person's attributes.
			numAttVals += 1;			// Increment the number of attribute values a person has.
		}
		return;
	}
	std::unordered_set<std::string> temp;									// If the attribute-value pair tree doesn't already
	temp.insert(attval.value);												// contain the particular attribute:
	AttValPair* newPair = new AttValPair(attval.attribute, attval.value);	// Create a new unordered set for that attribute, insert
	attTree.insert(attval.attribute, temp);									// its value into that set and put it in the Radix tree.
	totalAtt.insert(newPair);												// Insert a newly allocated attribute value pair to store in the attribute
	numAttVals += 1;														// tracker container "totalAtt".
}

int PersonProfile::GetNumAttValPairs() const {
	return numAttVals;							// Return the number of attributes an individual has.
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {	// Retrieve a value at a particular index for an attribute.
	if (attribute_num >= numAttVals)	// If the attribute number is larger than or equal to the number of attributes
		return false;					// a person has, return false.
	std::unordered_set<AttValPair*>::const_iterator it = totalAtt.begin();
	for (int i = 0; i < attribute_num; i++)	// Iterate through the container of all attributes.
		it++;
	attval = *(*it);						// Change the attval to a value and return true, indicating
	return true;							// that a particular value has been found.
}