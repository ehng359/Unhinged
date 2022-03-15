//MAY use the STL list, vector, set, and unordered_set classes
//MAY have any private member functions or variables you choose to add
//MUST be able to retrieve all related attribute - value pairs for a specified source attributevalue pair in better than O(N) time where N is the number of source attribute - value pairs
//stored in the object.So for example, O(log2 N) would be acceptable(although you can
//	do much better). For big - O analysis purposes, you may assume that there's a constant
//	that all attribute lengths are less than.You may also assume that the number of
//		compatible pairs any attribute - value pair translates to is bounded by a constant(e.g., <
//			10 pairs).
// MUST use your RadixTree class to map source attributes to compatible attributes(for
//			full credit)
#include <string>
#include <vector>
#include <fstream>
#include "provided.h"
#include "RadixTree.h"
#include "utility.h"
#ifndef ATT_TRANS
#define ATT_TRANS
class AttributeTranslator {
public:
	AttributeTranslator();
	~AttributeTranslator();
	bool Load(std::string filename);	// Load's all corresponding compatible attributes mapped to their related attributes.
	std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;	// Returns a list of compatiable attributes
private:																				// given a certain AttValPair.
	RadixTree<std::vector<AttValPair>> compAttMap;	// A Radix Tree containing a vector of AttValPairs which contain all compatiable attributes.
};
#endif