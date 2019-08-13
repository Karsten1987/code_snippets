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
Node<T> * add(const Node<T> * sum1, const Node<T> * sum2, size_t & carry_over)
{
  if (sum1 == nullptr && sum2 == nullptr) {
    return nullptr;
  }

  Node<T> * next1 = nullptr;
  Node<T> * next2 = nullptr;

  Node<T> * node = new Node<T>();
  node->value = carry_over;
  if (sum1) {
    node->value += sum1->value;
    next1 = sum1->next;
  }
  if (sum2) {
    node->value += sum2->value;
    next2 = sum2->next;
  }
  carry_over = node->value / 10;
  node->value %= 10;

  node->next = add(next1, next2, carry_over);
  return node;
}

template<class T>
Node<T> * get_sum(const Node<T> * sum1, const Node<T> * sum2)
{
  if (sum1 == nullptr && sum2 == nullptr) {
    return nullptr;
  }

  auto iterator1 = sum1;
  auto iterator2 = sum2;

  Node<T> * root = new Node<T>();
  if (iterator1) {
    root->value += iterator1->value;
    iterator1 = iterator1->next;
  }
  if (iterator2) {
    root->value += iterator2->value;
    iterator2 = iterator2->next;
  }

  size_t carry_over = 0u;
  auto root_iterator = root;
  while (iterator1 != nullptr || iterator2 != nullptr) {
    Node<T> * node = new Node<T>();
    node->value = carry_over;
    if (iterator1) {
      node->value += iterator1->value;
      iterator1 = iterator1->next;
    }
    if (iterator2) {
      node->value += iterator2->value;
      iterator2 = iterator2->next;
    }
    carry_over = node->value / 10;
    node->value %= 10;

    root_iterator->next = node;
    root_iterator = root_iterator->next;
  }
  return root;
}

int main() {
  std::vector<size_t> sum1 = {5, 4, 9};  // 945
  std::vector<size_t> sum2 = {1, 2, 3, 4};  // 4321

  auto ll1 = vector_to_linked_list(sum1);
  auto ll2 = vector_to_linked_list(sum2);

  size_t carry_over = 0;
  //auto root = add(&ll1, &ll2, carry_over);
  auto root = get_sum(&ll1, &ll2);
  print_linked_list(*root);
  return 0;
}
