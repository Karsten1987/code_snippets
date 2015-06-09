#include <iostream>

#include <vector>

#include <cstdint>
#include <algorithm>

enum class Players : int
{
  PLAYER_A=1,
  PLAYER_B=2
};

class TicTacToe
{
  public:

  TicTacToe()
  {
    for (int i=0;i<3;++i)
    {
      std::vector<int> row(3, 0);
      field_.push_back(row);
    }
  }

  std::vector<std::vector<int>> field_;
  Players next_player_ = Players::PLAYER_A;

  bool isWon( Players p ) const
  {
    // check rows
    for (auto i=0;i<3;++i)
    {
      const std::vector<int>& row_i = field_[i];
      auto sum = std::accumulate( row_i.begin(), row_i.end(),0 )*static_cast<int>(p);
      if ( sum == 3*static_cast<int>(p) )
      {
        return true;
      }

      std::vector<int> col_i = { field_[0][i], field_[1][i], field_[2][i] };
      sum = std::accumulate( col_i.begin(), col_i.end(), 0 )*static_cast<int>(p);
      if ( sum == 3*static_cast<int>(p) )
      {
        return true;
      }
    }
    // check both diagonals
    std::vector<int> diag1 = { field_[0][0], field_[1][1], field_[2][2] };
    auto sum = std::accumulate( diag1.begin(), diag1.end(), 0 );
    if ( sum == 3*static_cast<int>(p) )
    {
      return true;
    }
    std::vector<int> diag2 = { field_[0][2], field_[1][1], field_[2][0] };
    sum = std::accumulate( diag2.begin(), diag2.end(), 0 );
    if ( sum == 3*static_cast<int>(p) )
    {
      return true;
    }

    // global else
    return false;
  }

  // returns -1 for fouls, 0 for continuation, 1 for win
  int place( int x, int y, Players p )
  {
    if ( p != next_player_ )
    {
      std::cout << "wrong player turn. Expected player "<< static_cast<int>(next_player_) << std::endl;
      return -1;
    }
    if ( next_player_ == Players::PLAYER_A )
    {
      next_player_ = Players::PLAYER_B;
    }
    else
    {
      next_player_ = Players::PLAYER_A;
    }


    if (x < 0 || x >2 || y < 0 || y > 2)
    {
      std::cout << "index of game out of range " << std::endl;
      return -1;
    }
    if (field_[x][y] != 0)
    {
      std::cout << "field " << x << " " << y << " already occupied" << std::endl;
      return -1;
    }
    else
    {
      field_[x][y] = static_cast<int>(p);
    }

    if ( isWon( p ) )
    {
      return 1;
    }
    return 0;
  }

  void printField() const
  {
    for (int i=0;i<3;++i)
    {
      for (int j=0;j<3;++j)
      {
        std::cout << field_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

};

int main()
{

  TicTacToe game;

  auto won = game.place( 1,1, Players::PLAYER_A );
  won = game.place( 0,1, Players::PLAYER_B );
  won = game.place( 0,0, Players::PLAYER_A );
  won = game.place( 0,2, Players::PLAYER_B );
  won = game.place( 2,2, Players::PLAYER_A );
  if (won == 1)
  {
    std::cout << "Player " << static_cast<int>(Players::PLAYER_A) << " won " << std::endl;
  }
  
  return 0;
}
