#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>

/// Implementation of Graph data structure
/// based on adjacency list. Also, covers
/// basic algorithms like dfs, bfs, reachibility
/// etc.
/// Adjacency matrix implementation should be similar.
/// Graph is both directed and undirected
/// Graph has node keys and weighted edges
/// Edges can be unweighted but that just means
/// the weight is set to 1.

using namespace std;

// fwd decl
class Node;

class NodeWeightPairHashFctor {
  public:
    size_t operator()(const pair<shared_ptr<Node>, int>&
                          given_pair) const {
        return hash<shared_ptr<Node>>{}(given_pair.first);
    }
};

class NodeWeightPairEqualFctor {
  public:
    bool operator()(
        const pair<shared_ptr<Node>, int>& pair1,
        const pair<shared_ptr<Node>, int>& pair2) const {
        return pair1.first == pair2.first;
    }
};

using NeighborsSet =
    unordered_set<pair<shared_ptr<Node>, int>,
                  NodeWeightPairHashFctor,
                  NodeWeightPairEqualFctor>;

// Adjacency List Type
// Map from a node to a set of neighboring nodes
// Why hash map? Can lookup a node/vertex in the whole
// graph O(1) time.
// Why hash set? Can lookup a given node's child in
// O(1) time.
using AdjacencyList =
    unordered_set<shared_ptr<Node>>;

/// Node for graph.
/// Why string typed key? Can templatize easily.
class Node {
  public:
    Node()
        : key()
        , neighbors() {}

    bool operator==(const Node& other) {
        return this->key == other.key;
    }

    //
    /// Node's key value
    //
    string key;

    //
    /// Node API's
    //

    // Add neighbor if there isn't one already.
    // Else asserts (neighbor already exists)
    void add_neighbor(shared_ptr<Node> node,
                      int weight = 1) {
        assert(node);
        auto pair = make_pair(node, weight);
        if (neighbors.find(pair) != neighbors.end())
            assert(false); // neighbor already exists
        neighbors.insert(pair);
    }

    // Removes neighbor if there exists one.
    // Else, silently returns.
    void remove_neighbor(shared_ptr<Node> node) {
        assert(node);
        auto pair = make_pair(node, -1);
        if (neighbors.find(pair) != neighbors.end())
            neighbors.erase(pair);
    }

  private:
    NeighborsSet neighbors;
};

class Graph {
  public:
    Graph()
        : adj_list() {}

    void add_node(shared_ptr<Node> node) {
        assert(node);
        if (adj_list.find(node) != adj_list.end())
            assert(false);   // already exists
        adj_list.insert(node);
    }

    void add_edge(shared_ptr<Node> source,
                  shared_ptr<Node> dest,
		  int weight = 1) {
      assert(source && dest);
      if (adj_list.find(source) == adj_list.end())
	add_node(source);
      if (adj_list.find(source) == adj_list.end())
	add_node(dest);
      source->add_neighbor(dest, weight);
    }

  void add_undirected_edge(shared_ptr<Node> source,
			   shared_ptr<Node> dest,
			   int weight = 1) {
    assert(source && dest);
    add_edge(source, dest);
    add_edge(dest, source);    
  }

  private:
    AdjacencyList adj_list;
};

int main() {
    Graph g;
    cout << "hello" << endl;
    return 0;
}
