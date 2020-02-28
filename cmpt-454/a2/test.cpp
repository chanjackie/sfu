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
	string s("Hi");
	tree->insert(1, s);
	tree->printKeys();
	tree->printValues();

	return 0;
}