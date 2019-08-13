#include <algorithm>
#include <string>

void remove_duplicates(std::string & string)
{
  size_t len = string.size();
  if (len < 2) {
    return;
  };

  size_t string_index = 1;
  for (size_t i = 1; i < len; ++i) {
    // check if current character was already placed in the string
    bool duplicate_found = false;
    for (size_t j = 0; j < i; ++j) {
      if (string[i] == string[j]) {
        // skip the duplicates
        duplicate_found = true;
        break;
      }
    }
    if (!duplicate_found) {
      string[string_index] = string[i];
      ++string_index;
    }
  }
}

void remove_duplicates_sorted(std::string & string)
{
  std::sort(string.begin(), string.end());

  size_t head = 0u;
  size_t tail = 1u;

  while (tail < string.size()) {
    if (string[head] != string[tail]) {
      string[++head] = string[tail];
    }

    ++tail;
  }
}

int main()
{
  std::string with_duplicates = "aababcacddaeefafa";
  remove_duplicates_sorted(with_duplicates);
  printf("without duplicates %s\n", with_duplicates.c_str());
  return 0;
}
