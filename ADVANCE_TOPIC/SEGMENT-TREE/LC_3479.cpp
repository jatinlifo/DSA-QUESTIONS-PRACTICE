// You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.

// From left to right, place the fruits according to these rules:

// Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
// Each basket can hold only one type of fruit.
// If a fruit type cannot be placed in any basket, it remains unplaced.
// Return the number of fruit types that remain unplaced after all possible allocations are made.

 

// Example 1:

// Input: fruits = [4,2,5], baskets = [3,5,4]

// Output: 1

// Explanation:

// fruits[0] = 4 is placed in baskets[1] = 5.
// fruits[1] = 2 is placed in baskets[0] = 3.
// fruits[2] = 5 cannot be placed in baskets[2] = 4.
// Since one fruit type remains unplaced, we return 1.

// Example 2:

// Input: fruits = [3,6,1], baskets = [6,4,7]

// Output: 0

// Explanation:

// fruits[0] = 3 is placed in baskets[0] = 6.
// fruits[1] = 6 cannot be placed in baskets[1] = 4 (insufficient capacity) but can be placed in the next available basket, baskets[2] = 7.
// fruits[2] = 1 is placed in baskets[1] = 4.
// Since all fruits are successfully placed, we return 0.

 

// Constraints:

// n == fruits.length == baskets.length
// 1 <= n <= 105
// 1 <= fruits[i], baskets[i] <= 109

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    
    void buildSegmentTree(int i, int l, int r, vector<int>& segmentTree, vector<int>& baskets) {

        if (l == r) {
            segmentTree[i] = baskets[l];
            return;
        }

        int mid = l + (r - l) / 2;

        buildSegmentTree(2*i+1, l, mid, segmentTree, baskets);
        buildSegmentTree(2*i+2, mid+1, r, segmentTree, baskets);

        segmentTree[i] = max(segmentTree[2*i+1], segmentTree[2*i+2]);

        return;
    }

    bool query(int i, int l, int r, int f, vector<int>& segmentTree) {

        if (segmentTree[i] < f) {
            return false;
        }

        if (l == r) {
            segmentTree[i] = -1;
            return true;
        }

        bool placed = false;
        int mid = l + (r - l) / 2;

        if (segmentTree[2*i+1] >= f) {
            placed = query(2*i+1, l, mid, f, segmentTree);
        } else {
            placed = query(2*i+2, mid+1, r, f, segmentTree);
        }

        segmentTree[i] = max(segmentTree[2*i+1], segmentTree[2*i+2]);

        return placed;
    }
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        
        int n = baskets.size();

        vector<int> segmentTree(4*n);

        buildSegmentTree(0, 0, n-1, segmentTree, baskets);

        int ans = 0;

        for (int i = 0; i < n; i++) {

            if (!query(0, 0, n-1, fruits[i], segmentTree)) {
                ans++;
            }
        }

        return ans;
    }
};