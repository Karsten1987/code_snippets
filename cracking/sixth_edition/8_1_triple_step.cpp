#include <iostream>
#include <vector>

struct Node
{
  Node * next_1;
  Node * next_2;
  Node * next_3;
  size_t current_step;
};

void add_steps(Node * root, size_t current_sum, size_t max_steps, size_t & different_ways)
{
  if (current_sum == max_steps) {
    ++different_ways;
    return;
  }

  if (current_sum + 1 <= max_steps) {
    root->next_1 = new Node();
    root->next_1->current_step = 1;
    add_steps(root->next_1, current_sum + 1, max_steps, different_ways);
  }
  if (current_sum + 2 <= max_steps) {
    root->next_2 = new Node();
    root->next_2->current_step = 2;
    add_steps(root->next_2, current_sum + 2, max_steps, different_ways);
  }
  if (current_sum + 3 <= max_steps) {
    root->next_3 = new Node();
    root->next_3->current_step = 3;
    add_steps(root->next_3, current_sum + 3, max_steps, different_ways);
  }
}

Node * construct_step_tree(size_t max_steps)
{
  Node * root = new Node();
  root->current_step = 0;
  size_t different_ways = 0;
  add_steps(root, 0, max_steps, different_ways);

  std::cout << "added " << different_ways << " routes into the tree" << std::endl;
  return root;
}

void print_tree(Node * root, std::vector<std::vector<size_t>> & all_trajectories, std::vector<size_t> & vec)
{
  if (root == nullptr) {
    return;
  }

  vec.push_back(root->current_step);

  if (root->next_1 == nullptr && root->next_2 == nullptr && root->next_3 == nullptr)
  {
    all_trajectories.push_back(vec);
  }

  print_tree(root->next_1, all_trajectories, vec);
  print_tree(root->next_2, all_trajectories, vec);
  print_tree(root->next_3, all_trajectories, vec);

  vec.pop_back();
}

int count_ways(int n)
{
  if (n < 0) {
    return 0;
  }
  if (n == 0) {
    return 1;
  }
  return count_ways(n - 3) + count_ways(n -2) + count_ways(n - 1);
}

int main()
{
  auto max_steps = 8ul;
  Node * root = construct_step_tree(max_steps);
  std::vector<size_t> vec;
  std::vector<std::vector<size_t>> all_trajectories;
  print_tree(root, all_trajectories, vec);
  for (auto & traj : all_trajectories) {
    for (auto & el : traj) {
      std::cout << el << " --> ";
    }
    std::cout << "|" << std::endl;
  }
  std::cout << "found " << all_trajectories.size() << " ways" << std::endl;
  auto rec_size = count_ways(8);
  std::cout << "found recursively " << rec_size << " ways" << std::endl;
  return 0;
}
