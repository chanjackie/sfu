#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "BpTree.h"

BpTree::BpTree(int keyLen) {
	len = keyLen;
	numValues = 0;
	head = new Node(1);
}

bool BpTree::insert(int key, string value) {
	Node* node = head;
	vector<int> keys = node->getKeys();
	while (!node->getType()) {
		int key, i;
		keys = node->getKeys();
		vector<void*> children = node->getChildren();
		if (key >= keys.back()) {
			i = keys.size();
		} else {
			for (i=0; i<keys.size(); i++) {
				if (key < keys[i]) {
					break;
				}
			}
		}
		node = static_cast<Node*>(children[i]);
	}
	if (std::find(keys.begin(), keys.end(), key) != keys.end()) {
		return false;
	}
	node->addKeyChildPair(key, &value);
	// node->addChild(&value);	
	numValues++;
	if (node->getKeys().size() > len) {
		splitLeaf(node);
	}
	return true;
}
bool BpTree::remove(int key) {
	cout << "Remove not implemented" << endl;
	return false;
}

string BpTree::find(int key) {
	if (head == NULL || head->getKeys().empty()) {
		cout << "Head NULL or keys empty." << endl;
		return "";
	}
	vector<int> headKeys = head->getKeys();
	vector<void*> headChildren = head->getChildren();
	if (head->getType() == 1) {
		for (int i=0; i<headKeys.size(); i++) {
			if (key == headKeys[i]) {
				string *stringp = static_cast<string*>(headChildren[i]);
				string s = *stringp;
				delete stringp;
				return s;
			}
		}
	} else {
		cout << "xd" << endl;
	}
	return "";

}
void BpTree::printKeys() {
	Node* node = head;
	cout << "PRINTING KEYS: " << endl;
	while (!node->getType()) {
		node = static_cast<Node*>(node->getChildren()[0]);
	}
	int count = 0;
	while (count < numValues) {
		vector<int> keys = node->getKeys();
		vector<void*> values = node->getChildren();
		cout << "[ ";
		for (int i=0; i<keys.size(); i++) {
			cout << keys[i] << ' ';
			count++;
		}
		cout << ']';
		node = static_cast<Node*>(values[values.size()-1]);
	}
	cout << endl;
}

void BpTree::printValues() {
	Node* node = head;
	cout << "PRINTING VALUES: " << endl;
	while (!node->getType()) {
		node = static_cast<Node*>(node->getChildren()[0]);
	}
	int count = 0;
	while (count < numValues) {
		vector<void*> values = node->getChildren();
		cout << "[ ";
		for (int i=0; i<values.size(); i++) {
			string *stringp = static_cast<string*>(values[i]);
			cout << *stringp << ' ';
			count++;
		}
		cout << ']';
		node = static_cast<Node*>(values[values.size()-1]);
	}
	cout << endl;
}

Node* BpTree::getHead() {
	return head;
}

void BpTree::splitLeaf(Node* node) {
	Node* newLeaf = new Node(1);
	vector<int> keys = node->getKeys();
	vector<void*> children = node->getChildren();
	int splitKeys = (keys.size()+1)/2;
	int splitPts = (children.size()+1)/2;
	vector<int> firstHalfKeys(keys.begin(), keys.begin()+splitKeys);
	vector<int> newHalfKeys(keys.begin()+splitKeys, keys.end());
	vector<void*> firstHalfPts(children.begin(), children.begin()+splitPts);
	vector<void*> newHalfPts(children.begin()+splitPts, children.end());
	newLeaf->setKeys(newHalfKeys);
	newLeaf->setChildren(newHalfPts);
	firstHalfPts.push_back(newLeaf);
	if (head == node) {
		for (int i=0; i<firstHalfPts.size()-1; i++) {
			cout << *static_cast<string*>(firstHalfPts[i]) << ' ';
		}
		// Node* test = static_cast<Node*>(firstHalfPts[firstHalfPts.size()-1]);
		// firstHalfPts = test->getChildren();
		cout << endl;
		for (int i=0; i<newHalfPts.size()-1; i++) {
			cout << *static_cast<string*>(newHalfPts[i]) << ' ';
		}
		cout << endl;

	}
}

void BpTree::splitInterior(Node* node) {

}