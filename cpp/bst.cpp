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

Node* toBST( const std::vector<Node*>& vec, int lhs, int rhs )
{
  if ( vec.empty() )
  {
    return NULL;
  }

  if ( lhs>rhs )
  {
    return NULL;
  }

  int middle_idx = lhs + (rhs-lhs)/2;
  Node* const root = vec[middle_idx];
  root->lhs = toBST( vec, lhs, middle_idx-1);
  root->rhs = toBST( vec, middle_idx+1, rhs);
  return root;
}

void balanceTree( Node*& root )
{
  std::vector<Node*> vec;
  toVector(root, vec);

  root = toBST( vec, 0, vec.size()-1 );
}

int main()
{
  Node* root = new Node(1,1);
  insertNode( root, NULL );
  insertNode( new Node(2,2), root );
  insertNode( new Node(3,3), root );
  insertNode( new Node(4,4), root );
  insertNode( new Node(5,5), root );
  insertNode( new Node(6,6), root );
  insertNode( new Node(7,7), root );
  insertNode( new Node(8,8), root );

  balanceTree( root );
  std::cout << " root key lhs " << root->lhs->key <<std::endl;
  printBFS( root );


  return 0;
}
