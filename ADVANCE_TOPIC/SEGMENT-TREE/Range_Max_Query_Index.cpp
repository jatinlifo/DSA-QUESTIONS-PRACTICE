
#include <iostream>
#include <vector>


using namespace std;


void buildSegmentTree(int i, int l, int r, vector<int>& nums, vector<int>& segmentTree) {

    if (l == r) {
        segmentTree[i] = l;
    }

    int mid = l + (r - l) / 2;
    buildSegmentTree(2*i+1, l, mid, nums, segmentTree);
    buildSegmentTree(2*i+2, mid+1, r, nums, segmentTree);

    int left_idx = segmentTree[2*i+1];
    int right_idx = segmentTree[2*i+2];

    if (nums[left_idx] >= nums[right_idx]) {
        segmentTree[i] = left_idx;
    } else {
        segmentTree[i] = right_idx;
    }
}

int query(int st, int end, int i, int l, int r, vector<int>& nums, vector<int>& segmentTree) {

    if (st > r || l > end) {
        return -1;
    }

    if (l >= st && r <= end) {
        return segmentTree[i];
    }

    int mid = l + (r - l) / 2;

    int left_idx = query(st, end, 2*i+1, l, mid, nums, segmentTree);
    int right_idx = query(st, end, 2*i+2, mid+1, r, nums, segmentTree);

    if (left_idx == -1) return right_idx;
    else if (right_idx == -1) left_idx;
    else if (nums[left_idx] >= nums[right_idx]) return right_idx;
    return left_idx;
}

int rangeMinIndex(int st, int end, vector<int>& nums) {

    // build range max segment Tree
    int n = nums.size();
    vector<int> segmentTree(4*n);

  
    buildSegmentTree(0, 0, n-1, nums, segmentTree);
    return query(st, end, 0, 0, 0, nums, segmentTree);

}
