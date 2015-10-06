# include "QuadTree.hpp"

using namespace std;

QuadTree::QuadTree() {
	root = QuadTree::makeNewNode(-4, -4, 4, NULL);
	bounds = 4;
}

QuadTree::QuadTree(int size) {
	root = QuadTree::makeNewNode(-size, -size, size, NULL);
	bounds = size;
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

void QuadTree::addLiveCell(int x, int y){
  QuadTree::addLiveCellRecurse(x, y, root);
}

bool QuadTree::isCell(int x, int y, Node* node) {
	return node->size == 0 && node->x == x && node->y == y;
}

void QuadTree::addLiveCellRecurse(int x, int y, QuadTree::Node* node){
  cout << "LiveCellRecurse:(" << node->x << ", " << node->y << ") Size:" << node->size << endl;
	node->alive = true;
  if (QuadTree::isCell(x, y, node)) {
    //node->alive = true;
    return;
  } else if (node->size == 0){
    cout<< "error inserting node" << endl;
    return;
  }

  if (node->children[0] == NULL){
    int count = 0;
    for (int j = 0; j <= 1; j++){
      for (int k = 0; k <= 1; k++){
        node->children[count] = QuadTree::makeNewNode(node->x + node->size*j, node->y + node->size*k, node->size/2, node);
        count++;
      }
    }
  }

  cout << "Recursing" << endl;
  int index = 0;
  if (x >= node->x + node->size){
    index+=2;
  }
  if (y >= node->y + node->size){
    index++;
  }
  QuadTree::addLiveCellRecurse(x, y, node->children[index]);
}

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

void QuadTree::tick(){

}

bool QuadTree::isInBounds(int x, int y) {
	return (x > -bounds && x < bounds - 1) && (y > -bounds && y < bounds - 1);
}

bool QuadTree::isAlive(int x, int y) {
	return QuadTree::isAliveRecurse(x, y, root);
}

bool QuadTree::isAliveRecurse(int x, int y, Node* node) {
	if (!node->alive) return false;
	return true;
}
