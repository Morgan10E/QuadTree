#include <iostream>
#include "QuadTree.hpp"


int main(int argc, char *argv[])
{
  QuadTree* tree = new QuadTree();
  tree->printTree();
  std::cout << std::endl;
  tree->addLiveCell(3,3);
  tree->printTree();

	return 0;
}
