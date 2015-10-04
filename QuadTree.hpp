#include <iostream>
#include <stdlib.h>
#include <string>

class QuadTree
{
	public:
		QuadTree();
		~QuadTree();
		// void add(int val);
		// void remove(int val);
		// int getGreatestValue();
		// int getLeastValue();
		void printTree();


	private:
		typedef struct Node{
			Node* children[4];
			Node* parent;
			int x;
      int y;
      int size;
      bool alive;
		} Node;
		Node* root;
    Node* makeNewNode(int x, int y, int size, QuadTree::Node* parent);
    void printTreeRecurse(Node* node);
};
