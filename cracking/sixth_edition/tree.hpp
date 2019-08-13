#ifndef TREE_HPP_
#define TREE_HPP_

#include <cmath>
#include <vector>
#include <queue>

template<class T>
struct Node
{
  Node<T> * left;
  Node<T> * right;
  T value;

  Node():
    left(nullptr),
    right(nullptr),
    value(T(0))
  {}

  Node(T t):
    left(nullptr),
    right(nullptr),
    value(std::move(t))
  {}
};

template<class T>
void insert(Node<T> * root, T value)
{
  if (root == nullptr) {
    return;
  }

  // insert left
  if (value <= root->value) {
    if (root->left == nullptr) {
      root->left = new Node<T>(value);
      return;
    } else {
      insert(root->left, value);
      return;
    }
  }
  if (value > root->value) {
    if (root->right == nullptr) {
      root->right = new Node<T>(value);
      return;
    } else {
      insert(root->right, value);
      return;
    }
  }
}

template<class T>
Node<T> * create_binary_search_tree(const std::vector<T> & vec)
{
  if (vec.size() == 0) {
    return nullptr;
  }

  Node<T> * root = new Node<T>(vec[0]);
  for (size_t i = 1; i < vec.size(); ++i) {
    insert(root, vec[i]);
  }
  return root;
}

template<class T>
size_t get_max_depth(Node<T> * root)
{
  if (root == nullptr) {
    return 0;
  }

  auto depth_left = get_max_depth(root->left);
  auto depth_right = get_max_depth(root->right);
  if (depth_left > depth_right) {
    return depth_left + 1;
  }
  return depth_right + 1;
}

template<class T>
void print_tree(Node<T> * root)
{
  size_t max_level = get_max_depth(root);
  if (root == nullptr) {
    printf("[nullptr]\n");
    return;
  }

  std::queue<Node<T> *> queue;
  queue.push(root);

  size_t counter = 0u;
  size_t level = 0u;
  while (!queue.empty()) {
    ++counter;
    auto top = queue.front();
    queue.pop();
    if (top != nullptr) {
      queue.push(top->left);
      queue.push(top->right);
      printf("[%zu]", top->value);
    } else {
      queue.push(nullptr);
      queue.push(nullptr);
      printf(" ");
    }
    if (pow(2, level) == counter) {
      ++level;
      counter = 0;
      printf("\n");
    } else {
      printf(" ");
    }
    if (level == max_level) {
      break;
    }
  }
  printf("\n");
}

#endif  // TREE_HPP_
