#include <iostream>
#include <queue>
#include <vector>

struct Node
{
  Node* lhs;
  Node* rhs;
  int value;

  Node( int i ):
    lhs(NULL),
    rhs(NULL),
    value(i)
  {}
};


class BinaryTree
{
private:
  void insert( Node* node, Node* parent )
  {
    if( parent->lhs == NULL && node->value < parent->value )
    {
      parent->lhs = node;
      return;
    }
    if( parent->rhs == NULL && node->value >= parent->value )
    {
      parent->rhs = node;
      return;
    }

    if( parent->lhs != NULL && parent->value > node->value )
    {
      insert(node, parent->lhs);
    }
    if( parent->rhs != NULL && parent->value <= node->value )
    {
      insert(node, parent->rhs);
    }
  }

  void deleteTree( Node* node )
  {
    if ( node == NULL )
    {
      return;
    }

    deleteTree(node->lhs);
    deleteTree(node->rhs);

    std::cout << "delete node " << node->value << std::endl;
    delete node;
    node = NULL;
  }

  void sortedVector( Node* node, std::vector<Node*>& vec ) const
  {
    if (node == NULL)
    {
      return;
    }

    sortedVector( node->lhs, vec );
    vec.push_back( new Node(node->value) );
    sortedVector( node->rhs, vec );
  }



public:
  Node* root = NULL;

  ~BinaryTree()
  {
    deleteTree();
  }

  void deleteTree()
  {
    if (root != NULL)
    {
      deleteTree( root );
    }
    root = NULL;
  }

  void insertNode( Node* node )
  {
    if( root == NULL ) // it's the root
    {
      std::cout << "set root node " << node->value << std::endl;
      root = node;
      return;
    }
    insert(node, root);
  }

  void insertFromList( const std::vector<Node*>& vec, int lhs, int rhs, Node* parent )
  {
    if (lhs == rhs) // we have a leaf
    {
      return;
    }

    Node* root = vec[(lhs+rhs)/2];
    std::cout << "new middle element " << root->value << std::endl;
    insertFromList( vec, lhs, static_cast<int>((lhs+rhs)/2), root );
    insertFromList( vec, static_cast<int>((lhs+rhs)/2)+1, rhs, root );

    if (parent == NULL)
    {
      parent = root;
      return;
    }
    if (root->value < parent->value)
    {
      parent->lhs = root;
    }
    else
    {
      parent->rhs = root;
    }
  }

  void balanceTree( )
  {
    if ( root == NULL )
    {
      return;
    }

    std::vector<Node*> vec;
    sortedVector( root, vec );

    std::cout << "found vector of " << vec.size() << std::endl;
    std::cout << "middle element " << vec[vec.size()/2]->value << std::endl;
    for( size_t i=0; i<vec.size(); ++i )
    {
      std::cerr << vec[i]->value << " -> ";
    }
    std::cerr << "NULL" <<std::endl;

    deleteTree();
    insertFromList( vec, 0, static_cast<int>(vec.size()-1), root );
  }

  void printPreorder( Node* root ) const
  {
    if (root==NULL)
    {
      return;
    }

    std::cout << root->value << std::endl;
    printPreorder( root->lhs );
    printPreorder( root->rhs );
  }

  void printInorder( Node* root ) const
  {
    if (root==NULL)
    {
      return;
    }

    printInorder( root->lhs );
    std::cout << root->value << std::endl;
    printInorder( root->rhs );
  }

  void printPostorder( Node* root ) const
  {
    if (root==NULL)
    {
      return;
    }

    printPostorder( root->lhs );
    printPostorder( root->rhs );
    std::cout << root->value << std::endl;
  }

  void printBFS( Node* root ) const
  {
    if ( root == NULL )
    {
      std::cout << "no root leaf set" << std::endl;
      return;
    }

    std::queue<Node*> q;
    q.push( root );
    while (!q.empty())
    {
      Node* n = q.front();
      q.pop();
      std::cout << n->value << std::endl;

      if (n->lhs != NULL )
      {
        q.push( n->lhs );
      }
      if (n->rhs != NULL )
      {
        q.push( n->rhs );
      }
    }
  }

  void printTree( void (BinaryTree::*f)(Node*)const ) const
  {
    (this->*f)( this->root );
  }
};

/*
                 10
               /    \
             6      14
            / \    /  \
           5   8  11  18
*/

int main()
{
  BinaryTree bt;

  bt.insertNode( new Node(10) );
  bt.insertNode( new Node(6) );
  bt.insertNode( new Node(5) );
  bt.insertNode( new Node(8) );
  bt.insertNode( new Node(14) );
  bt.insertNode( new Node(11) );
  bt.insertNode( new Node(18) );
  bt.insertNode( new Node(7) );
  bt.insertNode( new Node(9) );
  std::cout << "print preorder" << std::endl;
  bt.printTree( &BinaryTree::printPreorder);
  std::cout << "print inorder" << std::endl;
  bt.printTree( &BinaryTree::printInorder);
  std::cout << "print postorder" << std::endl;
  bt.printTree( &BinaryTree::printPostorder);
  std::cout << "print BFSorder" << std::endl;
  bt.printTree( &BinaryTree::printBFS );

  std::cout << "balancing the tree" << std::endl;
  bt.balanceTree();
  std::cout << "print BFSorder" << std::endl;
  bt.printTree( &BinaryTree::printBFS );
  std::cout << "gonna delete tree" << std::endl;
  bt.deleteTree();
  bt.printTree( &BinaryTree::printInorder);
  return 0;
}
