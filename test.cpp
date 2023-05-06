#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include "Node.h"

using namespace std;

void printVec(vector <vector <int>> outputVec) //for testing purposes
{
    for(int a = 0; a < outputVec.size(); a++)
    {
        for(int b = 0; b < outputVec[0].size(); b++)
        {
            cout << outputVec[a][b] << " ";
        }
        cout << endl;
    }
}

int main() {
vector <vector <int>> userPuzzle;
vector <int> tempVec;
int tempVal;
int pChoice;
int aChoice;

//------------Puzzle Choice------------
cout << "Welcome to XXX 8-Puzzle Solver." << endl << "Type '1' to use a default puzzle or type '2' to create your own." << endl;
cin >> pChoice;

while (pChoice !=  1 || pChoice != 2) {
    if (pChoice == 1) {
        userPuzzle = {{1, 2, 0}, {4, 7, 6}, {5, 8, 3}};
        break;
    }

    else if (pChoice == 2) {
        cout << "Enter three numbers per row seperated by a space and using a '0' to represent the blank." << endl;
        for(int i = 0; i < 3; i++) {
            cout << "Enter numbers for row " << i + 1 << ": ";

            for(int j = 0; j < 3; j++) {
                cin >> tempVal;
                tempVec.push_back(tempVal);
            }
            userPuzzle.push_back(tempVec);
        }
        break;
    }

    else {
        cout << "Invalid input. Please enter only '1' or '2'." << endl;
        cout << "Type '1' to use a default puzzle or type '2' to create your own." << endl;
        cin >> pChoice;
    }
}

//Node(userPuzzle);
printVec(userPuzzle); //for testing purposes

//------------Algorithm Choice------------
cout << "Enter your choice of algorithm: " << endl << "1) Uniform Cost Search" << endl << "2) A* with the Misplaced Tile heuristic" << endl << "3) A* with the Euclidean distance heuristic" << endl;
cin >> aChoice;

while (aChoice < 1 || aChoice > 3) {
    if (aChoice == 1) {
        cout << "UCS"; //for testing purposes
        break;
    }

    else if (aChoice == 2) {
        cout << "A* mispaced"; //for testing purposes
        break;
    }

    else if (aChoice == 3) {
        cout << "A* euclid"; //for testing purposes
        break;
    }

    else {
        cout << "Invalid input. Please enter a number from 1-3." << endl;
        cout << "Enter your choice of algorithm: " << endl << "1) Uniform Cost Search" << endl << "2) A* with the Misplaced Tile heuristic" << endl << "3) A* with the Euclidean distance heuristic" << endl;
        cin >> aChoice;
    }
}
    return 0;
}

