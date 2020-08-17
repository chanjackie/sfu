#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Node.h"

Node::Node(int nodeType) {
	type = nodeType;
	parent = NULL;
}

Node::Node(int nodeType, vector<int> nodeKeys) {
	type = nodeType;
	keys = nodeKeys;
	parent = NULL;
}

Node::Node(int nodeType, vector<int> nodeKeys, 
			vector<void*> nodeChildren) {
	type = nodeType;
	keys = nodeKeys;
	children = nodeChildren;
	parent = NULL;
}

Node::Node(int nodeType, vector<int> nodeKeys, 
			vector<void*> nodeChildren, Node* nodeParent) {
	type = nodeType;
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

void Node::setType(int nodeType) {
	type = nodeType;
}

void Node::addKey(int nodeKey) {
	auto index = upper_bound(keys.begin(), keys.end(), nodeKey);
	keys.insert(index, nodeKey);
}

void Node::addChild(void* nodeChild) {
	auto index = upper_bound(children.begin(), children.end(), nodeChild);
	children.insert(index, nodeChild);
}

void Node::addKeyChildPair(int nodeKey, void* nodeChild) {
	auto it = upper_bound(keys.begin(), keys.end(), nodeKey);
	int index = std::distance(keys.begin(), it);
	keys.insert(it, nodeKey);
	children.insert(children.begin()+index, nodeChild);
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

int Node::getType() {
	return type;
}