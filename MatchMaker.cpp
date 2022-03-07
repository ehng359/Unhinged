#include <set>
#include "MatchMaker.h"
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	this->mdb = &mdb;
	this->at = &at;
}

MatchMaker::~MatchMaker() {}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	int total = 0;
	std::vector<EmailCount> eCount;
	std::vector<AttValPair> uniqueAttVals;
	std::vector<AttValPair> compatPairs;
	const PersonProfile* p = mdb->GetMemberByEmail(email);
	AttValPair avp;
	for (int i = 0; i < p->GetNumAttValPairs(); i++) {
		p->GetAttVal(i, avp);
		if (!uniqueAttVals.)
			uniqueAttVals.push_back(avp);
		compatPairs = at->FindCompatibleAttValPairs(avp);
		for (int j = 0; j != compatPairs.size(); j++)
			uniqueAttVals.push_back(compatPairs[j]);
	}
	for (std::vector<AttValPair>::iterator it = uniqueAttVals.begin(); it != uniqueAttVals.end();) {
		if (it != uniqueAttVals.end()) {
			total += mdb->FindingMatchingMembers(*it).size();
			it++;
		}
		else {
			break;
		}
	}
	return eCount;
}