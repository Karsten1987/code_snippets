#include <iostream>

#include "grid.hpp"
#include "astar.hpp"

int main(int argc, char** argv)
{
  astar::Map map(10, 10);
  astar::GridIndex index1{3, 3};
  astar::GridIndex index2{3, 6};
  while (index1.row < 6)
  {
    map.set_obstacle(index1);
    map.set_obstacle(index2);
    ++index1.row;
    ++index2.row;
  }
  astar::GridIndex start{5, 5};
  map.set_start(start);
  astar::GridIndex goal{9, 9};
  map.set_goal(goal);
  map.print();

  astar::Astar astar(map);
  //astar.traverse_bfs();
  astar.traverse_greedy_bfs();
  return 0;
}
