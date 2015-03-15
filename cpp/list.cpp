#include <stdio.h>
#include <iostream>


struct node
{
	int value;
	node* p_next;
};

node* reverseList(node* init_node) {
  node* new_root = 0;
  while (init_node) {
    node* next = init_node->p_next;
    init_node->p_next = new_root;
    new_root = init_node;
    init_node = next;
  }
  return new_root;
}

node* inverseList(node* init_node)
{
	node* p_left = 0;
	node* p_x = init_node;

	while (p_x->p_next !=NULL){
		node* p_right = p_x->p_next;
		p_x->p_next = p_left;
		p_left = p_x;
		p_x = p_right;
	}
	p_x->p_next = p_left;
	return p_x;
}

void printList(node& node_init)
{
	node* iter;
	iter  = &node_init;
	while (iter->p_next != NULL)
	{
		std::cerr << iter->value ;
		iter = iter->p_next;
	}
	std::cerr << iter->value << std::endl;
}

int insertNode(node& element, node& element_first)
{
	int counter = 0;

	node* iter;
	iter = &element_first;
	while(iter->p_next != NULL)
	{
		iter = iter->p_next;
		counter++;
	}
	iter->p_next = &element;
	return counter;

}

int main()
{
	node node_init;
	node_init.value = 1;
	node_init.p_next = NULL;

	node element1;
	element1.value = 2;
	element1.p_next = NULL;
	
	int idx1 = insertNode(element1, node_init);
	std::cerr << "new element inserted at idx: " << idx1 << std::endl;

	node element2;
	element2.value = 3;
	element2.p_next = NULL;
	
	int idx2 = insertNode(element2, node_init);
	std::cerr << "new element inserted at idx: " << idx2 << std::endl;

	node element3;
	element3.value = 4;
	element3.p_next = NULL;
	
	int idx3 = insertNode(element3, node_init);
	std::cerr << "new element inserted at idx: " << idx3 << std::endl;

	printList(node_init);

	node* root = &node_init;
	node* inv = inverseList(root);
	std::cerr << "list inverted" << std::endl;
	printList(*inv);
	return 0;

}
