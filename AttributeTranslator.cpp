#include "AttributeTranslator.h"
AttributeTranslator::AttributeTranslator() {

}
AttributeTranslator::~AttributeTranslator() {

}
bool AttributeTranslator::Load(std::string filename) {
	std::fstream input(filename);
	if (input.eof())
		return false;
	std::string compat;
	int stringIndex = 0, numCommas = 0;
	while (!input.eof()) {
		stringIndex = 0; numCommas = 0;
		std::getline(input, compat);
		while (compat.at(stringIndex) != ',' || numCommas != 1)
			stringIndex++;
		std::string source = compat.substr(0, stringIndex - 1);
		std::string associated = compat.substr(stringIndex + 1);

		stringIndex = 0;
		while (associated.at(stringIndex) != ',')
			stringIndex++;
		std::string compatAtt = associated.substr(0, stringIndex - 1);
		std::string	compatVal = associated.substr(stringIndex + 1);
		std::vector<AttValPair> insert;
		AttValPair first(compatAtt, compatVal);

		std::vector<AttValPair>* temp = compAttMap.search(source);
		if (temp == nullptr) {
			std::vector<AttValPair> insert;
			AttValPair first(compatAtt, compatVal);
			insert.push_back(first);
			compAttMap.insert(source, insert);
		}
		else {
			temp->push_back(first);
		}
	}
	return true;
}
std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
	std::vector<AttValPair> v;
	return v;
}