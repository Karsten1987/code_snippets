#include <iostream>
#include <vector>

enum class Color : size_t
{
  RED = 0,
  YELLOW = 1,
  BLUE = 2,
  GREEN = 3
};

std::pair<size_t, size_t> count_points(const std::vector<Color> & solution, const std::vector<Color> & guess)
{
  size_t hits = 0;
  size_t pseudo_hits = 0;

  std::vector<size_t> markings = {0, 0, 0, 0};
  for (size_t i = 0; i < guess.size(); ++i) {
    if (guess[i] == solution[i]) {
      ++hits;
    } else {
      ++markings[static_cast<size_t>(solution[i])];
    }
  }
  for (size_t i = 0; i < guess.size(); ++i) {
    size_t color_code = static_cast<size_t>(guess[i]);
    if (markings[color_code] != 0 && guess[i] != solution[i]) {
      ++pseudo_hits;
      --markings[color_code];
    }
  }

  return {hits, pseudo_hits};
}

int main()
{
  std::vector<Color> solution = {Color::RED, Color::GREEN, Color::BLUE, Color::YELLOW};

  std::vector<Color> guess = {Color::GREEN, Color::GREEN, Color::RED, Color::RED};

  auto points = count_points(solution, guess);
  std::cout << "hits: " << points.first << " pseudo: " << points.second << std::endl;
}
