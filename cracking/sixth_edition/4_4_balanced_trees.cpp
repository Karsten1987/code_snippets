#include "tree.hpp"
#include <cmath>

template<class T>
int get_depth(Node<T> * root, bool & escape)
{
  if (root == nullptr) {
    return 0;
  }

  auto depth_left = get_depth(root->left, escape);
  if (escape) {
    return 0;
  }

  auto depth_right = get_depth(root->right, escape);
  if (escape) {
    return 0;
  }


  if (std::abs(depth_left - depth_right) > 1) {
    printf("quick escape at %zu\n", root->value);
    escape = true;
    return depth_left;
  }

  return (depth_left > depth_right) ? depth_left + 1 : depth_right + 1;
}

template<class T>
bool is_balanced(Node<T> * root)
{
  if (root == nullptr) {
    return false;
  }

  bool escape = false;
  auto depth_left = get_depth(root->left, escape);
  if (escape) {
    return false;
  }
  auto depth_right = get_depth(root->right, escape);
  if (escape) {
    return false;
  }

  if (std::abs(depth_left - depth_right) > 1) {
    return false;
  }

  return true;
}

int main()
{
  //std::vector<size_t> vec = {3, 2, 5, 1, 4, 6};
  std::vector<size_t> vec = {1, 2, 3, 4, 5, 6};
  auto root = create_binary_search_tree(vec);
  print_tree(root);
  bool balanced = is_balanced(root);
  printf("tree is %s\n", balanced ? "balanced" : "not balanced");
  return 0;
}
