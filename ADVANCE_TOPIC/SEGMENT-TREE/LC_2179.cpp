// You are given two 0-indexed arrays nums1 and nums2 of length n, both of which are permutations of [0, 1, ..., n - 1].

// A good triplet is a set of 3 distinct values which are present in increasing order by position both in nums1 and nums2. In other words, if we consider pos1v as the index of the value v in nums1 and pos2v as the index of the value v in nums2, then a good triplet will be a set (x, y, z) where 0 <= x, y, z <= n - 1, such that pos1x < pos1y < pos1z and pos2x < pos2y < pos2z.

// Return the total number of good triplets.

 

// Example 1:

// Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
// Output: 1
// Explanation: 
// There are 4 triplets (x,y,z) such that pos1x < pos1y < pos1z. They are (2,0,1), (2,0,3), (2,1,3), and (0,1,3). 
// Out of those triplets, only the triplet (0,1,3) satisfies pos2x < pos2y < pos2z. Hence, there is only 1 good triplet.
// Example 2:

// Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
// Output: 4
// Explanation: The 4 good triplets are (4,0,3), (4,0,2), (4,1,3), and (4,1,2).
 

// Constraints:

// n == nums1.length == nums2.length
// 3 <= n <= 105
// 0 <= nums1[i], nums2[i] <= n - 1
// nums1 and nums2 are permutations of [0, 1, ..., n - 1].

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    
    void updateSegmentTree(int i, int l, int r, int idx, vector<long long>& segmentTree) {

        if (l == r) {
            segmentTree[i] = 1;
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid) {
            updateSegmentTree(2*i+1, l, mid, idx, segmentTree);
        } else {
            updateSegmentTree(2*i+2, mid+1, r, idx, segmentTree);
        }

        segmentTree[i] = segmentTree[2*i+1] + segmentTree[2*i+2];

        return;
    }

    long long querySegmentTree(int st, int end, int i, int l, int r, vector<long long>& segmentTree) {

        if (st > r || l > end) {
            return 0;
        }

        if (l >= st && r <= end) {
            return segmentTree[i];
        }

        int mid = l + (r - l) / 2;

        long long left = querySegmentTree(st, end, 2*i+1, l, mid, segmentTree);
        long long right = querySegmentTree(st, end, 2*i+2, mid+1, r, segmentTree);

        return left + right;
    }

    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        
        long long ans = 0;
        int n = nums1.size();

        unordered_map<int, int> map;

        for (int i = 0; i < n; i++) {
            map[nums2[i]] = i;
        }

        vector<long long> segmentTree(4*n);
        updateSegmentTree(0, 0, n-1, map[nums1[0]], segmentTree);

        for (int i = 1; i < n; i++) {

            int idx = map[nums1[i]];

            long long leftCommonCount = querySegmentTree(0, idx, 0, 0, n-1, segmentTree);
            long long leftNotCommonCount = i - leftCommonCount;
            long long afterIdxNum2Count = (n - 1) - idx;
            long long rightCommonCount = afterIdxNum2Count - leftNotCommonCount;

            long long pairs = rightCommonCount * leftCommonCount;

            ans += pairs;

            updateSegmentTree(0, 0, n-1, idx, segmentTree);
        }

        return ans;
    }
};