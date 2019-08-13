#include <unordered_map>
#include <string>
#include <vector>

template<class T = size_t>
struct Node
{
  Node * next;
  T value;
};

template<class T>
Node<T> vector_to_linked_list(std::vector<T> vec)
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
void remove_duplicates_with_buffer(Node<T> & node) {
  const auto root = &node;

  std::unordered_map<T, size_t> duplicate_count;
  duplicate_count[root->value] = 1;

  auto parent_node = &node;
  auto current_node = node.next;
  while (current_node != nullptr) {
    if (duplicate_count.count(current_node->value) == 1) {
      // skip version
      parent_node->next = current_node->next;
    } else {
      duplicate_count[current_node->value] = 1;
      parent_node = current_node;
    }
    current_node = current_node->next;
  }
}

template<class T>
void remove_duplicates(Node<T> & node) {
  const auto root = &node;

  auto parent_node = &node;
  auto current_node = node.next;
  while(current_node != nullptr) {
    // check from root to current node if duplicated
    auto tmp_node = root;
    bool duplicate_found = false;
    while(tmp_node != current_node) {
      if (current_node->value == tmp_node->value) {
        // skip current node
        parent_node->next = current_node->next;
        duplicate_found = true;
        break;
      }
      tmp_node = tmp_node->next;
    }
    // if no duplicates were found
    if (!duplicate_found) {
      parent_node = current_node;
    }
    current_node = current_node->next;
  }
}

int main()
{
  std::vector<size_t> vec = {1, 2, 3, 1, 5, 4, 5, 1};
  auto root = vector_to_linked_list(vec);

  auto tmp = &root;
  while (tmp != nullptr) {
    printf("[%zu] --> ", tmp->value);
    tmp = tmp->next;
  }
  printf("\n");

  //remove_duplicates(root);
  remove_duplicates_with_buffer(root);

  tmp = &root;
  while (tmp != nullptr) {
    printf("[%zu] --> ", tmp->value);
    tmp = tmp->next;
  }
  printf("\n");
  return 0;
}
