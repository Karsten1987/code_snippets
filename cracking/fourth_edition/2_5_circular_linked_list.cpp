#include <numeric>
#include <vector>
#include <unordered_map>

template<class T = size_t>
struct Node
{
  Node * next;
  T value;
};

template<class T>
Node<T> vector_to_linked_list(const std::vector<T> & vec)
{
  Node<T> root;
  root.value = vec[0];

  Node<T> * tmp = &root;
  for (auto i = 1u; i < vec.size(); ++i) {
    auto new_node = new Node<T>();
    new_node->value = vec[i];
    new_node->next = nullptr;

    tmp->next = new_node;
    tmp = new_node;
  }

  return root;
}

template<class T>
void print_linked_list(const Node<T> & node)
{
  auto iterator = &node;
  while (iterator != nullptr)
  {
    printf("[%zu] --> ", iterator->value);
    iterator = iterator->next;
  }
  printf("[nullptr]\n");
}

template<class T>
const Node<T> * get_circular_node_with_buffer(const Node<T> * root)
{
  auto map = std::unordered_map<const Node<T> *, size_t>();
  auto iterator = root;
  while (iterator != nullptr) {
    if (map.count(iterator) > 0) {
      return iterator;
    } else {
      map[iterator]++;
    }
    iterator = iterator->next;
  }

  return nullptr;
}

template<class T>
const Node<T> * get_circular_node(const Node<T> * root)
{
  auto fast_runner = root;
  auto slow_runner = root;

  while (fast_runner != nullptr && fast_runner->next != nullptr) {
    slow_runner = slow_runner->next;

    fast_runner = fast_runner->next->next;

    if (fast_runner == slow_runner) {
      break;
    }
  }
  if (fast_runner != slow_runner) {
    return nullptr;  // no circles were found
  }

  printf("meeting point was %zu\n", fast_runner->value);
  slow_runner = root;
  while (slow_runner != fast_runner) {
    slow_runner = slow_runner->next;
    fast_runner = fast_runner->next;
  }

  return slow_runner;
}

int main() {
  std::vector<size_t> v(10);
  std::iota(v.begin(), v.end(), 0);
  auto root = vector_to_linked_list(v);
  print_linked_list(root);

  auto last_node = &root;
  while (last_node->next != nullptr) {
    last_node = last_node->next;
  }
  auto circular_node = root.next->next->next;
  last_node->next = circular_node;
  auto false_node = get_circular_node(&root);
  if (!false_node) {
    printf("no circles are found\n");
  } else {
    printf("the circular node is %zu\n", false_node->value);
  }
  return 0;
}

