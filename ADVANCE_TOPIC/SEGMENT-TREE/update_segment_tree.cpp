#include <iostream>
#include <vector>

using namespace std;

/* 

whole tree height is log(n) 

and we only visit height of tree not visit all nodes we visit (2 * log(n)) = > log(n)

*/
void updateSegmentTreee(vector<int>& segmentTree, int idx, int val, int i, int l, int r) {

    if (l == r) {
        segmentTree[i] = val;
        return;
    }

    int mid = (l + r) / 2;

    if (idx <= mid) {
        updateSegmentTreee(segmentTree, idx, val, 2*i+1, l, mid);
    } else {
        updateSegmentTreee(segmentTree, idx, val, 2*i+2, mid+1, r);
    }

    // leap of faith worry only current root node

    segmentTree[i] = segmentTree[2*i+1] + segmentTree[2*i+2];
}