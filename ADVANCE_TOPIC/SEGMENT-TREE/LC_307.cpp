// Given an integer array nums, handle multiple queries of the following types:

// Update the value of an element in nums.
// Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
// Implement the NumArray class:

// NumArray(int[] nums) Initializes the object with the integer array nums.
// void update(int index, int val) Updates the value of nums[index] to be val.
// int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 

// Example 1:

// Input
// ["NumArray", "sumRange", "update", "sumRange"]
// [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
// Output
// [null, 9, null, 8]

// Explanation
// NumArray numArray = new NumArray([1, 3, 5]);
// numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
// numArray.update(1, 2);   // nums = [1, 2, 5]
// numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8
 

// Constraints:

// 1 <= nums.length <= 3 * 104
// -100 <= nums[i] <= 100
// 0 <= index < nums.length
// -100 <= val <= 100
// 0 <= left <= right < nums.length
// At most 3 * 104 calls will be made to update and sumRange.


#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
public:

    vector<int> tree;
    int n;

    SegmentTree(vector<int>& nums) {

        n = nums.size();
        tree.resize(4*n);

        build(0, 0, n-1, nums);
    }

    void build(int i, int l, int r, vector<int>& nums) {

        if (l == r) {
            tree[i] = nums[l];
            return;
        }

        int mid = l + (r - l) / 2;

        build(2*i+1, l, mid, nums);
        build(2*i+2, mid+1, r, nums);

        tree[i] = tree[2*i+1] + tree[2*i+2];
    }

    void update(int idx, int val) {

        updateTree(idx, val, 0, 0, n-1);
    }

    void updateTree(int idx, int val, int i, int l, int r) {

        if (l == r) {
            tree[i] = val;
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid) {
            updateTree(idx, val, 2*i+1, l, mid);
        } else {
            updateTree(idx, val, 2*i+2, mid+1, r);
        }

        tree[i] = tree[2*i+1] + tree[2*i+2];
    }

    int query(int left, int right) {

        return queryTree(left, right, 0, 0, n-1);
    }

    int queryTree(int st, int end, int i, int l, int r) {

        if (l > end || st > r) {
            return 0; // totally out of bound
        }

        if (l >= st && r <= end) { // completely 
            return tree[i];
        }

        int mid = l + (r - l) / 2;

        int left = queryTree(st, end, 2*i+1, l, mid); // some part get left side
        int right = queryTree(st, end, 2*i+2, mid+1, r); // some part get right side

        return left + right;
    }
};

class NumArray {
public:
    
    SegmentTree* segTree;

    NumArray(vector<int>& nums) {
        segTree = new SegmentTree(nums); // call constructor
    }
    
    void update(int index, int val) {
        
        segTree->update(index, val);
    }
    
    int sumRange(int left, int right) {

        return segTree->query(left, right);
    }
};

int main () {

    vector<int> nums = {1, 2, 3, 4, 5};

    NumArray obj(nums);

    cout << "SUM" <<"  : " << obj.sumRange(0, 4) << endl;

    obj.update(2, 8);

    cout << "SUM" << "  : " << obj.sumRange(2, 2) << endl;

    cout << "SUM" << " : " << obj.sumRange(2, 5) << endl;

    return 0;
}

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */