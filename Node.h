#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> intVec;

//------------Node class------------
struct node {
    int costUniform = 0;
    int costHeuristic = 0;
    int sumCost = 0;
    int costMisplaced = 0;
    int euclideanDistance = 0;

    node *c0 = NULL;
    node *c1 = NULL;
    node *c2 = NULL;
    node *c3 = NULL;
    node *p = NULL;

    intVec puzzle;

    node(intVec vec) : costUniform(0), costHeuristic(0), puzzle(vec) {}

    node(const node &vec)
        : puzzle(vec.puzzle), costHeuristic(vec.costHeuristic),
          costUniform(vec.costUniform), sumCost(vec.sumCost), c0(vec.c0),
          c1(vec.c1), c2(vec.c2), c3(vec.c3), p(vec.p) {}

    void operator=(const node &vec) {
        puzzle = vec.puzzle;
        costHeuristic = vec.costHeuristic;
        costUniform = vec.costUniform;
        sumCost = vec.sumCost;
        c0 = vec.c0;
        c1 = vec.c1;
        c2 = vec.c2;
        c3 = vec.c3;
        p = vec.p;
    }

    node(intVec vec, int uniform_cost)
        : puzzle(vec), costHeuristic(0), costUniform(uniform_cost) {}

    void printPuzzle() {
        for (int j = 0; j < 3; j++) {
            for (int z = 0; z < 3; z++) {
                cout << puzzle[j][z];
            }
            cout << endl;
        }
    }
};

struct comparison {
    bool operator()(const node &nleft, const node &nright) {
        return nleft.sumCost > nright.sumCost;
    }
};

#endif /* NODE_H_ */
