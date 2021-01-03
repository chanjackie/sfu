
#pragma once

#include <cassert>
#include <algorithm>
#include <iterator>
#include <memory>
#include <ostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace ex6 {

namespace task2 {

////////////////////////////////////////////////////////////////////////////////
// Part 2: Walking the same paths in new ways
////////////////////////////////////////////////////////////////////////////////

// Recall that there were two different types of graphs that we explored in
// exercise 5. The first contained nodes that were simply labeled with integers
// and had weights along edges to neighbors. The second expressed weighted
// anagram relationships among strings. We explore structures for each of these
// below. Notice that they do not satisfy the same API. Your task involves
// designing a system that will work with both anyway.


// A basic graph with simple numerical labels.
// The provided behaviors for nodes, edges, etc. should allow you to use the
// data structures that you desire.

class NumberGraph {
public:
  struct NodeID {
    size_t position;

    bool
    operator==(NodeID other) const noexcept {
      return position == other.position;
    }
    bool
    operator<(NodeID other) const noexcept {
      return position < other.position;
    }
  };

  struct Edge {
    NodeID target;
    size_t weight;
  };

  [[nodiscard]] NodeID
  createNode(int label) {
    nodes.push_back(Node{label, {}});
    return NodeID{nodes.size() - 1};
  }

  void
  addEdge(NodeID from, NodeID to, size_t weight) {
    assert(from.position < nodes.size() && "From node out of bounds.");
    assert(to.position < nodes.size() && "To node out of bounds.");

    nodes[from.position].edges.push_back(Edge{to, weight});
  }

  const std::vector<Edge>&
  getOutgoing(NodeID node) const noexcept {
    assert(node.position < nodes.size() && "Edge request on node out of bounds.");

    return nodes[node.position].edges;
  }

  int
  getLabel(NodeID node) const noexcept {
    assert(node.position < nodes.size() && "Label request on node out of bounds.");

    return nodes[node.position].label;
  }
  
private:

  struct Node {
    int label;
    std::vector<Edge> edges;
  };

  std::vector<Node> nodes;
};


// An "word edit" graph.
// An word edit graph is a fully connected graph between words in a dictionary.
// Because it is fully connected, the edges are implicit. The graph itself
// is nothing more than a vector of `Spelling`s of words in the dictionary.
// The cost from one word to another is the square of the letter frequency
// similarity of the words, provided through the API below.

struct Spelling {
  std::string word;
};


using WordEditGraph = std::vector<Spelling>;


size_t similarity(const Spelling& first, const Spelling& second) noexcept;

}


}


namespace std {
  template <> struct hash<typename ex6::task2::NumberGraph::NodeID> {
    [[nodiscard]] size_t
    operator()(const typename ex6::task2::NumberGraph::NodeID& id) const noexcept {
      return id.position;
    }
  };
}


