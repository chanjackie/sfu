#pragma once
#include <cstdio>
#include <vector>

using namespace std;

class Node 
{
private:
	vector<int> keys;
	vector<void*> children;
	int type;
	Node* parent;

public:
	Node(int nodeType);
	Node(int nodeType, vector<int> nodeKeys);
	Node(int nodeType, vector<int> nodeKeys, 
		vector<void*> nodeChildren);
	Node(int nodeType, vector<int> nodeKeys, 
		vector<void*> nodeChildren, Node* nodeParent);

	void setKeys(vector<int> nodeKeys);
	void setChildren(vector<void*> nodeChildren);
	void setParent(Node* nodeParent);
	void setType(int nodeType);

	void addKey(int nodeKey);
	void addChild(void* nodeChild);
	void addKeyChildPair(int nodeKey, void* nodeChild);

	vector<int> getKeys();
	vector<void*> getChildren();
	Node* getParent();
	int getType();

};