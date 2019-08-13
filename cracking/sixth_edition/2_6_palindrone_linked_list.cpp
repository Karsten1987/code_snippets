#include "linked_list.hpp"

#include <stack>

template<class T>
bool check_for_palindrone(const Node<T> * root)
{
  if (root == nullptr) {
    return false;
  }

  // Alternatively, instead of iterating once through the complete list to get the size,
  // we can start two runners, one slow, one fast.
  // The fast one reaches the end when the slow runner is in the middle of the list.

  size_t size = 0u;
  auto runner = root;
  while (runner != nullptr) {
    ++size;
    runner = runner->next;
  }
  printf("list has %zu elements\n", size);

  bool is_odd = ((size % 2) == 1);

  std::stack<T> stack;
  runner = root;
  for (size_t i = 0u; i < static_cast<size_t>(size / 2); ++i) {
    stack.push(runner->value);
    runner = runner->next;
  }

  if (is_odd) {
    runner = runner->next;
  }

  for (size_t i = 0u; i < static_cast<size_t>(size / 2); ++i) {
    if (stack.top() != runner->value) {
      return false;
    }
    stack.pop();
    runner = runner->next;
  }

  return (stack.empty() == true);
}

int main()
{
  auto root = create_list({1, 2, 3, 4, 1, 4, 3, 2, 1, 0});
  print_linked_list(root);
  bool is_palindrone = check_for_palindrone(root);
  printf("this list is %sa palidrone\n", is_palindrone ? "" : "not ");
}
