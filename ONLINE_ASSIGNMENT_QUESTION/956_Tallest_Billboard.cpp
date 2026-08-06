// You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.

// You are given a collection of rods that can be welded together. For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.

// Return the largest possible height of your billboard installation. If you cannot support the billboard, return 0.

// Example 1:

// Input: rods = [1,2,3,6]
// Output: 6
// Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
// Example 2:

// Input: rods = [1,2,3,4,5,6]
// Output: 10
// Explanation: We have two disjoint subsets {2,3,5} and {4,6}, which have the same sum = 10.
// Example 3:

// Input: rods = [1,2]
// Output: 0
// Explanation: The billboard cannot be supported, so we return 0.
 
// Constraints:

// 1 <= rods.length <= 20
// 1 <= rods[i] <= 1000
// sum(rods[i]) <= 5000

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

class Solution {
public:
    
    int dp[21][10002];
    // difference ka accordint sum -ve ho sakta hai toh hum ek offset bana lenga 5000 number ka jis always positive number sa compare kar paye

    int offSet = 5000;
    int solve(int i, int diff, vector<int>& rods) {

        if (i >= rods.size()) {
            if (diff == 0) {
                return 0;
            }
            return INT_MIN;
        }

        if (dp[i][diff+offSet] != -1) {
            return dp[i][diff+offSet];
        }

        int skip = solve(i+1, diff, rods);

        int left_rods = rods[i] + solve(i+1, diff + rods[i], rods);
        int right_rods = rods[i] + solve(i+1, diff - rods[i], rods);

        return dp[i][diff+offSet] = max({skip, left_rods, right_rods});
    }

    int tallestBillboard(vector<int>& rods) {
        
        /*
        first approach is take and skip 
        if skip not add
        add length 1 or add length 2 
        return max(those)

        second approach is also take and skip but tack only difference
        means l1 == l2 so, diff = 0 always zero

        suppose
        l1 - l2 = diff
        (l1 + x) - l2 = diff 
         and similer
         l1 - (l2 + x) = diff reduce 3d to 2d

         offset helps to overflow index access time like difference is -ve so that time use offSet
         size of dp 10000 
         minimum diff can be = -5000
         maximum diff can be =  5000 
         only so sometimes difference is -ve to easy offSet value fix = 5000
         like suppose diff = -5000 so now diff + offSet = -5000 + 5000 = 0
         always safe access any time 
        */

        memset(dp, -1, sizeof(dp));
        return solve(0, 0, rods) / 2;
    }
};