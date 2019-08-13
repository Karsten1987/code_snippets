#include <iostream>
#include <string>
#include <stack>

double calculate(const std::string & equation)
{
  std::stack<double> stack;

  auto extract_number = [&equation](size_t & i) -> double {
    auto begin = i;
    while (equation[i] != '+' && equation[i] != '-' && equation[i] != '*' && equation[i] != '/') {
      ++i;
    }
    auto d = std::stod(equation.substr(begin, i));
    --i;
    printf("extracted %f\n", d);
    return d;
  };

  int sign = 1;
  for (size_t i = 0; i < equation.size(); ++i) {
    auto  & c = equation[i];
    if (c == '+') {
      continue;
    }
    if (c == '-') {
      sign = -1;
    }
    else if (c == '/') {
      auto n = stack.top();
      stack.pop();
      auto m = extract_number(++i);
      stack.push(sign * n / m);
      sign = 1;
    }
    else if (c == '*') {
      auto n = stack.top();
      stack.pop();
      auto m = extract_number(++i);
      stack.push(sign * n * m);
      sign = 1;
    } else {
      auto n = extract_number(i);
      stack.push(sign * n);
      sign = 1;
    }
  }

  double sum = 0;
  while (!stack.empty()) {
    auto d = stack.top();
    printf("on stack %f\n", d);
    stack.pop();
    sum += d;
  }

  return sum;
}

int main()
{
  std::string equation = "2*3+5/6*3+15";
  double result = calculate(equation);
  std::cout << equation << " = " << result << std::endl;
}
