#include <iostream>
#include <vector>
#include <stack>
#include <unistd.h>
#include <queue>

#include "Node.h"

typedef vector<vector<int>> intVec;

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
}

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

int main() {
    vector<int> userInput = {1, 0, 3, 4, 2, 6, 7, 5, 8};

    intVec puzzle(3, vector<int>(3));

    int idx = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            puzzle[i][j] = userInput[idx];
            cout << puzzle[i][j];
            idx++;
        }
        cout << endl;
    }

    int opt;
    cin >> opt;

    string heuristic = "Uniform";
    solvePuzzle(puzzle, heuristic);

    cout << endl;
    cout << "Program Ending" << endl;


// int pChoice;
// int aChoice;

// //------------Puzzle Choice------------
// cout << "Welcome to XXX 8-Puzzle Solver." << endl << "Type '1' to use a default puzzle or type '2' to create your own." << endl;
// cin >> pChoice;

// while (pChoice !=  1 || pChoice != 2) {
//     if (pChoice == 1) {
        
//         break;
//     }

//     else if (pChoice == 2) {
//         cout << "Enter three numbers per row seperated by a space and using a '0' to represent the blank." << endl;
//         for(int i = 0; i < 3; i++) {
//             cout << "Enter numbers for row " << i + 1 << ": ";

//             for(int j = 0; j < 3; j++) {
//             //     cin >> tempVal;
//             //     tempVec.push_back(tempVal);      replace
//             }
//             // userPuzzle.push_back(tempVec);
//         }
//         break;
//     }

//     else {
//         cout << "Invalid input. Please enter only '1' or '2'." << endl;
//         cout << "Type '1' to use a default puzzle or type '2' to create your own." << endl;
//         cin >> pChoice;
//     }
// }

// //------------Algorithm Choice------------
// cout << "Enter a number corresponding to your choice of algorithm: " << endl << "1) Uniform Cost Search" << endl << "2) A* with the Misplaced Tile heuristic" << endl << "3) A* with the Euclidean distance heuristic" << endl;
// cin >> aChoice;

// while (aChoice < 1 || aChoice > 3) {
//     if (aChoice == 1) {
//         solvePuzzle(puzzle, "Uniform");
//         break;
//     }

//     else if (aChoice == 2) {
//         solvePuzzle(puzzle, "Misplaced"); //temp
//         break;
//     }

//     else if (aChoice == 3) {
//         solvePuzzle(puzzle, "Euclidean"); //temp
//         break;
//     }

//     else {
//         cout << "Invalid input. Please enter a number from 1-3." << endl;
//         cout << "Enter a number corresponding to your choice of algorithm: " << endl << "1) Uniform Cost Search" << endl << "2) A* with the Misplaced Tile heuristic" << endl << "3) A* with the Euclidean distance heuristic" << endl;
//         cin >> aChoice;
//     }
// }
    return 0;
}

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

