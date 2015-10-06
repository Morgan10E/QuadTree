#include <iostream>
#include <stdlib.h>
#include <string>

class QuadTree
{
	public:
		QuadTree();
		QuadTree(int size);
		~QuadTree();
		// void add(int val);
		// void remove(int val);
		// int getGreatestValue();
		// int getLeastValue();
		void printTree();
    void addLiveCell(int x, int y);
		void tick();
		bool isAlive(int x, int y);

	private:
		int bounds;
		typedef struct Node{
			Node* children[4];
			Node* parent;
			int x;
      int y;
      int size;
      bool alive;
		} Node;
		Node* root;
    Node* makeNewNode(int x, int y, int size, Node* parent);
    void printTreeRecurse(Node* node);
    void addLiveCellRecurse(int x, int y, Node* node);
		bool isInBounds(int x, int y);
		bool isCell(int x, int y, Node* node);
		bool isAliveRecurse(int x, int y, Node* node);
};
