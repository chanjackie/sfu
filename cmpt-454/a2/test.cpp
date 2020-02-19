#include "Node.h"
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> keys{4, 9, 16};
	vector<Node*> children;
	Node *a = new Node(keys);
	vector<int> test = a->getKeys();
	for (int i=0; i<3; i++) {
		cout << test[i] << endl;
	}
	return 0;
}