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
const Node<T> * nth_to_last_element(const Node<T> & root, size_t n)
{
  size_t counter = 0;
  auto iterator = &root;
  auto nth_iterator = &root;

  while (iterator != nullptr) {
    if (counter++ > n) {
      nth_iterator = nth_iterator->next;
    }
    iterator = iterator->next;
  }
  if (counter < n) {
    return nullptr;
  }
  return nth_iterator;
}

int main() {
  size_t n = 99;

  std::vector<size_t> v(100);
  std::iota(std::begin(v), std::end(v), 0);

  auto root = vector_to_linked_list(v);
  print_linked_list(root);

  auto nth_element = nth_to_last_element(root, n);
  if (nth_element == nullptr) {
    printf("no %zuth element available\n", n);
    return 1;
  }
  printf("[%zu]th element to last is %zu\n", n, nth_element->value);
  return 0;
}
