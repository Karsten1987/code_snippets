#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_

#include <iostream>
#include <random>
#include <vector>

template<class T = size_t>
struct Node
{
  Node * next;
  T value;

   Node():
    next(nullptr),
    value(T(0))
  {};

  Node(T t):
    next(nullptr),
    value(std::move(t))
  {};
};

template<class T = size_t>
Node<T> * create_list(const std::vector<T> & vec)
{
  if (vec.size() == 0) {
    return nullptr;
  }

  Node<T> * root = new Node<T>(vec[0]);
  auto runner = root;
  for (size_t i = 1u; i < vec.size(); ++i) {
    runner->next = new Node<T>(vec[i]);
    runner = runner->next;
  }

  return root;
}

template<class T = size_t>
Node<T> * create_random_list(size_t size)
{
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

  auto root = new Node<T>(dist(rng));
  auto runner = root;

  for (size_t i = 1; i < size; ++i) {
    auto tmp = new Node<T>(dist(rng));
    runner->next = tmp;
    runner = tmp;
  }

  return root;
}

template<class T = size_t>
void print_linked_list(const Node<T> * root)
{
  auto iterator = root;
  while (iterator != nullptr) {
    std::cout << "[" << iterator->value << "] --> ";
    iterator = iterator->next;
  }
  std::cout << "[nullptr]" << std::endl;
}

#endif  // LINKED_LIST_HPP_
