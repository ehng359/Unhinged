//MAY use the STL listand vector classes
//MAY have any private member functions or variables you choose to add
#include <string>
#include "provided.h"
#include "RadixTree.h"
#ifndef  MEMBER_DATABASE
#define MEMBER_DATABASE
class PersonProfile;
class MemberDatabase {
public:
	MemberDatabase();
	~MemberDatabase();
	bool LoadDataFile(std::string filename);
	std::vector<std::string> FindingMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(std::string email) const;
private:
};
#endif // ! MATCH_MAKER
