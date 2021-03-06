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

QuadTree::~QuadTree() {
	QuadTree::recurseFree(root);
}

void QuadTree::recurseFree(QuadTree::Node* node) {
	if (node->children[0]) {
		for (int i = 0; i < 4; i++) {
			QuadTree::recurseFree(node->children[i]);
		}
	}
	free(node);
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

int QuadTree::getIndex(int x, int y, Node* node) {
	int index = 0;
  if (x >= node->x + node->size){
    index+=2;
  }
  if (y >= node->y + node->size){
    index++;
  }
	return index;
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
  int index = QuadTree::getIndex(x, y, node);
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
	cout << "Starting tick" << endl;
	QuadTree::Node* newTree = QuadTree::makeNewNode(-bounds, -bounds, bounds, NULL);
	set<pair<int, int> > deadSet;
	set<pair<int, int> > liveSet;
	cout << "Descending" << endl;
	QuadTree::descend(root, liveSet, deadSet);
	cout << "Checking Dead" << endl;
	QuadTree::checkDead(liveSet, deadSet);
	QuadTree::recurseFree(root);
	root = newTree;
	QuadTree::addToNewTree(liveSet);
}

void QuadTree::descend(QuadTree::Node* node, set<pair<int, int> >& liveSet, set<pair<int, int> >& deadSet) {
	if (!node->alive) return;
	if (node->size == 0) {
		int numNeighbors = QuadTree::countNeighbors(node->x, node->y, deadSet, true);
		if (numNeighbors == 2 || numNeighbors == 3) {
			liveSet.insert(pair<int,int>(node->x, node->y));
		}
		return;
	}
	if (node->children[0]) {
		for (int i = 0; i < 4; i++) {
			QuadTree::descend(node->children[i], liveSet, deadSet);
		}
	}
}

void QuadTree::checkDead(set<pair<int, int> >& liveSet, set<pair<int, int> >& deadSet) {
	for (set<pair<int, int> >::iterator it = deadSet.begin(); it != deadSet.end(); it++){
		cout << " " << (*it).first << "," << (*it).second;
    int numNeighbors = QuadTree::countNeighbors((*it).first, (*it).second, deadSet, false);
		if (numNeighbors == 3) {
			liveSet.insert(*it);
		}
  }
}

void QuadTree::addToNewTree(set<pair<int, int> >& liveSet) {
	for (set<pair<int, int> >::iterator it = liveSet.begin(); it != liveSet.end(); it++){
    QuadTree::addLiveCell((*it).first, (*it).second);
  }
}

int QuadTree::countNeighbors(int x, int y, set<pair<int, int> >& deadSet, bool gather) {
	int count = 0;
	for (int r = -1; r <= 1; r++) {
		for (int c = -1; c <= 1; c++) {
			if (!(r == 0 && c == 0) && QuadTree::isInBounds(x + c, y + r)) {
				if (QuadTree::isAlive(x + c, y + r)) {
					count++;
				} else {
					if (gather) deadSet.insert(pair<int,int>(x + c, y + r));
				}
			}
		}
	}
	return count;
}

bool QuadTree::isInBounds(int x, int y) {
	return (x >= -bounds && x <= bounds - 1) && (y >= -bounds && y <= bounds - 1);
}

bool QuadTree::isAlive(int x, int y) {
	return QuadTree::isAliveRecurse(x, y, root);
}

bool QuadTree::isAliveRecurse(int x, int y, Node* node) {
	if (!node->alive) return false;
	if (QuadTree::isCell(x, y, node)) return true;
	int index = QuadTree::getIndex(x, y, node);
	return isAliveRecurse(x, y, node->children[index]);
}
