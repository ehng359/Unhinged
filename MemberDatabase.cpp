#include <fstream>
#include "PersonProfile.h"
#include "MemberDatabase.h"
MemberDatabase::MemberDatabase() {}
MemberDatabase::~MemberDatabase() {

}
bool MemberDatabase::LoadDatabase(std::string filename) {
	std::fstream input(filename);
	if (!input.is_open() || input.eof())
		return false;
	std::string name, email, totalAtt;
	while (!input.eof()) {
		getline(input, name);
		if (name == "") {
			input.close();
			return true;
		}
		getline(input, email);
		getline(input, totalAtt);
		PersonProfile* p = new PersonProfile(name, email);
		EmailToProfile.insert(email, p);
		int totalAttVals = 0;
		for (int i = 0; i != totalAtt.size(); i++) {
			totalAttVals += totalAtt.at(i) - '0';
			totalAttVals *= 10;
		}
		totalAttVals /= 10;

		std::string avp; int division = 0;
		for (int i = 0; i < totalAttVals; i++) {
			getline(input, avp);
			while (avp.at(division) != ',')
				division++;
			AttValPair personAtt(avp.substr(0, division), avp.substr(division + 1));
			p->AddAttVAlPair(personAtt);
			std::vector<std::string>* emails = AttValToEmail.search(avp);
			if (emails == nullptr) {
				std::vector<std::string> v;
				v.push_back(email);
				AttValToEmail.insert(avp, v);
				continue;
			}
			emails->push_back(email);
		}
		getline(input, avp);
	}
	input.close();
	return true;
}
std::vector<std::string> MemberDatabase::FindingMatchingMembers(const AttValPair& input) const {
	std::string attValConvert = input.attribute + "," + input.value;
	std::vector<std::string>* allMatchingMembers = AttValToEmail.search(attValConvert);
	return *allMatchingMembers;
}
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
	PersonProfile** person = EmailToProfile.search(email);
	if (person == nullptr)
		return nullptr;
	return *person;
}