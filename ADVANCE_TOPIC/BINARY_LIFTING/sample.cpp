/*

Binary lifting its help to upward in the tree very efficently 

direct long jump try suppose we reach kth node then jump direct long

always 2 ke power ma jump kare 
why 2 ke power ->  every number express power of 2

link read PDF -> https://github.com/MAZHARMIK/Interview_DS_Algo/blob/master/iPad%20PDF%20Notes/Binary%20Lifting%20Video%20-%201.pdf
*/

// code

#include <iostream>
#include <vector>
#include <climits>
#include <math.h>

using namespace std;

int main () {

    vector<int> parent{-1, 0, 0, 1, 1, 2, 2};
    int n = parent.size();

    int node = 4; // find node 4 ka kth ancestor
    int k = 5 ;

    int rows = n;
    int cols = log2(n)+1;

    vector<vector<int>> ancestorTable(rows, vector<int>(cols, -1));

    // fill base case ancestorTable

    for (int node=0; node<n; node++) {

        ancestorTable[node][0] = parent[node];
    }

    for (int j=1; j<cols; j++) {

        for (int node=0; node<rows; node++) {

            if (ancestorTable[node][j-1] != -1) {
                ancestorTable[node][j] = ancestorTable[ancestorTable[node][j-1]][j-1];
            }
        }
    }

    bool isFind = true;

    for (int j=0; j<cols; j++) {

        if (k & (1 << j)) { // jth bit set or not 
            node = ancestorTable[node][j];

            if (node == -1) {
                isFind = false;
                break;
            }
        }
    }

    if (isFind) {
        cout << "kth ancesto " << node;
    } else {
        cout << "Not find" << endl;
    }



    return 0;
}

