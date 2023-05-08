#include <iostream>
#include <vector>
#include <stack>
#include <unistd.h>
#include <queue>
#include <cmath>
#include "Node.h"

typedef vector<vector<int>> intVec;

//------------Operators------------
intVec switchPoints(int x, int y, int i, int j, intVec puzzle) {
    int temp = puzzle[i][j];
    puzzle[x][y] = temp;
    puzzle[i][j] = 0;
    return puzzle;
}

intVec shiftDown(intVec puzzle) {
    int n = 0, m = 0;
    for (int j = 0; j < 3; j++) {
        if (puzzle[0][j] == 0) return puzzle;
    }
    for (int j = 1; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (puzzle[j][k] == 0) {
                n = j;
                m = k;
            }
        }
    }
    return switchPoints(n, m, n - 1, m, puzzle);
}

intVec shiftUp(intVec puzzle) {
    int n = 0, m = 0;
    for (int j = 0; j < 3; j++) {
        if (puzzle[2][j] == 0) return puzzle;
    }
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 3; k++) {
            if (puzzle[j][k] == 0) {
                n = j;
                m = k;
            }
        }
    }
    return switchPoints(n, m, n + 1, m, puzzle);
}

intVec shiftRight(intVec puzzle) {
    int n = 0, m = 0;
    for (int j = 0; j < 3; j++) {
        if (puzzle[j][0] == 0) return puzzle;
    }
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (puzzle[j][k] == 0) {
                n = j;
                m = k;
            }
        }
    }
    return switchPoints(n, m, n, m - 1, puzzle);
}

intVec shiftLeft(intVec puzzle) {
    int n = 0, m = 0;
    for (int j = 0; j < 3; j++) {
        if (puzzle[j][2] == 0) return puzzle;
    }
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 2; k++) {
            if (puzzle[j][k] == 0) {
                n = j;
                m = k;
            }
        }
    }
    return switchPoints(n, m, n, m + 1, puzzle);
}

//------------Print state nodes------------
void printPuzzleNodes(const node& n, int expandedNodes, int maxQueueSize) {
    stack<node> nodeStack;
    node current = n;

    nodeStack.push(current);

    while (nullptr != current.p) {
        current = *current.p;
        nodeStack.push(current);
    }

    cout << "Expanding state" << endl;
    nodeStack.top().printPuzzle();
    cout << "\n";

    nodeStack.pop();

    while (nodeStack.size() > 1) {
        cout << "The best state to expand with g(n) = " << nodeStack.top().costUniform
             << " and h(n) = " << nodeStack.top().costHeuristic << " is...\n";

        nodeStack.top().printPuzzle();

        cout << "Expanding this node...\n" << endl;
        nodeStack.pop();
    }

    cout << "\nGoal !!!\n" << endl;
    cout << "To solve this problem the search algorithm expanded a total of " << expandedNodes << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << maxQueueSize << endl;
    cout << "The depth of the goal node was " << nodeStack.top().costUniform << "." << endl;
}

//------------Determines if previous nodes have been visited------------
bool previousNodes(const intVec& puzzle, const vector<node>& traversedNodes) {
    for (const auto& visitedNode : traversedNodes) {
        if (visitedNode.puzzle == puzzle) {
            return true;
        }
    }
    return false;
}



using namespace std;
const intVec goalState = {{1,2,3},{4,5,6},{7,8,0}};
vector<node> traversedNodes;
priority_queue<node, vector<node>, comparison> searchQueue;

void solvePuzzle(intVec, string);
void solvePuzzleMisplaced(intVec, string);
void solveEuclid(intVec, string);

int main() {
int pChoice = 0;
int aChoice = 0;
int userVal;
int idx = 0;
string heuristic;
vector<int> userInput;
intVec puzzle(3, vector<int>(3));

//------------Puzzle Choice------------
cout << "Welcome to XXX 8-Puzzle Solver." << endl << "Type '1' to use a default puzzle or type '2' to create your own." << endl;

while (pChoice !=  1 || pChoice != 2) {
    cin >> pChoice;
    if (pChoice == 1) {
        userInput = {1, 0, 3, 4, 2, 6, 7, 5, 8};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                puzzle[i][j] = userInput[idx];
                cout << puzzle[i][j];
                idx++;
            }
            cout << endl;
        }
        break;
    }

    else if (pChoice == 2) {
        cout << "Enter three numbers per row seperated by a space, using a '0' to represent the blank." << endl;
        for(int i = 0; i < 3; i++) {
            cout << "Enter numbers for row " << i + 1 << ": ";

            for(int j = 0; j < 3; j++) {
                cin >> userVal;
                userInput.push_back(userVal);
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                puzzle[i][j] = userInput[idx];
                cout << puzzle[i][j];
                idx++;
            }
            cout << endl;
        }
        break;
    }

    else {
        cout << "Invalid input. Please enter only '1' or '2'." << endl;
        cout << "Type '1' to use a default puzzle or type '2' to create your own." << endl;
        cin >> pChoice;
    }
}

//------------Algorithm Choice------------
cout << "Enter a number corresponding to your choice of algorithm: " << endl << "1) Uniform Cost Search" << endl << "2) A* with the Misplaced Tile heuristic" << endl << "3) A* with the Euclidean distance heuristic" << endl;

while (aChoice < 1 || aChoice > 3) {
    cin >> aChoice;
    if (aChoice == 1) {
        heuristic = "Uniform";
        solvePuzzle(puzzle, heuristic);
        break;
    }

    else if (aChoice == 2) {
        heuristic = "Misplaced";
        solvePuzzleMisplaced(puzzle, heuristic);
        break;
    }

     else if (aChoice == 3) {
         heuristic = "Euclidean";
         solveEuclid(puzzle, heuristic);
        break;
     }

    else {
        cout << "Invalid input. Please enter a number from 1-3." << endl;
        cout << "Enter a number corresponding to your choice of algorithm: " << endl << "1) Uniform Cost Search" << endl << "2) A* with the Misplaced Tile heuristic" << endl << "3) A* with the Euclidean distance heuristic" << endl;
        cin >> aChoice;
    }
}
    return 0;
}
//------------Uniform Cost Search------------
void solvePuzzle(intVec puzzle, string heuristic) {
    int expandedNodes;
    size_t maxQueueSize = 0;

    node currentNode(puzzle);
    expandedNodes = 0;

    traversedNodes.push_back(currentNode);
    searchQueue.push(currentNode);

    while (!searchQueue.empty()) {
        node *n = new node(searchQueue.top());

        if (goalState == searchQueue.top().puzzle) {
            printPuzzleNodes(searchQueue.top(), maxQueueSize, expandedNodes);
            break;
        } else {
            traversedNodes.push_back(searchQueue.top());
            if (maxQueueSize < searchQueue.size()) {
                maxQueueSize = searchQueue.size();
            }

            searchQueue.pop();

            expandedNodes++;
            node *n_up = new node(shiftUp(n->puzzle), n->costUniform + 1);
            node *n_down = new node(shiftDown(n->puzzle), n->costUniform + 1);
            node *n_left = new node(shiftLeft(n->puzzle), n->costUniform + 1);
            node *n_right = new node(shiftRight(n->puzzle), n->costUniform + 1);

            n_left->sumCost = n_left->costHeuristic + n_left->costUniform;
            n_right->sumCost = n_right->costHeuristic + n_right->costUniform;
            n_up->sumCost = n_up->costHeuristic + n_up->costUniform;
            n_down->sumCost = n_down->costHeuristic + n_down->costUniform;

            if (!previousNodes(n_right->puzzle, traversedNodes)) {
                n->c0 = n_right;
                n_right->p = n;
                searchQueue.push(*n_right);
            }

            if (!previousNodes(n_left->puzzle, traversedNodes)) {
                n->c1 = n_left;
                n_left->p = n;
                searchQueue.push(*n_left);
            }

            if (!previousNodes(n_up->puzzle, traversedNodes)) {
                n->c2 = n_up;
                n_up->p = n;
                searchQueue.push(*n_up);
            }

            if (!previousNodes(n_down->puzzle, traversedNodes)) {
                n->c3 = n_down;
                n_down->p = n;
                searchQueue.push(*n_down);
            }
        }
    }
}

// Helper function for misplaced tiles
int getMisplacedTiles(const intVec& puzzle) {
    int misplacedTiles = 0;
    int k = 1;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (puzzle[i][j] != k % 9){ // Checks if the tile is misplaced
                misplacedTiles++;
            }
            k++;
        }
    }
    return misplacedTiles;
}

//Misplaced tiles
void solvePuzzleMisplaced(intVec puzzle, string heuristic) {
    int expandedNodes;
    size_t maxQueueSize = 0;

    node currentNode(puzzle);
    currentNode.costMisplaced = getMisplacedTiles(puzzle); // initialize costMisplaced inside current node
    currentNode.sumCost = currentNode.costUniform + currentNode.costMisplaced; // initialize sumCost
    expandedNodes = 0;

    traversedNodes.push_back(currentNode);
    searchQueue.push(currentNode);

    while (!searchQueue.empty()){
        node *n = new node(searchQueue.top());

        if (goalState == searchQueue.top().puzzle){
            printPuzzleNodes(searchQueue.top(), maxQueueSize, expandedNodes);
            break;
        } else {
            traversedNodes.push_back(searchQueue.top());
            if (maxQueueSize < searchQueue.size()) {
                maxQueueSize = searchQueue.size();
            }

            searchQueue.pop();

            expandedNodes++;
            node *n_up = new node(shiftUp(n->puzzle), n->costUniform + n->costMisplaced + 1);
            node *n_down = new node(shiftDown(n->puzzle), n->costUniform + n->costMisplaced + 1);
            node *n_left = new node(shiftLeft(n->puzzle), n->costUniform + n->costMisplaced + 1);
            node *n_right = new node(shiftRight(n->puzzle), n->costUniform + n->costMisplaced + 1);

            n_left->costMisplaced = getMisplacedTiles(n_left->puzzle);
            n_right->costMisplaced = getMisplacedTiles(n_right->puzzle);
            n_up->costMisplaced = getMisplacedTiles(n_up->puzzle);
            n_down->costMisplaced = getMisplacedTiles(n_down->puzzle);

            n_left->sumCost = n_left->costHeuristic + n_left->costMisplaced;
            n_right->sumCost = n_right->costHeuristic + n_right->costMisplaced;
            n_up->sumCost = n_up->costHeuristic + n_up->costMisplaced;
            n_down->sumCost = n_down->costHeuristic + n_down->costMisplaced;

            if (!previousNodes(n_right->puzzle, traversedNodes)) {
                n->c0 = n_right;
                n_right->p = n;
                searchQueue.push(*n_right);
            }

            if (!previousNodes(n_left->puzzle, traversedNodes)) {
                n->c1 = n_left;
                n_left->p = n;
                searchQueue.push(*n_left);
            }

            if (!previousNodes(n_up->puzzle, traversedNodes)) {
                n->c2 = n_up;
                n_up->p = n;
                searchQueue.push(*n_up);
            }

            if (!previousNodes(n_down->puzzle, traversedNodes)) {
                n->c3 = n_down;
                n_down->p = n;
                searchQueue.push(*n_down);
            }
        }
    }
}

//Helper function for Euclidean distance
int euclidean_dist(intVec puzzle){
	int dist = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(puzzle[i][j] == 0){
				continue;
			}
			if(puzzle[i][j] != goalState[i][j]){
				int r = 0;
				int c = 0;

				for(int x = 0; x < 3; x++){
					for(int y = 0; y < 3; y++){
						if(goalState[x][y] == puzzle[i][j]){
							r = x;
							c = y;
						}
					}
				}
				r = pow(r - c,2);
				c = pow(i - j,2);
				while(r != 0 || c != 0){
					if(r < 0){
						dist++;
						r++;
        			}
					if(r > 0){
						dist++;
						r--;
					}
					if(c < 0){
					    dist++;
						c++;
					}
					if(c > 0){
						dist++;
						c--;
					}
				}
			}
		}
	}
	return dist;
}

//Euclidean Distance
void solveEuclid(intVec puzzle, string heuristic){
 int expandedNodes;
 size_t maxQueueSize = 0;

 node currentNode(puzzle);
 expandedNodes = 0;

 currentNode.sumCost = currentNode.costUniform + currentNode.euclideanDistance;
 
 traversedNodes.push_back(currentNode);
 searchQueue.push(currentNode); // search queue

 while(!searchQueue.empty()){
    node *n = new node(searchQueue.top());

    if (goalState == searchQueue.top().puzzle){
         printPuzzleNodes(searchQueue.top(), maxQueueSize, expandedNodes);
         break;
    } else { 
        traversedNodes.push_back(searchQueue.top());
        if (maxQueueSize < searchQueue.size()){
            maxQueueSize = searchQueue.size();
        }
    searchQueue.pop();

    expandedNodes++;
    node *n_up = new node(shiftUp(n->puzzle), n->costUniform + n->costHeuristic + 1);
    node *n_down = new node(shiftDown(n->puzzle), n->costUniform + n->costHeuristic + 1);
    node *n_left = new node(shiftLeft(n->puzzle), n->costUniform + n->costHeuristic + 1);
    node *n_right = new node(shiftRight(n->puzzle), n->costUniform + n->costHeuristic + 1);


    n_up->costHeuristic= euclidean_dist(n_up->puzzle);
    n_down->costHeuristic = euclidean_dist(n_down->puzzle);
    n_left->costHeuristic = euclidean_dist(n_left->puzzle);
    n_right->costHeuristic = euclidean_dist(n_right->puzzle);

    n_up->sumCost = n_up->costHeuristic + n_up->euclideanDistance;
    n_down->sumCost = n_down->costHeuristic + n_down->euclideanDistance;
    n_left->sumCost = n_left->costHeuristic + n_left->euclideanDistance;
    n_right->sumCost = n_right->costHeuristic + n_right->euclideanDistance;

    if(!previousNodes(n_up->puzzle, traversedNodes)){
        n->c0 = n_up;
        n_up->p = n;
        searchQueue.push(*n_up);
    }
    if(!previousNodes(n_down->puzzle, traversedNodes)){
        n->c1 = n_down;
        n_down->p = n;
        searchQueue.push(*n_down);
    }
    if(!previousNodes(n_right->puzzle, traversedNodes)){
        n->c2 = n_right;
        n_right->p = n;
        searchQueue.push(*n_right);
    }
    if(!previousNodes(n_left->puzzle, traversedNodes)){
        n->c3 = n_left;
        n_left->p = n;
        searchQueue.push(*n_left);
    }

   }
  }
}