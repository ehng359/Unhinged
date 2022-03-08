#include "MatchMaker.h"
#include <unordered_map>
#include <unordered_set>
#include <map>
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	this->mdb = &mdb;
	this->at = &at;
}

MatchMaker::~MatchMaker() {}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	int total = 0;
	std::unordered_map<std::string, int> MatchMap;
	std::vector<AttValPair> compatPairs;
	std::vector<std::string> matching;
	std::unordered_set<std::string> allCompats;
	const PersonProfile* p = mdb->GetMemberByEmail(email);
	AttValPair avp;
	for (int i = 0; i < p->GetNumAttValPairs(); i++) {
		p->GetAttVal(i, avp);
		compatPairs = at->FindCompatibleAttValPairs(avp);
		for (int j = 0; j != compatPairs.size(); j++) {
			allCompats.insert(AttValToString(avp));
		}
	}
	for (std::unordered_set<std::string>::iterator it = allCompats.begin(); it != allCompats.end(); it++) {
		matching = mdb->FindingMatchingMembers(StringToAttval(*it));
		for (int i = 0; i != matching.size(); i++) {
			if (MatchMap.find(matching[i]) == MatchMap.end())
				MatchMap[matching[i]] = 1;
			else
				MatchMap[matching[i]] += 1;
		}
	}
	std::vector<EmailCount> eCount;
	for (std::unordered_map<std::string, int>::iterator it = MatchMap.begin(); it != MatchMap.end(); it++) {
		if (it->second >= threshold && it->first != email) {
			eCount.push_back(EmailCount(it->first, it->second));
		}
	}
	return eCount;
}