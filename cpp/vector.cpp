#include <iostream>
#include <vector>

void modify(int &i)
{
  i+=1000;
}

int main()
{
  std::vector<int> my_vec;
  for (int i=0; i<10; ++i)
  {
    my_vec.push_back(i);
  }

  modify(my_vec[3]);

  for (int i=0; i<10; ++i)
  {
    std::cerr << my_vec[i] << std::endl;
  }

  std::vector<int> lhs = {1,2,3,4,5};
  std::vector<int> rhs = {6,7,8,9,10};

  lhs.insert( lhs.end(), rhs.begin(), rhs.end() );
  std::cout << "new size of lhs " << lhs.size() << std::endl;

  return 0;
}
