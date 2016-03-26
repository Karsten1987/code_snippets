#include <iostream>
#include <memory>

template<class T>
struct Node
{
  Node* next;
  T data;
};

template<class T>
class LinkedListFactory
{
  LinkedListFactory() = delete;

public:
  static Node<T>* createList( std::initializer_list<T> values )
  {
    Node<T>* root = new Node<T>();
    Node<T>* init_root = nullptr;
    for (auto& val : values)
    {
      if (!init_root)
      {
        root->next = nullptr;
        root->data = val;
        init_root = root;
        continue;
      }

      Node<T>* head = new Node<T>();
      head->next = nullptr;
      head->data = val;
      root->next = head;
      root = head;
    }
    return init_root;
  }

  static void printList( const Node<T>* root )
  {
    std::cout << "[ ";
    while ( root->next != nullptr )
    {
      std::cout << root->data << " ";
      root = root->next;
    }
    std::cout << root->data << " ]";
  }
};

int main()
{
  Node<int>* root = LinkedListFactory<int>::createList( {5,4,3,2,1,} );
  LinkedListFactory<int>::printList(root);
  return 0;
}
