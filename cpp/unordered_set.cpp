#include <unordered_set>

int main()
{
  std::unordered_set<size_t> set;
  set.insert(13);
  set.insert(14);
  set.insert(13);

  printf("%zu\n", set.count(13));
}
