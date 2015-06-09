#include <iostream>
#include <vector>

std::vector<std::vector<int>> getPermutations( const std::vector<int>& vec )
{
  std::vector<std::vector<int>> res;
  if (vec.size() == 2)
  {
    std::vector<int> i1 = {vec[0], vec[1]};
    std::vector<int> i2 = {vec[1], vec[0]};
    res.push_back( i1 );
    res.push_back( i2 );
    return res;
  }

  int i = vec.front();
  std::vector<std::vector<int>> old_perm = getPermutations( std::vector<int>(vec.begin()+1, vec.end() ));
  for (auto idx=0;idx<old_perm.size();++idx)
  {
    for (int input_idx=0;input_idx<old_perm[idx].size()+1;++input_idx)
    {
      std::vector<int> new_perm;
      new_perm.reserve(old_perm[idx].size()+1);

      for (auto k=0;k<input_idx;++k)
      {
        new_perm.push_back( old_perm[idx][k] );
      }
      new_perm.push_back(i);
      for (auto k=input_idx;k<old_perm[idx].size();++k)
      {
        new_perm.push_back( old_perm[idx][k] );
      }

      res.push_back( new_perm );
    }
  }
  return res;
}

int main()
{

  std::vector<int> input = {1,2,3,4,5};
  std::vector<std::vector<int>> perms = getPermutations(input);
  for (auto i=0;i<perms.size();++i)
  {
    for (auto j=0;j<perms[i].size();++j)
    {
      std::cout << perms[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << perms.size() << std::endl;

  return 0;
}
