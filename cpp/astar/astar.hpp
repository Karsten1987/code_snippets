#pragma once

#include <iostream>
#include <queue>
#include <thread>

#include "grid.hpp"

namespace astar
{

struct PathNode
{
  GridIndex parent;
};

class Astar
{
public:
  Astar(Map & map):
    map_(map),
    path_map_(map.num_rows(), map.num_cols())
  {}

  void
  traverse_bfs()
  {
    std::queue<GridIndex> bfs_queue;
    GridIndex start = map_.get_start_index();
    bfs_queue.push(map_.get_start_index());

    GridIndex goal = map_.get_goal_index();

    while (!bfs_queue.empty())
    {
      GridIndex head = bfs_queue.front();
      bfs_queue.pop();
      if (head.row == goal.row && head.col == goal.col)
      {
        break;
      }

      auto neighbours = map_.get_valid_neighbours(head);
      for (auto neighbour : neighbours)
      {
        map_.set_visited(neighbour);
        bfs_queue.push(neighbour);
        GridValue<PathNode> path_node;
        path_node.value.parent = head;
        path_map_.set_value(neighbour, path_node);
      }
      map_.print();
      std::cout << " ****** queue size: " << bfs_queue.size() << " ******** " << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  void
  traverse_greedy_bfs()
  {
    auto compare_grid_index = [&](const GridIndex & lhs, const GridIndex & rhs) -> bool {
      GridIndex goal = map_.get_goal_index();
      auto lhs_to_goal
        = std::abs(static_cast<int>(lhs.col-goal.col))
        + std::abs(static_cast<int>(lhs.row-goal.row));
      auto rhs_to_goal
        = std::abs(static_cast<int>(rhs.col-goal.col))
        + std::abs(static_cast<int>(rhs.row-goal.row));
      if (lhs_to_goal > rhs_to_goal)
        return true;
      return false;
    };

    std::priority_queue<GridIndex, std::vector<GridIndex>, decltype(compare_grid_index)>
      greedy_queue(compare_grid_index);
    GridIndex start = map_.get_start_index();
    greedy_queue.push(map_.get_start_index());

    GridIndex goal = map_.get_goal_index();

    while (!greedy_queue.empty())
    {
      GridIndex head = greedy_queue.top();
      greedy_queue.pop();
      if (head.row == goal.row && head.col == goal.col)
      {
        break;
      }
      auto neighbours = map_.get_valid_neighbours(head);
      for (auto neighbour : neighbours)
      {
        if (neighbour != map_.get_start_index()
            && neighbour != map_.get_goal_index())
        {
          map_.set_visited(neighbour);
        }
        greedy_queue.push(neighbour);
        GridValue<PathNode> path_node;
        path_node.value.parent = head;
        path_map_.set_value(neighbour, path_node);
      }
      map_.print();
      std::cout << " ****** queue size: " << greedy_queue.size() << " ******** " << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    GridValue<PathNode> path_goal = path_map_.get_value(goal);
    GridIndex grid_index = goal;
    bool start_reached = false;
    GridValue<std::uint8_t> path_printer {0, " p |"};

    while (!start_reached)
    {
      if (grid_index.row == start.row && grid_index.col == start.col) {
        start_reached = true;
      }

      std::cout << "Row: " << grid_index.row << " Col: " << grid_index.col << std::endl;
      map_.set_value(grid_index, path_printer);
      path_goal = path_map_.get_value(path_goal.value.parent);
      grid_index = path_goal.value.parent;
    }
  }

private:
  Map & map_;
  Grid<PathNode> path_map_;
};

}  // namespace astar
