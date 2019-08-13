#include <algorithm>
#include <vector>
#include <unordered_set>

std::vector<size_t> longest_sequence_with_set(const std::vector<size_t> & v)
{
  std::unordered_set<size_t> set;
  for (auto i : v) {
    set.insert(i);
  }

  std::vector<std::vector<size_t>> all_sequences;
  std::vector<size_t> sequence;

  for (auto i : v) {
    auto left = i - 1;
    auto right = i + 1;
    sequence.push_back(i);

    auto iter = set.begin();
    while ((iter = set.find(left)) != set.end()) {
      sequence.push_back(*iter);
      set.erase(iter);
      --left;
    }
    while ((iter = set.find(right)) != set.end()) {
      sequence.push_back(*iter);
      set.erase(iter);
      ++right;
    }
    all_sequences.push_back(sequence);
    sequence.clear();
  }

  size_t max_index = 0u;
  size_t max_count = 0u;
  for (auto i = 0u; i < all_sequences.size(); ++i) {
    std::for_each(all_sequences[i].begin(), all_sequences[i].end(), [](size_t i) {
        printf("[%zu] ", i);});
    printf("\n");
    if (all_sequences[i].size() > max_count) {
      max_count = all_sequences[i].size();
      max_index = i;
    }
  }
  printf("\n****\n");
  return all_sequences[max_index];
}

std::vector<size_t> longest_sequence(std::vector<size_t> & v)
{
  std::vector<std::vector<size_t>> all_sequences;
  std::vector<size_t> longest_seq;
  std::sort(v.begin(), v.end());
  std::for_each(v.begin(), v.end(), [](size_t i) {
      printf("[%zu] ", i); });
  printf("\n");

  size_t idx = 0u;
  while (idx < v.size()) {
    longest_seq.push_back(v[idx]);
    if (idx >= v.size() || v[idx] + 1 != v[idx + 1])
    {
      all_sequences.push_back(longest_seq);
      longest_seq.clear();
    }
    ++idx;
  }

  size_t max_index = 0u;
  size_t max_count = 0u;
  for (auto i = 0u; i < all_sequences.size(); ++i) {
    std::for_each(all_sequences[i].begin(), all_sequences[i].end(), [](size_t i) {
        printf("[%zu] ", i);});
    printf("\n");
    if (all_sequences[i].size() > max_count) {
      max_count = all_sequences[i].size();
      max_index = i;
    }
  }
  printf("\n****\n");
  return all_sequences[max_index];
}

int main()
{
  std::vector<size_t> v = {5, 4, 3, 1, 6, 8, 9, 7, 11, 12};  // 3456789
  //auto longest_seq = longest_sequence(v);
  auto longest_seq = longest_sequence_with_set(v);
  std::for_each(longest_seq.begin(), longest_seq.end(), [](size_t i) {
      printf("[%zu] ", i); });
  printf("\n");
}
