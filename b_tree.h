#ifndef B_TREE_H
#define B_TREE_H


#include <vector>

template <class T> class Node
{
	friend class B_tree;

	std::vector <T> data;	//
	Node * parent;
	Node * child;
};

template <class T> class B_tree
{
public:
	B_tree();
	void add_node(std::vector<T>);
private:
	Node * head;	//Понадобится для удаления
};



#endif /* B_TREE_H */