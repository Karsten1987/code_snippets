#include <stdio.h>
#include <iostream>
#include <map>
#include <typeinfo>

struct Node {
	int value;
	Node* p_next;
};

void printList(Node* root){
	std::cerr << root->value;
	while(root->p_next != NULL)
	{
		root = root->p_next;
		std::cerr << root->value;
	}
	std::cerr << std::endl;
}

void insertNode(Node* root, int value, Node* closing = NULL)
{
	while(root->p_next != NULL)
	{
		root = root->p_next;
	}
	Node* n = new Node();
	n->value = value;

	n->p_next = closing;
	root->p_next = n;
}

template <typename T>
T createFibbonacci(T a, T b, int counter)
{
	if (counter > 10){
		return a+b;
	}
	else{
		std::cerr << a << std::endl;
		return createFibbonacci(b, a+b, ++counter);
	}
}

		


Node* reverseList(Node* root)
{
	Node* p_x = root;
	Node* p_l = NULL;
	while(p_x->p_next != NULL)
	{
		Node* p_r = p_x->p_next;
		p_x->p_next = p_l;
		p_l = p_x;
		p_x = p_r;
	}
	p_x->p_next = p_l;
	return p_x;
}

Node* initList()
{

	Node* root;
	root->value = 1;
	return root;
}		

bool isCyclic(Node* init)
{
	Node* head = init;
	
	while (init->p_next != NULL)
	{
		if (init->p_next == head)
		{
			return true;
		}
		init = init->p_next;
	}
	return false;
}

int main() 
{
	Node* init = new Node();
	init->value = 1;
	init->p_next = NULL;

	insertNode(init, 2);
	insertNode(init, 3);
	insertNode(init, 4);
	insertNode(init, 5);
	insertNode(init, 6);
	std::cerr << "is cyclic: " << (isCyclic(init)?"true":"false") << std::endl;
	insertNode(init, 7,init);
	std::cerr << "is cyclic: " << (isCyclic(init)?"true":"false") << std::endl;

	createFibbonacci(1,2,0);
	createFibbonacci(1.3,1.2,0);


	int* i = new int[5];
	i[0] = 1;
	i[1] = 2;
	for (int k=0; k<6; ++k)
	{
		std::cerr << i[k] << std::endl;
	}

	delete[] i;
	i = 0;
	
	for (int k=0; k<6; ++k)
	{
		std::cerr << i[k] << std::endl;
	}



	return 0;
}
