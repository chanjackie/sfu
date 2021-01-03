
#include "task02.h"

#include <limits>
#include <set>

#include <iostream>
#include <unordered_map>

using ex5::task2::Node;

std::vector<const Node*>
shortestPath(const Node& from, const Node& to) noexcept {
	std::vector<const Node*> shortestPath;
	std::vector<const Node*> Q;
	std::unordered_map<const Node*, int> dist;
	std::unordered_map<const Node*, int> prev;

	std::vector<Node::Edge> succ = from.getSuccessors();
	bool hasNew = true;
	while (hasNew) {
		hasNew = false;
		for (Node::Edge e : succ) {
			if (std::find(Q.begin(), Q.end(), e.node) == Q.end()) {
				dist.insert({e.node, 9999});
				prev.insert({e.node, -1});
				Q.push_back(e.node);
				hasNew = true;
			}
		}
	}
	dist[&from] = 0;

	while (!Q.empty()) {
		Node = 
	}


	// printf("%ld, %ld, %ld\n", dist.size(), prev.size(), Q.size());



	return shortestPath;
}