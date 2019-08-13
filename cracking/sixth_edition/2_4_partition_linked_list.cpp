#include "linked_list.hpp"

template<class T>
void partition_list(Node<T> * root, T pivot_point)
{
  Node<T> * left = nullptr;
  Node<T> * right = nullptr;

  Node<T> * right_root = nullptr;
  Node<T> * left_root = nullptr;

  auto iterator = root;
  while (iterator != nullptr) {
    if (iterator->value > pivot_point) {
      if (right == nullptr) {
        right = new Node<T>(iterator->value);
        right_root = right;
      } else {
        right->next = new Node<T>(iterator->value);
        right = right->next;
      }
    } else {
      if (left == nullptr) {
        left = new Node<T>(iterator->value);
        left_root = left;
      } else {
        left->next = new Node<T>(iterator->value);
        left = left->next;
      }
    }
    iterator = iterator->next;
  }

  left->next = right_root;
  *root = *left_root;
}

int main()
{
  auto root = create_random_list(10);
  print_linked_list(root);
  partition_list(root, 50lu);
  print_linked_list(root);
  return 0;
}
