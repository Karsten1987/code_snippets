#include <iostream>
#include <vector>

std::vector<size_t> find_intersection_sorted(
    const std::vector<size_t> & v1,
    const std::vector<size_t> & v2,
    const std::vector<size_t> & v3)
{
  std::vector<size_t> intersections;

  size_t v1_index = 0lu;
  size_t v2_index = 0lu;
  size_t v3_index = 0lu;

  bool array_end = false;
  while (!array_end) {
    if (v1_index >= v1.size() || v2_index >= v2.size() || v3_index >= v3.size()) {
      array_end = true;
      break;
    }
    if (v1[v1_index] == v2[v2_index] && v2[v2_index] == v3[v3_index]) {
      intersections.push_back(v1[v1_index]);
      ++v1_index;
      ++v2_index;
      ++v3_index;
      continue;
    }

    // find smallest element
    // increase index
    // check for intersection
    // if index == end for any v return false
    if (v1[v1_index] <= v2[v2_index] && v1[v1_index] <= v3[v3_index]) {
      ++v1_index;
    } else if (v2[v2_index] <= v1[v1_index] && v2[v2_index] <= v3[v3_index]) {
      ++v2_index;
    } else {
      ++v3_index;
    }
  }

  return intersections;
}

std::vector<size_t> find_intersection_unsorted(
  const std::vector<size_t> & v1,
  const std::vector<size_t> & v2,
  const std::vector<size_t> & v3)
{
  std::vector<size_t> intersections;

  unsigned long long v1_bitset = 0llu;
  unsigned long long v2_bitset = 0llu;

  for (const auto & v : v1) {
    v1_bitset |= (1llu << v);
  }
  for (const auto & v : v2) {
    v2_bitset |= (1llu << v);
  }
  for (const auto & v : v3) {
    auto comp = 1llu << v;
    if (!(v1_bitset & comp)) {
      continue;
    }
    if (!(v2_bitset & comp)) {
      continue;
    }
    intersections.push_back(v);
  }

  return intersections;
}

int main()
{
  std::vector<size_t> vec1 = {1, 3, 5, 7, 9, 10};
  std::vector<size_t> vec2 = {3, 6, 7, 10};
  std::vector<size_t> vec3 = {3, 8, 10, 12};

  std::vector<size_t> intersections = find_intersection_unsorted(
      vec1, vec2, vec3);

  for (const auto & el : intersections) {
    std::cout << el << std::endl;
  }
  return 0;
}
