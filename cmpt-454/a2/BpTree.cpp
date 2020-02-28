#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "BpTree.h"

BpTree::BpTree(int keyLen) {
	len = keyLen;
	head = new Node(1);
}

bool BpTree::insert(int key, string value) {
	vector<int> headKeys = head->getKeys();
	if (std::find(headKeys.begin(), headKeys.end(), key) != headKeys.end()) {
		return false;
	}
	head->addKey(key);
	head->addChild(&value);
	return true;
}
bool BpTree::remove(int key) {

	return false;
}

string BpTree::find(int key) {
	if (head == NULL || head->getKeys().empty()) {
		std::cout << "Head NULL or keys empty." << std::endl;
		return "";
	}
	vector<int> headKeys = head->getKeys();
	vector<void*> headChildren = head->getChildren();
	if (head->getType() == 1) {
		for (int i=0; i<headKeys.size(); i++) {
			if (key == headKeys[i]) {
				std::string *stringp = static_cast<std::string*>(headChildren[i]);
				std::string s = *stringp;
				delete stringp;
				return s;
			}
		}
	} else {
		std::cout << "xd" << std::endl;
	}
	return "";

}
void BpTree::printKeys() {
	vector<int> keys = head->getKeys();
	for (int i=0; i<keys.size(); i++) {
		std::cout << keys[i];
	}
	std::cout << std::endl;
}

void BpTree::printValues() {
	vector<void*> values = head->getChildren();
	for (int i=0; i<values.size(); i++) {
		std::string *stringp = static_cast<std::string*>(values[i]);
		std::cout << *stringp;
	}
	std::cout << std::endl;
}

Node* BpTree::getHead() {
	return head;
}