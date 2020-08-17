#include "BpTree.h"
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	// vector<int> keys{4, 9, 16};
	// vector<Node*> children;
	// Node *a = new Node(keys);
	// vector<int> test = a->getKeys();
	// for (int i=0; i<3; i++) {
	// 	cout << test[i] << endl;
	// }

	BpTree* tree = new BpTree(3);
	string s("what");
	tree->insert(4, s);
	s = "fudge";
	tree->insert(23, s);
	s = "the";
	tree->insert(14, s);
	s = "doin";
	tree->insert(63, s);
	s = "we";
	tree->insert(47, s);
	s = "is";
	tree->insert(38, s);
	tree->printKeys();
	tree->printValues();

	return 0;
}