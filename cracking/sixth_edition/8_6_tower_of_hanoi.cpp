#include <iostream>
#include <stack>
#include <vector>

template<class T>
void print_towers(std::stack<T> tower1, std::stack<T> tower2, std::stack<T> tower3)
{
  auto max_size = tower1.size();
  if (tower2.size() > max_size) {
    max_size = tower2.size();
  }
  if (tower3.size() > max_size) {
    max_size = tower3.size();
  }

  for (auto i = 0; i < max_size; ++i) {
    if (tower1.size() >= max_size - i) {
      auto top = tower1.top();
      tower1.pop();
      std::cout << "[" << top << "]\t";
    } else {
      std::cout << "   \t";
    }

    if (tower2.size() >= max_size - i) {
      auto top = tower2.top();
      tower2.pop();
      std::cout << "[" << top << "]\t";
    } else {
      std::cout << "   \t";
    }

    if (tower3.size() >= max_size - i) {
      auto top = tower3.top();
      tower3.pop();
      std::cout << "[" << top << "]" << std::endl;
    } else {
      std::cout << "   " << std::endl;
    }
  }
  std::cout << "---\t---\t---" << std::endl;
}

template<class T>
void move_disk(int top_size, std::stack<T> & origin, std::stack<T> & destination, std::stack<T> & buffer)
{
  if (top_size <= 0) {
    return;
  }

  move_disk(top_size - 1, origin, buffer, destination);

  auto top = origin.top();
  origin.pop();
  destination.push(top);

  move_disk(top_size - 1, buffer, destination, origin);
}

int main()
{
  std::stack<size_t> tower1;
  std::stack<size_t> tower2;
  std::stack<size_t> tower3;

  tower1.push(4);
  tower1.push(3);
  tower1.push(2);
  tower1.push(1);

  print_towers(tower1, tower2, tower3);

  move_disk(4, tower1, tower3, tower2);

  print_towers(tower1, tower2, tower3);
}
