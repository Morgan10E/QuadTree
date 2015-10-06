#include <iostream>
#include "QuadTree.hpp"


int main(int argc, char *argv[])
{
  QuadTree* tree = new QuadTree(8);
  tree->printTree();

  std::cout << std::endl;

  tree->addLiveCell(3,3);
  tree->printTree();

  std::cout << std::endl;

  tree->addLiveCell(2,2);
  tree->addLiveCell(-2,1);
  tree->addLiveCell(1,-4);
  tree->printTree();

	return 0;
}
