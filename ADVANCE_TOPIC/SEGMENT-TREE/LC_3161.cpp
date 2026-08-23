// There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.

// You are given a 2D array queries, which contains two types of queries:

// For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
// For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
// Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.

 

// Example 1:

// Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]

// Output: [false,true,true]

// Explanation:



// For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.

// Example 2:

// Input: queries = [[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]

// Output: [true,true,false]

// Explanation:



// Place an obstacle at x = 7 for query 0. A block of size at most 7 can be placed before x = 7.
// Place an obstacle at x = 2 for query 2. Now, a block of size at most 5 can be placed before x = 7, and a block of size at most 2 before x = 2.
 

// Constraints:

// 1 <= queries.length <= 15 * 104
// 2 <= queries[i].length <= 3
// 1 <= queries[i][0] <= 2
// 1 <= x, sz <= min(5 * 104, 3 * queries.length)
// The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
// The input is generated such that there is at least one query of type


#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    
    void updateSegmentTree(int val, int idx, int i, int l, int r, vector<int>& segmentTree) {

        if (l == r) {
            segmentTree[i] = val;
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid) {
            updateSegmentTree(val, idx, 2*i+1, l, mid, segmentTree);
        } else {
            updateSegmentTree(val, idx, 2*i+2, mid+1, r, segmentTree);
        }

        segmentTree[i] = max(segmentTree[2*i+1], segmentTree[2*i+2]);

        return;
    }

    int querySegmentTree(int st, int end, int i, int l, int r, vector<int>& segmentTree) {

        if (l > end || st > r) {
            return 0;
        }

        if (l >= st && r <= end) {
            return segmentTree[i];
        }

        int mid = l + (r - l) / 2;
        int left = querySegmentTree(st, end, 2*i+1, l, mid, segmentTree);
        int right = querySegmentTree(st, end, 2*i+2, mid+1, r, segmentTree);

        return max(left, right);
    }
    vector<bool> getResults(vector<vector<int>>& queries) {
        
        vector<bool> ans;
        set<int> set;
        set.insert(0);

        int n = 50000;
        vector<int> segmentTree(4*n);

        for (auto& q : queries) {

            if (q[0] == 1) {
                int x = q[1];

                auto it = set.upper_bound(x);
                auto nxt = (it != set.end()) ? *it : -1;
                int pre = *prev(it);

                updateSegmentTree(x - pre, x, 0, 0, n-1, segmentTree);

                if (nxt != -1) {
                    updateSegmentTree(nxt - x, nxt, 0, 0, n-1, segmentTree);
                }
                set.insert(x);
            } else {
                int x = q[1];
                int sz = q[2];
                // int prev = 0;
                // bool flag = false;

                // for (auto& curr : set) {

                //     if (curr > x) break;
                //     if (curr - prev >= sz) {
                //         flag = true;
                //         break;
                //     }
                //     prev = curr;
                // }

                auto it = set.upper_bound(x);
                int pre = *prev(it);

                int maxGap = querySegmentTree(0, pre, 0, 0, n-1, segmentTree);
                int best = max(maxGap, x - pre);

                ans.push_back(best >= sz);
            }
        }

        return ans;
    }
};