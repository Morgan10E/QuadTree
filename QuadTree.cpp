# include "QuadTree.hpp"

using namespace std;

QuadTree::QuadTree() {
	root = QuadTree::makeNewNode(0, 0, 32, NULL);
}

QuadTree::Node* QuadTree::makeNewNode(int x, int y, int size, QuadTree::Node* parent){
	QuadTree::Node* newNode = new Node();
	newNode->x = x;
  newNode->y = y;
	newNode->parent = parent;
  newNode->size = size;
  newNode->alive = false;
  for (int i = 0; i < 4; i++) newNode->children[i] = NULL;
	return newNode;
}

// void QuadTree::addLiveCell(int x, int y){
//   QuadTree::addLiveCellRecurse(x, y, root);
// }
//
// void QuadTree::addLiveCellRecurse(int x, int y, QuadTree::Node* node){
//   if (node->size == 0) {
//     node->x = x;
//     node->y = y;
//     node->alive = true;
//   } else if (node->children[0] == NULL){
//     for (int i = 0; i < 4; i++) {
//
//     }
//   }
// }

void QuadTree::printTree(){
  QuadTree::printTreeRecurse(root);
}

void QuadTree::printTreeRecurse(Node* node){
  string toPrint = "Size: " + to_string(node->size) + ", (" + to_string(node->x) + ", " + to_string(node->y) + ")";
  if (node->alive) toPrint += " ALIVE";
  else toPrint += " dead";
  cout << toPrint << endl;
  if (node->children[0]) {
    for (int i = 0; i < 4; i++){
      QuadTree::printTreeRecurse(node->children[i]);
    }
  }
}
