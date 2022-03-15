#include <fstream>
#include "PersonProfile.h"
#include "MemberDatabase.h"
MemberDatabase::MemberDatabase() {}
MemberDatabase::~MemberDatabase() {
	for (int i = 0; i != holder.size(); i++)	// Cleans up all PersonProfiles after the program finishes executing.
		delete holder[i];
}
bool MemberDatabase::LoadDatabase(std::string filename) {
	std::fstream input(filename);							// Opens file.
	if (!input.is_open() || input.eof())					// If the file is not open or the end of the file has been reached,
		return false;										// return false (formatting error).
	std::string name, email, totalAtt;
	while (!input.eof()) {									// For each line until the end of the file,
		getline(input, name);
		if (name == "") {									// If the input is empty, close the file and
			input.close();									// return true, indicating having reached the end.
			return true;
		}
		getline(input, email);
		getline(input, totalAtt);
		PersonProfile* p = new PersonProfile(name, email);	// Dynamically allcoate a new person profile with name/email.
		holder.push_back(p);								// Insert appropriate information into the radix trees.
		EmailToProfile.insert(email, p);
		int totalAttVals = 0;
		for (int i = 0; i != totalAtt.size(); i++) {	// Convert between a string-number to a useable integer value.
			totalAttVals += totalAtt.at(i) - '0';		// Store the value in totalAttVals.
			totalAttVals *= 10;
		}
		totalAttVals /= 10;

		std::string avp; int division = 0;
		for (int i = 0; i < totalAttVals; i++) {		// For each AttValPair for the individual,
			getline(input, avp);
			//while (avp.at(division) != ',')
			//	division++;
			//AttValPair personAtt(avp.substr(0, division), avp.substr(division + 1));	// Create a AttvalPair for the person
			AttValPair personAtt = StringToAttVal(avp);									// based on the input provided and
			p->AddAttValPair(personAtt);												// add it into their profile.
			std::vector<std::string>* emails = AttValToEmail.search(avp);				
			if (emails == nullptr) {			// If the vector of emails for a certain trait doesn't exist,
				std::vector<std::string> v;		// create one and push the current person's email into it before inserting
				v.push_back(email);				// it into the Radix Tree.
				AttValToEmail.insert(avp, v);
				continue;
			}
			emails->push_back(email);			// If such a vector of emails exists, push the current person's email onto it.
		}
		getline(input, avp);	// Retrieve a blank line.
	}
	input.close();	// Close the file and return true.
	return true;
}
std::vector<std::string> MemberDatabase::FindingMatchingMembers(const AttValPair& input) const {
	std::string attValConvert = AttValToString(input);
	std::vector<std::string>* allMatchingMembers = AttValToEmail.search(attValConvert); // Find all members' emails containing a particular trait.
	if (allMatchingMembers != nullptr)													// If such search returns a valid pointer to the vector,
		return *allMatchingMembers;														// Return a copy of such vector.
	return std::vector<std::string>();													// Otherwise return an empty vector.
}
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
	PersonProfile** person = EmailToProfile.search(email);							// Find a pointer to a PersonProfile based on their
	if (person == nullptr)															// email.
		return nullptr;																// If that PersonProfile doesn't exist (is nullptr) return nullptr,
	return *person;																	// but otherwise return the pointer to the PersonProfile.
}