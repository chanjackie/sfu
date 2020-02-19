#include <cstdio>
#include <vector>
#include "Node.h"

using namespace std;

Node::Node() {
	parent = NULL;
}

Node::Node(vector<int> nodeKeys) {
	keys = nodeKeys;
	parent = NULL;
}

Node::Node(vector<int> nodeKeys, vector<void*> nodeChildren) {
	keys = nodeKeys;
	children = nodeChildren;
	parent = NULL;
}

Node::Node(vector<int> nodeKeys, vector<void*> nodeChildren, Node* nodeParent) {
	keys = nodeKeys;
	children = nodeChildren;
	parent = nodeParent;
}

void Node::setKeys(vector<int> nodeKeys) {
	keys = nodeKeys;
}

void Node::setChildren(vector<void*> nodeChildren) {
	children = nodeChildren;
}

void Node::setParent(Node* nodeParent) {
	parent = nodeParent;
}

vector<int> Node::getKeys() {
	return keys;
}

vector<void*> Node::getChildren() {
	return children;
}

Node* Node::getParent() {
	return parent;
}