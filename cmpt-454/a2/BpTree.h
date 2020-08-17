#pragma once
#include <vector>
#include <cstdio>
#include <string>
#include "Node.h"

using namespace std;

class BpTree
{
private:
	Node* head;
	int len;
	int numValues;

	void splitLeaf(Node* node);
	void splitInterior(Node* node);

public:
	BpTree(int keyLen);
	bool insert(int key, string value);
	bool remove(int key);
	string find(int key);
	void printKeys();
	void printValues();

	Node* getHead();
};