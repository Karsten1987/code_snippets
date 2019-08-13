#include <algorithm>
#include <vector>

void print_range(const std::vector<size_t> & v)
{
  if (v.size() < 1) {
    return;
  }
  if (v.size() == 1) {
    printf("%zu\n", v[0]);
    return;
  }

  bool is_open_range = false;
  for (auto i = 0u; i < v.size() - 1; ++i) {
    // are consecutive?
    if (v[i] + 1 == v[i + 1]) {
      if (!is_open_range) {
        printf("%zu", v[i]);
        is_open_range = true;
      } // continue if already open
    } else {
      // not consecutive
      if (is_open_range) {
        printf("-%zu, ", v[i]);
        is_open_range = false;
      } else {
        printf("%zu, ", v[i]);
      }
    }
  }
  if (is_open_range) {
    printf("-%zu\n", v[v.size() - 1]);
  } else {
    printf("%zu\n", v[v.size() - 1]);
  }
}

int main()
{
  std::vector<size_t> v = {1, 3, 5, 6, 7, 8, 10, 11, 14, 15, 16, 98, 99};  // 3456789
  print_range(v);
}
