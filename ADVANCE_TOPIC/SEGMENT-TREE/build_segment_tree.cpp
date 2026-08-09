

#include <iostream>
#include <vector>

using namespace std;

/*

we visit every node 2 times so T.C O(2 * n) == > O(n)
and size of while tree 2*n
n = leaf node
n-1 = internal node
total = n + n-1 = 2n -1 approx 2n

*/
void buildSegmentTree(vector<int>& segmentTree, vector<int>& nums, int i, int l, int r) {

    if (l == r) {
        segmentTree[i] = nums[l]; // l == r this is my single element
    }

    int mid = (l + r) / 2;

    buildSegmentTree(segmentTree, nums, 2*i+1, l, mid);
    buildSegmentTree(segmentTree, nums, 2*i+2, mid+1, r);

    // leap of faith ke recurison mere kam ka dega mujhe bss current root node ke tension leni hai
    segmentTree[i] = segmentTree[2*i+1] + segmentTree[2*i+2]; // accoding to our need change the condition 
    // like we need to find minimum so add min similar add max and other need
}