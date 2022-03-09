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
	bool LoadDatabase(std::string filename);	// Loads all the members from a database into a radix-tree with associated information.
	std::vector<std::string> FindingMatchingMembers(const AttValPair& input) const;	// Finds all members' emails having a certain AttValPair.
	const PersonProfile* GetMemberByEmail(std::string email) const;	// Finds any PersonProfiles based on email provided.
private:
	RadixTree<std::vector<std::string>> AttValToEmail;	// Data structure mapping AttValPairs to Emails.
	RadixTree<PersonProfile*> EmailToProfile;			// Data structure mapping Emails to PersonProfiles.

	std::vector<PersonProfile*> holder;		// Container used for keeping track of every person for memory deletion.
};
#endif // ! MATCH_MAKER
