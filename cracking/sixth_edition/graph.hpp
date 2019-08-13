#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <random>
#include <vector>

template<class T = size_t>
struct Node
{
  enum class Flags : uint8_t
  {
    NON_VISITED,
    VISITED,
  };
  Flags flag = Flags::NON_VISITED;
  std::vector<Node *> next_nodes;
  T value;

  Node(T t):
    value(std::move(t))
  {}
};

template<class T = size_t>
struct Graph
{
  std::vector<Node<T> *> available_nodes;
};

template<class T = size_t>
Graph<T> create_random_graph(size_t size)
{
  Graph<T> g;
  if (size == 0) {
    return g;
  }
  g.available_nodes.reserve(size);

  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist_index(0, size - 1);
  std::uniform_int_distribution<std::mt19937::result_type> dist_connection(1, 3);

  for (size_t i = 0u; i < size; ++i) {
    g.available_nodes.push_back(new Node<T>(i));
  }

  for (auto & node : g.available_nodes) {
    auto connection_count = dist_connection(rng);

    std::vector<size_t> used_indexes;
    for (size_t i = 0u; i < connection_count; ++i) {
      size_t index = 0u;
      while (true) {
        index = dist_index(rng);
        auto it = std::find(used_indexes.begin(), used_indexes.end(), index);
        if (it == used_indexes.end()){
          used_indexes.push_back(index);
          break;
        }
      }
      auto & child = g.available_nodes[index];
      node->next_nodes.push_back(child);
    }
  }

  return g;
}

template<class T = size_t>
void print_graph(const Graph<T> & graph)
{
  for (const auto & node : graph.available_nodes) {
    std::cout << "[" << node->value << "]" << std::endl;
    for (const auto & next_node : node->next_nodes) {
      std::cout << "\t[" << next_node->value << "]" << std::endl;
    }
  }
}

#endif  // GRAPH_HPP_
