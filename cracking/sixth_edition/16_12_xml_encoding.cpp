#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (const auto & el : vec) {
    std::cout << "[" << el << "]";
  }
  std::cout << std::endl;
}

std::string encode(const std::string & s, const std::unordered_map<std::string, size_t> & map)
{
  std::string encoded_s = "";

  char * c_string = strdup(s.c_str());
  std::vector<std::string> tokens;
  char * pch = strtok(c_string,"\n\t< >");
  while (pch != NULL)
  {
    tokens.push_back(std::string(pch));
    pch = strtok (NULL, "\n\t< >");
  }

  print_vector(tokens);

  for (auto i = 0ul; i < tokens.size(); ++i) {
    if (tokens[i][0] == '/') {
      encoded_s += "0";
      continue;
    }

    auto equal = tokens[i].find("=");
    if (equal != tokens[i].npos) {
      auto att_name = tokens[i].substr(0, equal);
      auto att_value = tokens[i].substr(equal + 2, tokens[i].size() - equal - 3);
      std::cout << att_name << " and vlaue " << att_value << std::endl;
      auto mapping = map.find(att_name);
      if (mapping != map.end()) {
        encoded_s += std::to_string(mapping->second);
      } else {
        std::cout << "something went wrong: " << att_name << " not found in map" << std::endl;
      }
      encoded_s += att_value;
      continue;
    }

    auto mapping = map.find(tokens[i]);
    if (mapping != map.end()) {
      encoded_s += std::to_string(mapping->second);
    } else {
      encoded_s += tokens[i];
    }
  }

  return encoded_s;
}

int main()
{
  std::string s = "<family lastName=\"McDowell\" state=\"CA\">\n";
  s += "\t<person firstName=\"Gary\">Some_Message</person>\n";
  s += "</family>\n";

  std::unordered_map<std::string, size_t> map;
  map["family"] = 1;
  map["person"] = 2;
  map["firstName"] = 3;
  map["lastName"] = 4;
  map["state"] = 5;

  std::string encoded_s = encode(s, map);

  std::cout << s << std::endl;
  std::cout << encoded_s << std::endl;
}
