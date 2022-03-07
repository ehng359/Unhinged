#include <unordered_set>
#include "MatchMaker.h"
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	this->mdb = &mdb;
	this->at = &at;
}

MatchMaker::~MatchMaker() {}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	int total = 0;
	std::vector<EmailCount> total;
	std::unordered_set<AttValPair> uniqueAttVals;
	std::unordered_set<AttValPair> uniqueCompatAttVals;
	std::vector<AttValPair> compatPairs;
	const PersonProfile* p = mdb->GetMemberByEmail(email);
	AttValPair avp;
	for (int i = 0; i < p->GetNumAttValPairs(); i++) {
		p->GetAttVal(i, avp);
		uniqueAttVals.insert(avp);
		compatPairs = at->FindCompatibleAttValPairs(avp);
		for (int j = 0; j < compatPairs.size(); j++)
			uniqueCompatAttVals.insert(compatPairs[j]);
	}
	for (std::unordered_set<AttValPair>::iterator it = uniqueAttVals.begin(), ct = uniqueCompatAttVals.begin(); it != uniqueAttVals.end() && ct != uniqueCompatAttVals.end();) {
		if (it != uniqueAttVals.end()) {
			total += mdb->FindingMatchingMembers(*it).size();
			it++;
		}
		else if (ct != uniqueCompatAttVals.end()) {
			total += mdb->FindingMatchingMembers(*ct).size();
			ct++;
		}
	}
}