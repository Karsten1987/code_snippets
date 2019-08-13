#include <iostream>
#include <vector>
#include <assert.h>

template<class MessageT>
class Publisher
{
public:
  void publish(MessageT msg)
  {
    std::cout << "Publish Message: " << msg << std::endl;
  }
};

template<class MessageT>
class LifecyclePublisher : public Publisher<MessageT>
{
public:
  void publish(MessageT msg)
  {
    if (!enabled_)
    {
      std::cout << "Publishing not allowed" << std::endl;
      return;
    }
    std::cout << "Publishing Message: " << msg << std::endl;
  }

  bool enabled_ = true;
};

// Node.hpp
class Node
{
  public:
  template<class MessageT, template <class MessageT> class PublisherT = Publisher>
  PublisherT<MessageT>
  create_publisher();

  size_t get_number_of_publisher() const;

private:
  size_t number_of_pubs_ = 0;
};

// NodeImpl.hpp
template<class MessageT, template <class MessageT> class PublisherT>
PublisherT<MessageT>
Node::create_publisher()
{
  PublisherT<MessageT> pub;
  ++number_of_pubs_;
  return pub;
}

// Node.cpp
size_t Node::get_number_of_publisher() const
{
  return number_of_pubs_;
}


// Lifecycle.hpp
class LifecycleNode : public Node
{
public:
  template<class MessageT>
  LifecyclePublisher<MessageT>
  create_publisher()
  {
    return Node::create_publisher<MessageT, LifecyclePublisher>();
  }
};

template<class T>
class MyNode
{
  typedef T T;
};

int main()
{
  Node n;
  Publisher<std::string> pub = n.create_publisher<std::string>();
  assert(n.get_number_of_publisher()==1);

  LifecycleNode lcn;
  LifecyclePublisher<std::string> lcn_pub = lcn.create_publisher<std::string>();
  assert(lcn.get_number_of_publisher()==1);

  MyNode<int> mn;
  decltype<mn::T> mn2;
  return 0;

}
