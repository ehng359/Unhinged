// Avoid O(n)
// MAY use ANY STL containers you like
// MAY have any private member functions or variables you choose to add
#include <vector>
#include <algorithm>
#include "provided.h"
#include "utility.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "PersonProfile.h"
#ifndef  MATCH_MAKER
#define MATCH_MAKER

bool operator>(const EmailCount& a, const EmailCount& b);

class MatchMaker {
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	~MatchMaker();
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
	const MemberDatabase* mdb;
	const AttributeTranslator* at;
};
#endif // ! MATCH_MAKER
