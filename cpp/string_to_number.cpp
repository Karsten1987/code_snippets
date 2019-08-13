#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <utility>

template<char C, class Enable = void>
struct CharacterToHex;

template<char C>
struct CharacterToHex<C, typename std::enable_if<C >= 48 && C <= 57>::type>
{
  static constexpr int value = C - 48;
};

template<char C>
struct CharacterToHex<C, typename std::enable_if<C >= 65 && C <= 70>::type>
{
  static constexpr int value = C - 65 + 10;
};

template<char C>
struct CharacterToHex<C, typename std::enable_if<C >= 97 && C <= 102>::type>
{
  static constexpr int value = C - 97 + 10;
};

template<size_t m, size_t n>
struct Pow
{
  static constexpr long value = m * Pow<m, n - 1>::value;
};

template<size_t m>
struct Pow<m, 1>
{
  static constexpr long value = m;
};

template<char C0, char ... STR>
struct StringToHex
{
  static constexpr int value = CharacterToHex<C0>::value;
};

struct Format
{
  using type = uint8_t;
  static constexpr type HEX = 16;
  static constexpr type BIN = 2;
};

template<char CN1, char CN2, char ... STR>
struct StringToHex<CN1, CN2, STR ...>
{
  static constexpr int value =  CharacterToHex<CN1>::value * Pow<16, sizeof...(STR) + 1>::value + StringToHex<CN2, STR...>::value;
};

template<Format::type F, typename std::enable_if<
  F == Format::BIN || F == Format::HEX>::type * = nullptr>
int parse(char c)
{
  if (c >= 48 && c <= 57) {
    return c - 48;
  }
  if (c >= 65 && c <= 90) {
    return c - 65 + 10;
  }
  if (c >= 97 && c <= 122) {
    return c - 97 + 10;
  }

  return -1;
}

template<Format::type F, typename std::enable_if<
  F == Format::BIN || F == Format::HEX>::type * = nullptr>
long convert(const std::string & s)
{
  long l = 0l;
  for (size_t i = 0; i < s.size(); ++i) {
    auto v = parse<F>(s[s.size() - 1 - i]);
    if (v < 0) {
      return v;
    }
    l += v * pow(F, i);
  }
  return l;
}

int main()
{
  auto tmp = StringToHex<'G', 'A', '4'>::value;
  std::cout << "template = " << tmp << std::endl;
  std::string s = "FA4";
  long v = convert<Format::HEX>(s);
  std::cout << "runtime = " << v << std::endl;
}
