#pragma once
#include <cstdio>
#include <vector>

using namespace std;

class Node 
{
public:
	vector<int> keys;
	vector<void*> children;
	Node* parent;

	Node();
	Node(vector<int> nodeKeys);
	Node(vector<int> nodeKeys, vector<void*> nodeChildren);
	Node(vector<int> nodeKeys, vector<void*> nodeChildren, Node* nodeParent);

	void setKeys(vector<int> nodeKeys);
	void setChildren(vector<void*> nodeChildren);
	void setParent(Node* nodeParent);

	vector<int> getKeys();
	vector<void*> getChildren();
	Node* getParent();
};