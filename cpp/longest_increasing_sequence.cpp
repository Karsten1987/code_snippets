#include <iostream>
#include <vector>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  size_t i = 0;
  for (; i < vec.size() - 1; ++i) {
    std::cout << "[" << vec[i] << "] ";
  }
  std::cout << "[" << vec[i] << "]" << std::endl;
}

int longest_sequence(
  const std::vector<size_t> & vec, size_t size, size_t & max_element_index)
{
  if (size == 1) {
    max_element_index = 0;
    return 1;
  }

  int max = 0;
  for (auto i = 1lu; i < size; ++i) {
    int prior_max = longest_sequence(vec, i, max_element_index);
    if (vec[i - 1] < vec[size - 1]) {
      if (max < prior_max + 1) {
        max = prior_max + 1;
        max_element_index = i;
      }
    }
  }

  return max;
}

int longest_sequence(const std::vector<size_t> & vec)
{
  std::vector<size_t> ls(vec.size(), 1);

  for (auto i = 0lu; i < vec.size(); ++i) {
    for (auto j = 0lu; j < i; ++j) {
      if (vec[i] > vec[j]) {
        if (ls[j] + 1 >= ls[i]) {
          ls[i] = ls[j] + 1;
        }
      }
    }
  }

  print_vector(ls);

  return *std::max_element(ls.begin(), ls.end());
}

int main()
{
  std::vector<size_t> seq = {10, 22, 9, 33, 23, 24, 25, 34, 35, 46};
  //std::vector<size_t> seq = {10};
  //auto max = longest_sequence(seq);
  auto max_element = 0lu;
  auto max = longest_sequence(seq, seq.size(), max_element);
  std::cout << "max sequence length" << max << std::endl;
  return 0;
}
