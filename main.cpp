#include <iostream>
#include "QuadTree.hpp"


int main(int argc, char *argv[])
{
  QuadTree* tree = new QuadTree(4);
  tree->printTree();

  std::cout << std::endl;

  tree->addLiveCell(3,3);
  tree->printTree();

  std::cout << std::endl;

  tree->addLiveCell(2,2);
  tree->addLiveCell(-2,1);
  tree->addLiveCell(1,-4);
  tree->addLiveCell(1,-3);
  tree->addLiveCell(2,-4);
  tree->printTree();

  std::set<std::pair<int, int> > deadSet;

  std::cout << tree->countNeighbors(1, -4, deadSet, true) << std::endl;
  for (std::set<std::pair<int, int> >::iterator it = deadSet.begin(); it != deadSet.end(); it++){
    std::cout << " " << (*it).first << "," << (*it).second;
  }

  std::cout << std::endl;

  // tree->tick();
  // tree->printTree();


  free(tree);

	return 0;
}
