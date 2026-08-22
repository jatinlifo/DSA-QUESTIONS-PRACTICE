// You are given an integer array nums.

// A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of distinct odd numbers.

// Return the length of the longest balanced subarray.

 

// Example 1:

// Input: nums = [2,5,4,3]

// Output: 4

// Explanation:

// The longest balanced subarray is [2, 5, 4, 3].
// It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3]. Thus, the answer is 4.
// Example 2:

// Input: nums = [3,2,2,5,4]

// Output: 5

// Explanation:

// The longest balanced subarray is [3, 2, 2, 5, 4].
// It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5]. Thus, the answer is 5.
// Example 3:

// Input: nums = [1,2,3,2]

// Output: 3

// Explanation:

// The longest balanced subarray is [2, 3, 2].
// It has 1 distinct even number [2] and 1 distinct odd number [3]. Thus, the answer is 3.
 

// Constraints:

// 1 <= nums.length <= 105
// 1 <= nums[i] <= 105

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:

    void propagate(int i, int l, int r, vector<int>& minSegmentTree, vector<int>& maxSegmentTree, vector<int>& lazyTree) {

        if (lazyTree[i] != 0) {

            minSegmentTree[i] += lazyTree[i];
            maxSegmentTree[i] += lazyTree[i];

            if (l != r) {
                lazyTree[2*i+1] += lazyTree[i];
                lazyTree[2*i+2] += lazyTree[i];
            }

            lazyTree[i] = 0;
        }

        return;
    }
    void update(int st, int end, int val, int i, int l, int r, vector<int>& minSegmentTree, vector<int>& maxSegmentTree, vector<int>& lazyTree) {

        propagate(i, l, r, minSegmentTree, maxSegmentTree, lazyTree);
        if (end < l || r < st) {
            return;
        }

        if (l >= st && r <= end) {
            lazyTree[i] += val;

            propagate(i, l, r, minSegmentTree, maxSegmentTree, lazyTree);

            return;
        }

        int mid = l + (r - l) / 2;

        update(st, end, val, 2*i+1, l, mid, minSegmentTree, maxSegmentTree, lazyTree);
        update(st, end, val, 2*i+2, mid+1, r, minSegmentTree, maxSegmentTree, lazyTree);

        minSegmentTree[i] = min(minSegmentTree[2*i+1], minSegmentTree[2*i+2]);
        maxSegmentTree[i] = max(maxSegmentTree[2*i+1], maxSegmentTree[2*i+2]);

        return;
    }

    int findLeftMostZero(int i, int l, int r, vector<int>& minSegmentTree, vector<int>& maxSegmentTree, vector<int>& lazyTree) {

        propagate(i, l, r, minSegmentTree, maxSegmentTree, lazyTree);

        if (minSegmentTree[i] > 0 || maxSegmentTree[i] < 0) {
            return -1;
        }

        if (l == r) {
            return l;
        }

        int mid = l + (r - l) / 2;

        int left = findLeftMostZero(2*i+1, l, mid, minSegmentTree, maxSegmentTree, lazyTree);

        if (left != -1) {
            return left;
        }

        return findLeftMostZero(2*i+2, mid+1, r, minSegmentTree, maxSegmentTree, lazyTree);
    }

    int longestBalanced(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> prefix(n, 0);// treat odd -1, or even +1
        vector<int> minSegmentTree(4*n);
        vector<int> maxSegmentTree(4*n);
        vector<int> lazyTree(4*n);
        unordered_map<int, int> map;
        int maxL = 0;

        for (int r = 0; r < n; r++) {

            int val = (nums[r] % 2 == 0) ? 1 : -1;

            int prev = -1;

            if (map.count(nums[r])) {
                prev = map[nums[r]];
            }

            // this is update l to prev we can apply segment tree
            // if (prev != -1) {
            //     for (int l = 0; l <= prev; l++) {
            //         prefix[l] -= val;
            //     }

            // }
            if (prev != -1) {
                update(0, prev, -val, 0, 0, n-1, minSegmentTree, maxSegmentTree, lazyTree);
            }

            //also add l to r val so, here we can apply segment tree
            // for (int l = 0; l <= r; l++) {
            //     prefix[l] += val;
            // }

            update(0, r, val, 0, 0, n-1, minSegmentTree, maxSegmentTree, lazyTree);


            // every time find left most l where prefix[l] == 0 so we can apply segment tree using min tree or max tree
            // for (int l = 0; l <= r; l++) {

            //     if (prefix[l] == 0) {
            //         maxL = max(maxL, r - l + 1);
            //         break;
            //     }
            // }

            int l = findLeftMostZero(0, 0, n-1, minSegmentTree, maxSegmentTree, lazyTree);

            if (l != -1) {
                maxL = max(maxL, r - l + 1);
            }

            map[nums[r]] = r;
        }

        return maxL;
    }
};