#include <iostream>
#include <vector>
#include <bitset>

#include <algorithm>

std::vector<int> mergeOrRemove( std::vector<int>& lhs, std::vector<int>& rhs )
{
  std::vector<int> merge;
  merge.reserve(lhs.size()+rhs.size());

  size_t lhs_idx = 0;
  size_t rhs_idx = 0;

  while (lhs_idx != lhs.size() && rhs_idx != rhs.size())
  {
    if ( lhs[lhs_idx] < rhs[rhs_idx] )
    {
      merge.push_back( lhs[lhs_idx] );
      ++lhs_idx;
    }
    else if ( lhs[lhs_idx] > rhs[rhs_idx] )
    {
      merge.push_back( rhs[rhs_idx] );
      ++rhs_idx;
    }
    else if ( lhs[lhs_idx] == rhs[rhs_idx] )
    {
      std::cout << "found duplicate " << lhs[lhs_idx] << std::endl;
      // skip on in case of equality
      merge.push_back( lhs[lhs_idx] );
      ++rhs_idx;
      ++lhs_idx;
    }
  }
  // dump lhs in case
  while (lhs_idx < lhs.size())
  {
    merge.push_back( lhs[lhs_idx] );
    ++lhs_idx;
  }
  // dump rhs in case
  while (rhs_idx < rhs.size())
  {
    merge.push_back( rhs[rhs_idx] );
    ++rhs_idx;
  }
  return merge;
}

std::vector<int> removeDuplicates( std::vector<int>& input, int lhs, int rhs )
{
  if (input.size() <= 1)
  {
    return std::vector<int>();
  }

  if (lhs == rhs)
  {
    std::vector<int> ret;
    ret.push_back( input[lhs] );
    return ret;
  }
  int middle_idx = lhs + (rhs-lhs)/2;
  std::vector<int> input_lhs = removeDuplicates( input, lhs, middle_idx );
  std::vector<int> input_rhs = removeDuplicates( input, middle_idx+1, rhs);

  return mergeOrRemove( input_lhs, input_rhs );
}


std::vector<char> removeDuplicates( std::string& input )
{
  std::vector<char> duplicates;
  duplicates.reserve( input.size()/10 );

  long long map = 0LL;
  for (int i=0; i<input.size(); ++i)
  {
    if ( (map & (1LL << (input[i]-'a'))) >0 )
    {
      duplicates.push_back( input[i] );
    }
    else
    {
      map |= (1LL << (input[i]-'a'));
    }
  }
  return duplicates;
}

int main()
{

  std::vector<int> all = {1,2,1,4,3,1,432,12,32,5,2,34324234,54,432,543,65752,421,13132,1,23,2,3,4,53,24,432,3};
  std::cout << "still integer? " << static_cast<int>(34324234) << std::endl;
  //std::sort( all.begin(), all.end() );
  std::vector<int> dups = removeDuplicates( all, 0, all.size()-1 );
  return 0;
}
