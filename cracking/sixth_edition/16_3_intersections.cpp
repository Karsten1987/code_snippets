#include <iostream>


int main()
{
  std::pair<int, int> a1 = {0, 0};
  std::pair<int, int> a2 = {10, 10};

  std::pair<int, int> b1 = {5, 0};
  std::pair<int, int> b2 = {6, 2};

  auto da = double(a1.second - a2.second) / double(a1.first - a2.first);
  auto db = double(b1.second - b2.second) / double(b1.first - b2.first);

  if (da == db) {
    printf("no intersection possible with parallel lines\n");
    return -1;
  }

  // dx + b = 0
  // da * a1.first + b = a1.second
  // da * a1.first - a1.second = -b
  // -1 * da * a1.first + a1.second = b
  auto ba = -1 * da * a1.first + a1.second;
  auto bb = -1 * db * b1.first + b1.second;

  // da * x + ba      = db * x + bb
  // da * x           = db * x + bb - ba
  // da * x - db * x  = bb - ba
  // x * (da - db)    = bb - ba
  // x                = (bb -ba) / (da - db)

  auto x = (bb - ba) / (da - db);
  auto y = da * x + ba;

  auto min_x = a1.first > b1.first ? a1.first : b1.first;
  auto max_x = a2.first < b2.first ? a2.first : b2.first;

  if (x >= min_x && x <= max_x) {
    printf("two lines crossing at x:%f and y:%f\n", x, y);
  } else {
    printf("two lines crossing out of range x:%f and y:%f\n", x, y);
  }

  return 0;
}
