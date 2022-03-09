#include <string>
#include <unordered_set>
#include <vector>
#include <iostream> // remove this
#ifndef RADIX_TREE
#define RADIX_TREE

template <typename ValueType>
struct RadixTree {
public:
	RadixTree();
	~RadixTree();
	void insert(std::string key, const ValueType& value);
	ValueType* search(std::string key) const;
private:
	const unsigned int END_WORD = 129;		// Location for the "value node" of the Radix Tree.
	struct Node {
		Node(Node* prev = nullptr) : label(""), targetNode{ 0 } {	// Initialization of each Node when created.
			parent = prev;
		}
		~Node() {					// Every Node is newly allocated and thus
			if (this != nullptr)	// will deallocate itself once the program terminates.
				delete this;
		}
		std::string label;
		ValueType val;
		Node* parent;
		Node* targetNode [130];		// We'll have it so that the "target node" will have a label in place of the "letter" if there's only one relevant item
	};								// We'll split it further into two different nodes once we insert a value such that it contains a "common factor".
	Node* dummyNode;
};
// Indicator €
template <typename ValueType>
RadixTree<ValueType>::RadixTree() {
	dummyNode = new Node;
}

template <typename ValueType> inline
RadixTree<ValueType>::~RadixTree() {}

template <typename ValueType> inline
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
	std::string k = key;
	Node* iter = dummyNode->targetNode[k.at(0)];				// Starting with the first letter key of the word:
	if (iter == nullptr) {
		dummyNode->targetNode[k.at(0)] = new Node(dummyNode);	// If there is a node not already allocated for the letter,
		iter = dummyNode->targetNode[k.at(0)];					// allocate a new node holding the value for insertion.
		iter->label = k;										// Change the label of the node.
		iter->targetNode[END_WORD] = new Node(iter);
		iter = iter->targetNode[END_WORD];
		iter->val = value;										// Insert the value into the value node spot and return.
		return;
	}

	if (key == iter->label) {								// If the current node's label is the key itself,
		if (iter->targetNode[END_WORD])						// Update the value if there exists one.
			iter->targetNode[END_WORD]->val = value;
		else {
			iter->targetNode[END_WORD] = new Node(iter);	// Create the value node if there doesn't exist one.
			iter->targetNode[END_WORD]->val = value;
		}
	}
	else {
		int numConsec = 0;
		std::string temp;
		while (true) {
			temp = "";
			numConsec = 0;
			while ((numConsec != k.size() && numConsec != iter->label.size()) && k.at(numConsec) == iter->label.at(numConsec)) {
				temp += k.at(numConsec);										// Count the length of matching characters between
				numConsec++;													// the current label and key.
			}
			if (numConsec == k.size() && numConsec != iter->label.size()) {		// If the number of letters consecutive matches
				Node* subseq = new Node(iter->parent);							// the total size of the key, create a new node
				subseq->label = k;												// containing the totality of the key and update
				iter->label = iter->label.substr(numConsec);					// the current node's label to be a substring of
				iter->parent->targetNode[k.at(0)] = subseq;						// its prior label, based on matching letters.
				iter->parent = subseq;
				subseq->targetNode[iter->label.at(0)] = iter;
				subseq->targetNode[END_WORD] = new Node(iter);					// Insert a dynamically allocated the value node into the tree.
				subseq->targetNode[END_WORD]->val = value;
				return;
			}
			if (numConsec != k.size() && numConsec != iter->label.size()) {		// If the number consecutive letters is a prefix of both strings,
				k = k.substr(numConsec);										// Add a new node to the radix tree containing the common prefix
				iter->label = iter->label.substr(numConsec);					// and adjust it such that the old node's label doesn't have said
				Node* subseq = new Node(iter->parent);							// prefix.
				subseq->label = temp;
				iter->parent->targetNode[subseq->label.at(0)] = subseq;
				iter->parent = subseq;
				subseq->targetNode[iter->label.at(0)] = iter;

				iter = subseq;												// Traverse backwards to the new parent node.
				iter->targetNode[k.at(0)] = new Node(iter);					// Allocate a new node for the now-empty branch containing
				iter = iter->targetNode[k.at(0)];							// the old node and pass the new key in with its value
				iter->targetNode[END_WORD] = new Node(iter);				// into the tree.
				iter->targetNode[END_WORD]->val = value;
				iter->label = k;
				return;
			}													// Case where the entirety of the current label is a prefix to the key.
			k = k.substr(numConsec);							// Set k to be a substring of itself without the current node label's prefix.
			Node* t = iter->targetNode[k.at(0)];
			if (t == nullptr) {									// If there exists no node for the remainder of the key, allocate
				iter->targetNode[k.at(0)] = new Node(iter);		// new memory for a node and place value node into the tree as well
				iter = iter->targetNode[k.at(0)];				// to sore the value.
				iter->targetNode[END_WORD] = new Node(iter);
				iter->targetNode[END_WORD]->val = value;
				iter->label = k;
				return;
			}
			else {
				iter = t;		// If there does exist such node for the raminder of the key, move the node iterator forward to that node.
			}
		}
	}
	return;
}

template <typename ValueType> inline
ValueType* RadixTree<ValueType>::search(std::string key) const {
	std::string k = key;
	Node* iter = dummyNode->targetNode[k.at(0)];
	if (!iter)					// If the node at the "starting letter" of the key is not present,
		return nullptr;			// return a pointer to nothing.
	while (iter && k != "") {
		if (iter->label == k)										// While the key isn't empty and iter isn't nullptr,
			return &(iter->targetNode[END_WORD]->val);				// If the label matches, return the address of the value node's value.
		else if (iter->label == k.substr(0, iter->label.size())) {	// Otherwise, if the substring of the key of label-length matches 
			if (k.size() == iter->label.size())						// the length:
				return &(iter->targetNode[END_WORD]->val);			//		Return the address of the value node's value if the label and key
			k = k.substr(iter->label.size());						//		have the same size.
			iter = iter->targetNode[k.at(0)];						// Else shorten the key to be without the prefix and move to the next node.
		}
		else
			return nullptr;					// If such key cannot be found in the Radix tree, return nullptr.
	}
	return nullptr;
}

#endif