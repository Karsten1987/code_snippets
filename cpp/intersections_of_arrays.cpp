#include <vector>

std::vector<size_t> find_intersections(
  const std::vector<size_t> & v1,
  const std::vector<size_t> & v2,
  const std::vector<size_t> & v3)
{
  // find the smallest element at all fronts and shift its index
  // if equal push back
  std::vector<size_t> intersections;

  auto i1 = 0u;
  auto i2 = 0u;
  auto i3 = 0u;

  while (i1 < v1.size() && i2 < v2.size() && i3 < v3.size()) {
    size_t e1 = v1[i1];
    size_t e2 = v2[i2];
    size_t e3 = v3[i3];
    if (e1 == e2 && e2 == e3) {
      intersections.push_back(e1);
      i1++;
      i2++;
      i3++;
      continue;
    }

    // if not equal, find smallest element to increment
    if (e1 > e2 && e2 > e3) {
      i3++;
    } else if (e1 > e2 && e2 < e3) {
      i2++;
    } else {
      i1++;
    }
  }

  return intersections;
}

int main()
{
  std::vector<size_t> v1 = {3, 5, 6, 6, 8, 10, 12};
  std::vector<size_t> v2 = {1, 2, 3, 4, 5, 6};
  std::vector<size_t> v3 = {3, 5, 6, 10, 15};

  auto intersections = find_intersections(v1, v2, v3);
  std::for_each(intersections.begin(), intersections.end(), [](size_t i) {
      printf("found intersection %zu\n", i);
      });
}
