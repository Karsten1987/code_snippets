#include <iostream>
#include <vector>
#include <unordered_map>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (auto & element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

class Anagram
{
public:
  Anagram(const std::string & s)
    :s_(s)
  {
    for (char c : s) {
      map_[c]++;
    }
  }

  bool operator==(Anagram & other)
  {
    for (char c : other.s_) {
      if (this->map_[c] != other.map_[c]) {
        // printf("%s and %s are not anagrams\n", this->s_.c_str(), other.s_.c_str());
        return false;
      }
    }
    printf("%s and %s are anagrams\n", this->s_.c_str(), other.s_.c_str());
    return true;
  }

private:
  std::string s_;
  std::unordered_map<char, size_t> map_;
};

struct anagram_predicate
{
  bool operator()(const std::string & t1, const std::string & t2) {
    //Anagram a1(t1);
    //Anagram a2(t2);
    auto tt1 = t1;
    auto tt2 = t2;
    std::sort(tt1.begin(), tt1.end());
    std::sort(tt2.begin(), tt2.end());
    return tt1 < tt2;
  }
};

template<class T, class Predicate>
void merge(std::vector<T> & vec, std::vector<T> & helper, size_t lhs, size_t middle, size_t rhs, Predicate p)
{
  for (auto i = lhs; i <= rhs; ++i) {
    helper[i] = vec[i];
  }

  auto start_left = lhs;
  auto start_right = middle + 1;
  auto index = start_left;
  while (start_left <= middle && start_right <= rhs)
  {
    if (p(helper[start_left], helper[start_right])) {
      vec[index] = helper[start_left];
      ++start_left;
    } else {
      vec[index] = helper[start_right];
      ++start_right;
    }
    ++index;
  }

  while (start_left <= middle) {
    vec[index] = helper[start_left];
    ++start_left;
    ++index;
  }

  while (start_right <= rhs) {
    vec[index] = helper[start_right];
    ++start_right;
    ++index;
  }
}

template<class T, class Predicate>
void merge_sort(std::vector<T> & vec, std::vector<T> & helper, size_t lhs, size_t rhs, Predicate p)
{
  if (lhs >= rhs) {
    return;
  }

  auto middle = lhs + ((rhs - lhs) / 2);
  merge_sort(vec, helper, lhs, middle, p);
  merge_sort(vec, helper, middle + 1, rhs, p);
  merge(vec, helper, lhs, middle, rhs, p);
}

template<class T, class Predicate = std::less<T>>
void merge_sort(std::vector<T> & vec, size_t lhs, size_t rhs)
{
  std::vector<T> helper = vec;

  merge_sort(vec, helper, lhs, rhs, Predicate());
}

template<>
void merge_sort<std::string, class Predicate>(std::vector<std::string> & vec, size_t lhs, size_t rhs)
{
  std::vector<std::string> helper = vec;

  merge_sort(vec, helper, lhs, rhs, anagram_predicate());
}

template<class T>
void group_anagrams(std::vector<T> & vec)
{
  merge_sort<std::string, anagram_predicate>(vec, 0, vec.size() -1);
}

int main()
{
  std::vector<std::string> vec = {
    "abc",
    "123",
    "Hello World",
    "cba",
    "def",
    "bac",
    "iceman",
    "cinema"
  };

  //std::vector<size_t> vec = {3, 4, 5, 1, 2, 78, 123};
  group_anagrams(vec);
  print_vector(vec);
}
