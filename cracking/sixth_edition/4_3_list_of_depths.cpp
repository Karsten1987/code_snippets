#include "tree.hpp"

#include <vector>

template<class T>
struct LinkedListNode
{
  LinkedListNode * next;
  T value;

  LinkedListNode(T t):
    next(nullptr),
    value(std::move(t))
  {}
};

template<class T>
void list_of_depths(Node<T>* root, size_t depth, std::vector<LinkedListNode<T> *> & vec)
{
  if (root == nullptr) {
    return;
  }

  printf("value %zu is on level %zu\n", root->value, depth);
  // we begin a new depth
  if (vec.size() < depth) {
    auto new_node = new LinkedListNode<T>(root->value);
    vec.push_back(new_node);
  } else {
    auto new_node = new LinkedListNode<T>(root->value);
    auto bucket_root = vec[depth - 1];
    while (bucket_root->next != nullptr) {
      bucket_root = bucket_root->next;
    }
    bucket_root->next = new_node;
  }

  depth += 1;
  list_of_depths(root->left, depth, vec);
  list_of_depths(root->right, depth, vec);
}

template<class T>
void print_list_of_depths(const std::vector<LinkedListNode<T> *> & vec)
{
  for (auto i = 0; i < vec.size(); ++i) {
    auto iterator = vec[i];
    while (iterator != nullptr) {
      printf("[%zu] ", iterator->value);
      iterator = iterator->next;
    }
    printf("\n");
  }
}

int main()
{
  //std::vector<size_t> vec = {3, 2, 5, 1, 4, 6};
  std::vector<size_t> vec = {1, 2, 3, 4, 5, 6};
  auto root = create_binary_search_tree(vec);
  print_tree(root);
  std::vector<LinkedListNode<size_t> *> vec_ll;
  list_of_depths(root, 1u, vec_ll);
  print_list_of_depths(vec_ll);
  printf("max depth of tree %zu\n", get_max_depth(root));
  return 0;
}
