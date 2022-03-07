// Avoid O(n)
// MAY use ANY STL containers you like
// MAY have any private member functions or variables you choose to add
#include <vector>
#include "provided.h"
#ifndef  MATCH_MAKER
#define MATCH_MAKER
class MatchMaker {
	MatchMaker();
	~MatchMaker();
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
};
#endif // ! MATCH_MAKER
