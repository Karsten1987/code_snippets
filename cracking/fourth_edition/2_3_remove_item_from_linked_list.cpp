#include <numeric>
#include <vector>

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
void remove_node_from_linked_list(Node<T> * node)
{
  printf("node to be deleted %zu\n", node->value);
  node->value = node->next->value;
  node->next = node->next->next;
}

int main() {
  std::vector<size_t> v(10);
  std::iota(v.begin(), v.end(), 0);
  auto root = vector_to_linked_list(v);
  print_linked_list(root);

  auto current_node = root.next->next->next;
  remove_node_from_linked_list(current_node);
  print_linked_list(root);
  return 0;
}
