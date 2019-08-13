#include <vector>

void remove_duplicates(std::vector<size_t> & v)
{
  size_t idx = 1u;
  size_t runner = 1u;

  while (runner < v.size()) {
    if (v[runner - 1] != v[runner]) {
      v[idx] = v[runner];
      ++idx;
    }
    ++runner;
  }
  v.resize(idx);
}

int main()
{
  std::vector<size_t> v = {1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 5, 6, 7, 8, 8};
  remove_duplicates(v);

  std::for_each(v.begin(), v.end(), [](size_t i) {printf("%zu\t", i);});
  printf("\n");
}
