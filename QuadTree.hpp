#include <iostream>
#include <stdlib.h>
#include <string>
#include <set>
#include <utility>

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


		int countNeighbors(int x, int y, std::set<std::pair<int, int> >& deadSet);

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
		void recurseFree(Node* node);
    void printTreeRecurse(Node* node);
    void addLiveCellRecurse(int x, int y, Node* node);
		bool isInBounds(int x, int y);
		bool isCell(int x, int y, Node* node);
		int getIndex(int x, int y, Node* node);
		void descend(Node* node, Node* newTree, std::set<std::pair<int, int> >& deadSet);
		//int countNeighbors(int x, int y, std::set<std::pair<int, int> >& deadSet);
		bool isAliveRecurse(int x, int y, Node* node);


};
