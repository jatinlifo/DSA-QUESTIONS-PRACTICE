// Question link: https://leetcode.com/problems/closest-subsequence-sum/description/

// You are given an integer array nums and an integer goal.

// You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).

// Return the minimum possible value of abs(sum - goal).

// Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.

 

// Example 1:

// Input: nums = [5,-7,3,5], goal = 6
// Output: 0
// Explanation: Choose the whole array as a subsequence, with a sum of 6.
// This is equal to the goal, so the absolute difference is 0.
// Example 2:

// Input: nums = [7,-9,15,-2], goal = -5
// Output: 1
// Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
// The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the minimum.
// Example 3:

// Input: nums = [1,2,3], goal = -7
// Output: 7
 

// Constraints:

// 1 <= nums.length <= 40
// -107 <= nums[i] <= 107
// -109 <= goal <= 109

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        
        // apply MITM -> (MEET IN THE MIDDLE)
        int n = nums.size();

        int n1 = n / 2;
        int n2 = n - n1;

        vector<int> sumsA(1 << n1);
        vector<int> sumsB(1 << n2);

        for (int mask = 0; mask < (1 << n1); mask++) {

            int sum = 0;

            for (int i=0; i<n1; i++) {

                if (mask & (1 << i)) {
                    sum += nums[i];
                }
            }

            sumsA[mask] = sum;
        }

        for (int mask = 0; mask < (1 << n2); mask++) {

            int sum = 0;

            for (int i=0; i<n2; i++) {

                if (mask & (1 << i)) {
                    sum += nums[n1+i];
                }
            }

            sumsB[mask] = sum;
        }

        int ans = INT_MAX;

        sort(begin(sumsB), end(sumsB));

        for (int sum1 : sumsA) {

            int need = goal - sum1;

            int low = lower_bound(begin(sumsB), end(sumsB), need) - begin(sumsB);

            if (low < sumsB.size()) {
                int sum2 = sumsB[low];
                int total = sum1 + sum2;

                ans = min(ans, abs(total - goal));
            }

            if (low > 0) {
                int sum2 = sumsB[low-1];
                int total = sum1 + sum2;

                ans = min(ans, abs(total - goal));
            }
        }

        return ans;
    }
};

int main () {

    int n;
    int goal;

    cin >> n >> goal ;

    vector<int> nums(n);

    for (int i=0; i<n; i++) {
        cin >> nums[i];
    }

    Solution obj;

    int ans = obj.minAbsDifference(nums, goal);

    cout << "Minimum Difference is : " << ans << endl;

    return 0;
}