#include "graph.hpp"

#include <queue>

constexpr size_t DFS = 0u;
constexpr size_t BFS = 1u;

template<size_t T>
struct TraversalMode;

template<>
struct TraversalMode<DFS>
{};

template<>
struct TraversalMode<BFS>
{};

template<
  class T = size_t,
  class TRAVERSE_MODE,
  typename std::enable_if<
    std::is_same<TraversalMode<DFS>, TRAVERSE_MODE>::value, TRAVERSE_MODE>::type * = nullptr>
bool route_exists(Node<T> * start, Node<T> * goal)
{
  if (goal == nullptr) {
    return false;
  }

  if (start == nullptr) {
    return false;
  }

  if (start->flag == Node<T>::Flags::NON_VISITED) {
    printf("visiting %zu\n", start->value);
    start->flag = Node<T>::Flags::VISITED;
  } else {
    return false;
  }

  if (start->value == goal->value) {
    return true;
  }
  for (auto & node : start->next_nodes) {
    if (route_exists<T, TRAVERSE_MODE>(node, goal)) {
        return true;
    }
  }

  return false;
}

template<
  class T = size_t,
  class TRAVERSE_MODE,
  typename std::enable_if<
    std::is_same<TraversalMode<BFS>, TRAVERSE_MODE>::value, TRAVERSE_MODE>::type * = nullptr>
bool route_exists(Node<T> * start, Node<T> * goal)
{
  if (goal == nullptr) {
    return false;
  }
  if (start == nullptr) {
    return false;
  }

  std::queue<Node<T> *> queue;
  queue.push(start);

  while (!queue.empty())
  {
    auto top = queue.front();
    queue.pop();
    if (top->flag == Node<T>::Flags::VISITED) {
      continue;
    }

    top->flag = Node<T>::Flags::VISITED;
    if (top->value == goal->value) {
      return true;
    }

    for (auto & node : top->next_nodes) {
      queue.push(node);
    }
  }

  return false;
}

int main()
{
  auto graph = create_random_graph<size_t>(10);
  print_graph(graph);

  auto start = graph.available_nodes[1];
  auto goal = graph.available_nodes[5];
  bool has_route = route_exists<size_t, TraversalMode<BFS>>(start, goal);
  printf("route between %zu and %zu %s\n", start->value, goal->value, has_route ? "exists" : "does not exist");
  return 0;
}
