#include <iostream>

#include <queue>
#include <vector>

struct Node
{
  int key;
  int value;
  Node* lhs = NULL;
  Node* rhs = NULL;

  Node( int k, int v )
    : key(k),
    value(v)
  {}
};


void printInorder( Node* root )
{
  if ( root == NULL )
  {
    return;
  }

  printInorder( root->lhs );
  std::cout << root->key  << std::endl;
  printInorder( root->rhs );
}

void printBFS( Node* root )
{
  if (root == NULL)
  {
    return;
  }

  std::queue<Node*> queue;
  queue.push( root );
  while( !queue.empty() )
  {
    Node* n = queue.front();
    std::cout << n->key << std::endl;
    if ( n->lhs != NULL)
    {
      queue.push( n->lhs );
    }
    if ( n->rhs != NULL )
    {
      queue.push( n->rhs );
    }
    queue.pop();
  }
}

void insertNode( Node* n, Node* root )
{
  if ( root == NULL )
  {
    root = n;
    return;
  }

  if ( root->lhs == NULL && root->rhs == NULL ) // we have a leaf
  {
    if ( n->key < root->key )
    {
      root->lhs = n;
      return;
    }
    else
    {
      root->rhs = n;
      return;
    }
  }

  if ( n->key < root->key )
  {
    return insertNode(n, root->lhs);
  }
  else
  {
    return insertNode(n, root->rhs);
  }
}

void toVector( Node* root, std::vector<Node*>& vec )
{
  if ( root == NULL )
  {
    return;
  }

  toVector( root->lhs, vec );
  vec.push_back( root );
  toVector( root->rhs, vec );
  return;
}

void toBST( std::vector<Node*>& vec, int lhs, int rhs, Node* root )
{
  if ( vec.size() == 0)
  {
    root = NULL;
  }

  int middle_idx = lhs + (rhs-lhs)/2;

  if (root == NULL)
  {
    root = vec[middle_idx];
  }
  toBST( vec, 0, middle_idx-1, root );
  toBST( vec, middle_idx+1, rhs, root );
  return;
  // half the vector, get middle index as root
}

void balanceTree( Node* root )
{
  std::vector<Node*> vec;
  toVector(root, vec);
  for (auto i=0; i<vec.size(); ++i)
  {
    std::cout << vec[i]->key << std::endl;
  }
  root = NULL;
  toBST( vec, 0, vec.size()-1, root );
  printInorder( root );
}

int main()
{
  Node* root = new Node(1,1);
  insertNode( root, NULL );
  insertNode( new Node(2,2), root );
  insertNode( new Node(3,3), root );
  insertNode( new Node(4,4), root );
  insertNode( new Node(5,5), root );

  balanceTree( root );
  //printBFS( root );


  return 0;
}
