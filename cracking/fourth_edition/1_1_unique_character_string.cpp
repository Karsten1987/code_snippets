#include <string>

#define MAP 0
#define HASH 1
#define VECTOR 2

#define METHOD VECTOR

#if METHOD == MAP
#include <unordered_map>
#elif METHOD == VECTOR
#include <vector>
#endif

bool test_for_uniqueness(const std::string & str)
{
#if METHOD == HASH
  unsigned long long low_hash = 0llu;
  unsigned long long high_hash = 0llu;

  constexpr size_t ascii_offset = 63;

  for (const auto & c : str) {
    size_t ascii_index = static_cast<size_t>(c);
    if (ascii_index > ascii_offset) {
      auto index = 1ull << (ascii_index - ascii_offset);
      if (high_hash & index) {
        return false;
      }
      high_hash |= index;
    } else {
      auto index = 1ull << ascii_index;
      if (low_hash & index) {
        return false;
      }
      low_hash |= 1ull << index;
    }
  }
  return true;

#elif METHOD == MAP
  std::unordered_map<char, size_t> map;
  for (const auto & c : str) {
    if (map.count(c) > 0) {
      return false;
    }
    map[c] = 1;
  }
  return true;

#elif METHOD == VECTOR
  std::vector<bool> vector(128, 0);
  for (const auto & c : str) {
    if (vector[c]) {
      return false;
    }
    vector[c] = true;
  }
  return true;
#endif
}

int main() {
  std::string unique_str = "abcd1234ABCD!@#$";
  std::string copied_str = "abcd12344321dcbaABCD!@#$%^&*()_+";

  bool is_unique = test_for_uniqueness(unique_str);
  printf("%s is %s\n", unique_str.c_str(), (is_unique ? "unique" : "not unique"));
  is_unique = test_for_uniqueness(copied_str);
  printf("%s is %s\n", copied_str.c_str(), (is_unique ? "unique" : "not unique"));

  return 0;
}
