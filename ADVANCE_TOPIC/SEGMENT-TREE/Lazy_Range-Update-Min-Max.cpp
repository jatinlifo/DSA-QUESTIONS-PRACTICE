
#include <iostream>
#include <vector>

using namespace std;

void buildSegmentTree(int i, int l, int r, vector<int>& segmentTree, vector<int>& nums) {

    if (l == r) {
        segmentTree[i] = nums[l];
        return;
    }

    int mid = l + (r - l) / 2;

    buildSegmentTree(2*i+1, l, mid, segmentTree, nums);
    buildSegmentTree(2*i+2, mid+1, r, segmentTree, nums);

    segmentTree[i] = min(segmentTree[2*i+1], segmentTree[2*i+2]);

    return;
}


void updateSegmentTree(int val, int st, int end, int i, int l, int r, vector<int>& segmentTree, vector<int>& lazy) {

    if (st > r || end < l) {
        return;
    }

    if (l >= st && r <= end) {
        lazy[i] += val;

        if (lazy[i] != 0) {
            segmentTree[i] += val;

            if (l != r) {
                lazy[2*i+1] += lazy[i];
                lazy[2*i+2] += lazy[i];
            }
        }

        lazy[i] = 0;

        return;
    }

    int mid = l + (r - l) / 2;

    updateSegmentTree(val, st, end, 2*i+1, l, mid, segmentTree, lazy);
    updateSegmentTree(val, st, end, 2*i+2, mid+1, r, segmentTree, lazy);

    segmentTree[i] = min(segmentTree[2*i+1], segmentTree[2*i+2]);

    return;
}