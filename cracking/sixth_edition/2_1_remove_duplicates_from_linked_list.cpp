#include "linked_list.hpp"

#include <unordered_set>

template<class T>
void remove_duplicates_w_buffer(Node<T> * root)
{
  if (root == nullptr) {
    return;
  }

  std::unordered_set<T> set;
  auto runner = root;
  Node<T> * previous = nullptr;
  while (runner != nullptr) {
    if (set.count(runner->value) == 1) {
      auto node_to_be_deleted = runner;
      previous->next = runner->next;
      delete node_to_be_deleted;
      node_to_be_deleted = nullptr;
    } else {
      set.insert(runner->value);
      previous = runner;
    }

    runner = runner->next;
  }
}

template<class T>
void remove_duplicates_wo_buffer(Node<T> * root)
{
  if (root == nullptr) {
    return;
  }

  auto runner = root;
  Node<T> * previous = nullptr;
  while (runner != nullptr) {
    auto inner_runner = root;
    while (inner_runner != runner) {
      if (runner->value == inner_runner->value) {  // duplicate detected
        auto node_to_be_deleted = runner;
        previous->next = runner->next;
        delete node_to_be_deleted;
        node_to_be_deleted = nullptr;
        break;
      }
      inner_runner = inner_runner->next;
    }
    previous = runner;
    runner = runner->next;
  }
}

int main()
{
  Node<size_t> * root = create_random_list(10);
  print_linked_list(root);
  remove_duplicates_wo_buffer(root);
  print_linked_list(root);
  return 0;
}
