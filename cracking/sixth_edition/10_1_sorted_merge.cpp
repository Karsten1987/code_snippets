#include <iostream>
#include <vector>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (auto & element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

template<class T>
void sorted_merge(
  std::vector<T> & vec_a,
  int lhs_a, int rhs_a,
  const std::vector<T> & vec_b,
  int lhs_b, int rhs_b)
{
  int distance_a = rhs_a - lhs_a + 1;
  if (distance_a < 0) {
    printf("rhs_a and lhs_a are wrong\n");
    return;
  }
  int distance_b = rhs_b - lhs_b + 1;
  if (distance_b < 0) {
    printf("rhs_b and lhs_b are wrong\n");
    return;
  }

  auto size_a = vec_a.size();
  if (size_a == 0) {
    printf("vec_a size is 0\n");
    return;
  }
  auto size_b = vec_b.size();
  if (size_a != distance_a + distance_b) {
    printf("vec_a doesn't have enough storage for both\n");
    printf("size_a %zu\n", size_a);
    printf("distnace_a %d, distance_b %d\n", distance_a, distance_b);
    return;
  }

  int index = vec_a.size() - 1;
  while (rhs_a >= lhs_a && rhs_b >= lhs_b) {
    if (vec_a[rhs_a] >= vec_b[rhs_b]) {
      vec_a[index] = vec_a[rhs_a];
      --rhs_a;
    } else {
      vec_a[index] = vec_b[rhs_b];
      --rhs_b;
    }
    --index;
  }

  while (rhs_b > lhs_b) {
    vec_a[index] = vec_b[rhs_b];
    --rhs_b;
  }
  printf("yuhuu\n");
}

int main()
{
  std::vector<size_t> vec_a = {1, 1, 3, 4, 56, 67, 123};
  std::vector<size_t> vec_b = {1, 2, 5, 7, 8, 9, 77, 245};

  auto size_real = vec_a.size();
  vec_a.resize(vec_a.size() + vec_b.size());
  print_vector(vec_a);
  print_vector(vec_b);
  sorted_merge(vec_a, 0, size_real - 1, vec_b, 0, vec_b.size() - 1);
  print_vector(vec_a);
}
