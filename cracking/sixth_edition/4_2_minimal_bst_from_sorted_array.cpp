#include "tree.hpp"

template<class T>
void insert_minimal(const std::vector<T> & vec,
  Node<T> * root, size_t lhs, size_t rhs)
{
  if (root == nullptr) {
    return;
  }

  auto middle_index = lhs + ((rhs - lhs) / 2);
  root->value = vec[middle_index];
  if (middle_index >= lhs + 1) {
    root->left = new Node<T>();
    insert_minimal(vec, root->left, lhs, middle_index - 1);
  }
  if (middle_index <= rhs - 1) {
    root->right = new Node<T>();
    insert_minimal(vec, root->right, middle_index + 1, rhs);
  }
}

template<class T>
Node<T> * create_minimal_bst(const std::vector<T> & vec)
{
  if (vec.size() == 0) {
    return nullptr;
  }

  Node<T> * root = new Node<T>();
  insert_minimal(vec, root, 0, vec.size() - 1);

  return root;
}

int main()
{
  std::vector<size_t> vec = {1, 2, 3, 4, 5, 6};
  //std::vector<size_t> vec = {1, 2, 3};
  //std::vector<size_t> vec = {3, 2, 5, 1, 4, 6};
  //auto root = create_binary_search_tree(vec);
  auto root = create_minimal_bst(vec);
  print_tree(root);
  return 0;
}
