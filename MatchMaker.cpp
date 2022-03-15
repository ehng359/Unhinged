#include "MatchMaker.h"
#include <unordered_map>
#include <unordered_set>
#include <map>

bool operator>(const EmailCount& a, const EmailCount& b) {	// Defined comparison for the EmailCount class.
	if (a.count > b.count)			// If the amount of relevant attributes of object a is greater than
		return true;				// object b, return true.
	else if (a.count == b.count)	// Else if the amount of compatible attributes are equal,
		return a.email < b.email;	// return the emails in alphabetical order.
	return false;					// Otherwise return false.
}

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	this->mdb = &mdb;	// Give the MatchMaker object the address to the entire member database.
	this->at = &at;		// Give the MatchMaker object the address to the mappings to all compatible AttValPairs to AttValPairs.
}

MatchMaker::~MatchMaker() {}	// MatchMaker destructor.

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	if (threshold <= 0)		// If the threshold to minimum matches needed is lower than or equal to 0, change it to 1.
		threshold = 1;

	std::unordered_map<std::string, int> MatchMap;	// Container mapping emails to number of relevant compatible attributes.
	std::vector<AttValPair> compatPairs;			// Container for holding all compatible AttValPairs for a given Attribute.
	std::vector<std::string> matching;				// Container holding a lists of emails with a particular attribute.s
	std::unordered_set<std::string> allCompats;		// Container holding the string-version of all compatible AttValPairs for a person's attribute set.

	const PersonProfile* p = mdb->GetMemberByEmail(email);	// Retrive the person profile of the individual via the provided email.
	AttValPair avp;
	for (int i = 0; i < p->GetNumAttValPairs(); i++) {			// For each attribute of an individual:
		p->GetAttVal(i, avp);									// Retrieve the attribute value and put it into avp.
		compatPairs = at->FindCompatibleAttValPairs(avp);		// Find all the compatible values for that AttValPair in avp,
		for (int j = 0; j != compatPairs.size(); j++) {			// and insert it into the container allCompats which holds
			allCompats.insert(AttValToString(compatPairs[j]));	// an unordered set of strings for relevant comopatible values.
		}
	}

	for (std::unordered_set<std::string>::iterator it = allCompats.begin(); it != allCompats.end(); it++) {	// For each set of compatible values:
		matching = mdb->FindingMatchingMembers(StringToAttVal(*it));	// Retrieve all members holding the compatible value at hand,
		for (int i = 0; i != matching.size(); i++) {					// and for each email, if they don't exist in the map of "total matches"
			if (MatchMap.find(matching[i]) == MatchMap.end())			// set their value to one (referring to having one compatible AttValPair)
				MatchMap[matching[i]] = 1;
			else
				MatchMap[matching[i]] += 1;								// Or otherwise increment the count of the number of relevant/compatible AttValPairs.
		}
	}

	std::vector<EmailCount> eCount;
	for (std::unordered_map<std::string, int>::iterator it = MatchMap.begin(); it != MatchMap.end(); it++) {	// Iterating through each member that has minimum one compatible attribute,
		if (it->second >= threshold && it->first != email) {		// If the number of compatible attributes exceeds or meets the threshold level,
			eCount.push_back(EmailCount(it->first, it->second));	// push the email and its count into the vector of EmailCounts.
		}
	}
	std::sort(eCount.begin(), eCount.end(), operator>);	// Sort EmailCounts based on their relevant matches first and then by alphabetical ordering in the email name.
	return eCount;	// Return the vector of EmailCounts by which meet the requirement threshold of having threshold number of compatible attributes.
}