#include "linked_list.hpp"

template<class T>
Node<T> * sum_rec(const Node<T> * sum1, const Node<T> * sum2, size_t carry_over)
{
  if (sum1 == nullptr && sum2 == nullptr) {
    return nullptr;
  }

  Node<T> * next1 = nullptr;
  Node<T> * next2 = nullptr;

  auto sum = carry_over;
  if (sum1) {
    sum += sum1->value;
    next1 = sum1->next;
  }
  if (sum2) {
    sum += sum2->value;
    next2 = sum2->next;
  }

  auto new_node = new Node<T>(sum % 10);
  new_node->next = sum_rec(next1, next2, sum / 10);

  return new_node;
}

template<class T>
Node<T> * sum_lists(const Node<T> * sum1, const Node<T> * sum2) {
  return sum_rec(sum1, sum2, 0u);
}

int main()
{
  auto sum1 = create_list({7, 1, 6});
  auto sum2 = create_list({5, 9, 2});

  print_linked_list(sum1);
  print_linked_list(sum2);

  auto sum = sum_lists(sum1, sum2);
  print_linked_list(sum);
  return 0;
}
