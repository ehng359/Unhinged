#include <string>
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
	const unsigned int END_WORD = 129;
	struct Node {
		Node(Node* prev = nullptr) : label(""), targetNode{ 0 } {
			parent = prev;
		}
		std::string label;
		ValueType val;
		Node* parent;
		Node* targetNode [130];		// We'll have it so that the "target node" will have a label in place of the "letter" if there's only one relevant item
	};								// We'll split it further into two different nodes once we insert a value such that it contains a "common factor".
	Node dummyNode;
	// Perhaps place associated values / Attribute pairs
};
// Indicator €
template <typename ValueType>
RadixTree<ValueType>::RadixTree() {}

template <typename ValueType> inline
RadixTree<ValueType>::~RadixTree() {}

template <typename ValueType> inline
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
	std::string k = key;
	Node* iter = dummyNode.targetNode[k.at(0)];
	if (iter == nullptr) {
		dummyNode.targetNode[k.at(0)] = new Node(&dummyNode);
		iter = dummyNode.targetNode[k.at(0)];
		iter->label = k;
		iter->targetNode[END_WORD] = new Node(iter);
		iter = iter->targetNode[END_WORD];
		iter->val = value;
		return;
	}
	if (key == iter->label) {
		if (iter->targetNode[END_WORD])
			iter->targetNode[END_WORD]->val = value;
		else {
			iter->targetNode[END_WORD] = new Node(iter);
			iter->targetNode[END_WORD]->val = value;
		}
	}
	else {
		int numConsec = 0;
		std::string temp;
		while ((numConsec != k.size() || numConsec != iter->label.size()) && k.at(numConsec) == iter->label.at(numConsec)) {
			temp += k.at(numConsec);
			numConsec++;
		}
		iter->label = iter->label.substr(numConsec);
		k = k.substr(numConsec);
		Node* subseq = new Node(iter->parent);
		subseq->label = temp;
		iter->parent->targetNode[subseq->label.at(0)] = subseq;
		iter->parent = subseq;
		subseq->targetNode[iter->label.at(0)] = iter;

		iter = subseq;
		iter->targetNode[k.at(0)] = new Node(iter);
		iter = iter->targetNode[k.at(0)];
		iter->targetNode[END_WORD] = new Node(iter);
		iter->targetNode[END_WORD]->val = value;
		iter->label = k;
	}
	return;
}

template <typename ValueType> inline
ValueType* RadixTree<ValueType>::search(std::string key) const {
	return;
}

#endif RADIX_TREE