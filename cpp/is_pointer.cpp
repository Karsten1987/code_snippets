#include <iostream>
#include <memory>

using namespace std;

namespace node_traits
{

template<class NodeT>
struct is_smart_pointer_helper : std::false_type
{};

template<class NodeT>
struct is_smart_pointer_helper<std::shared_ptr<NodeT>> : std::true_type
{};

template<class NodeT>
struct is_smart_pointer_helper<std::unique_ptr<NodeT>> : std::true_type
{};

template<class NodeT>
struct is_smart_pointer : is_smart_pointer_helper<typename std::remove_cv<NodeT>::type>
{};

template<class NodeT>
struct is_node_pointer
{
  static constexpr bool value = is_smart_pointer<NodeT>::value == true || std::is_pointer<NodeT>::value == true;
  using type = typename std::integral_constant<NodeT, is_smart_pointer<NodeT>::value == true || std::is_pointer<NodeT>::value == true>::value_type;
};
}

int main() {
  auto ptr = new int(13);
  auto sptr = std::make_shared<int>(13);
  const auto csptr = std::make_shared<int>(13);
  const volatile auto cvsptr = std::make_shared<int>(13);
  const int * const i = new int (13);
  const volatile auto cvsptrc = std::shared_ptr<int const>(i);
  auto uptr = std::make_unique<int>(13);
  const auto cuptr = std::make_unique<int>(13);
  const volatile auto cvuptr = std::make_unique<int>(13);
  const volatile auto cvuptrc = std::make_unique<const int>(13);

  //node_traits::is_node_pointer<int>::type d = 13;
  cout << boolalpha << node_traits::is_node_pointer<decltype(ptr)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(sptr)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(csptr)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(cvsptr)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(cvsptrc)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(uptr)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(cuptr)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(cvuptr)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(cvuptrc)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<decltype(cvuptrc)>::value << endl;
  cout << boolalpha << node_traits::is_node_pointer<int>::value << endl;
  return 0;
}
