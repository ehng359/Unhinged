#include "AttributeTranslator.h"
AttributeTranslator::AttributeTranslator() {}
AttributeTranslator::~AttributeTranslator() {}
bool AttributeTranslator::Load(std::string filename) {
	std::fstream input(filename);						// Open the file provided by the parameter.
	if (!input.is_open() || input.eof())				// If the file is not open or the end of the file has been reached,
		return false;									// return false (formatting error).
	std::string compat;
	int stringIndex = 0, numCommas = 0;					// Tracker variables to parse through the AttValPairs.
	while (!input.eof()) {								// While the file has not reached the end:
		stringIndex = 0; numCommas = 0;					//	Reset the tracker variables.
		std::getline(input, compat);					//	Retrieve a line of input from the file.
		if (compat == "") {								//	If the line was empty, close the file and return
			input.close();								//	true indicating that the loading process has concluded.
			return true;
		}
		while (numCommas <= 1) {						// Parse through the line until the second comma has been reached.
			if (compat.at(stringIndex) == ',')
				numCommas++;
			stringIndex++;
		}
		std::string source = compat.substr(0, stringIndex - 1);		// Separate the original component into the source AttValPair (as a string)
		std::string associated = compat.substr(stringIndex);		// and its respective compatible AttValPair (as a string)
																	// based upon the location of the second comma, the dividing point.			
		AttValPair first(StringToAttVal(associated));				// Convert the associated string into an attribute value pair.
		std::vector<AttValPair>* temp = compAttMap.search(source);	// Search the Attribute Mappings for the source attribute.
		if (temp == nullptr) {					// If there doesn't exist such source trait,
			std::vector<AttValPair> insert;		// create an empty vector and push back
			insert.push_back(first);			// the associated attribute value pair into it.
			compAttMap.insert(source, insert);	// Insert the source with its respective compatible AttValPair in a vector.
		}
		else {									//	Otherwise,
			temp->push_back(first);				//	push the AttValPair in the vector of associated pairs to a source.
		}
	}
	input.close();		// Close the file and return true once finished.
	return true;
}
std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
	std::string sourceString = AttValToString(source);				// Convert the source AttValPair into a string
	std::vector<AttValPair>* v = compAttMap.search(sourceString);	// and search for it in the Radix Tree if it exists.
	if (v != nullptr)												// If the search results in a valid pointer to a vector of AttValPairs,
		return *v;													// return that vector pointer's contents.
	return std::vector<AttValPair>();								// Otherwise, return an empty vector.
}