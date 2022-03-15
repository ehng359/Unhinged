#include <vector>
#include <algorithm>
#include "provided.h"
#include "utility.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "PersonProfile.h"
#ifndef  MATCH_MAKER
#define MATCH_MAKER

bool operator>(const EmailCount& a, const EmailCount& b);	// Defining the operator greater than for sorting EmailCounts.

class MatchMaker {
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);	// Constructs the MatchMaker object by mediating between the translator and member database.
	~MatchMaker();															// Destructs the MatchMaker class.
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
	const MemberDatabase* mdb;		// A pointer holding the addresss of the member database.
	const AttributeTranslator* at;	// A pointer holding the address to all attribute value pair compatabilities.
};
#endif // ! MATCH_MAKER
