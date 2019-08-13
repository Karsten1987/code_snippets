#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
  std::unordered_map<char, std::string> single_map;
  single_map['0'] = "";
  single_map['1'] = "one";
  single_map['2'] = "two";
  single_map['3'] = "three";
  single_map['4'] = "four";
  single_map['5'] = "five";
  single_map['6'] = "six";
  single_map['7'] = "seven";
  single_map['8'] = "eight";
  single_map['9'] = "nine";

  std::unordered_map<char, std::string> tens_map;
  tens_map['0'] = "";
  tens_map['1'] = "ten";
  tens_map['2'] = "twenty";
  tens_map['3'] = "thirty";
  tens_map['4'] = "fourty";
  tens_map['5'] = "fifty";
  tens_map['6'] = "sixty";
  tens_map['7'] = "seventy";
  tens_map['8'] = "eighty";
  tens_map['9'] = "ninty";

  std::unordered_map<size_t, std::string> prefix_map;
  prefix_map[0] = "";
  prefix_map[3] = "thousand, ";
  prefix_map[6] = "million, ";

  // 1 234 567 890
  //int a = -1234567890;
  int a = -1101234;

  if (a == 0) {
    std::cout << "null" << std::endl;
  }

  std::string input_string = std::to_string(std::abs(a));
  std::string output_string = "";

  std::string prefix = "";
  size_t counter = 0u;
  for (int i = input_string.size() - 1; i >= 0; --i, ++counter) {
    if (counter % 3 == 0) {
      prefix = prefix_map[input_string.size() - i - 1];
      output_string = single_map[input_string[i]] + prefix + output_string;
    }
    if (counter % 3 == 1) {
      output_string = tens_map[input_string[i]] + output_string;
    }
    if (counter % 3 == 2) {
      output_string = single_map[input_string[i]] + std::string("hundert") + output_string;
    }
  }

  if (a < 0) {
    output_string = "minus " + output_string;
  }

  std::cout << "a: " << a << " = " << output_string << std::endl;
  return 0;
}
