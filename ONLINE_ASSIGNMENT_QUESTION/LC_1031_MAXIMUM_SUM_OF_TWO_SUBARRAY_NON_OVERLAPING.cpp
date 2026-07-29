// Given an integer array nums and two integers firstLen and secondLen, return the maximum sum of elements in two non-overlapping subarrays with lengths firstLen and secondLen.

// The array with length firstLen could occur before or after the array with length secondLen, but they have to be non-overlapping.

// A subarray is a contiguous part of an array.

// Example 1:

// Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
// Output: 20
// Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
// Example 2:

// Input: nums = [3,8,1,3,2,1,8,9,0], firstLen = 3, secondLen = 2
// Output: 29
// Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.
// Example 3:

// Input: nums = [2,1,5,6,0,9,5,0,3,8], firstLen = 4, secondLen = 3
// Output: 31
// Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [0,3,8] with length 3.

// Constraints:

// 1 <= firstLen, secondLen <= 1000
// 2 <= firstLen + secondLen <= 1000
// firstLen + secondLen <= nums.length <= 1000
// 0 <= nums[i] <= 1000

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    // approach 1 using prefix sum
    int fun(vector<int> &nums, int L, int M)
    {

        int n = nums.size();

        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + nums[i];

        int ans = 0;

        int maxL = prefix[L] - prefix[0];

        for (int i = L + M; i <= n; i++)
        {

            maxL = max(maxL, prefix[i - M] - prefix[i - M - L]);

            int currM = prefix[i] - prefix[i - M];

            ans = max(ans, maxL + currM);
        }

        return ans;
    }

    // approach2 using sliding window concept
    int fun(vector<int> &nums, int L, int M)
    {

        int n = nums.size();
        int lSum = 0;
        int mSum = 0;

        for (int i = 0; i < L + M; i++)
        {

            if (L > i)
            {
                lSum += nums[i];
            }
            else
            {
                mSum += nums[i];
            }
        }

        int maxLeftSum = lSum;
        int ans = lSum + mSum;

        for (int i = L + M; i < n; i++)
        {

            lSum += nums[i - M] - nums[i - M - L];
            mSum += nums[i] - nums[i - M];

            maxLeftSum = max(maxLeftSum, lSum);

            ans = max(ans, mSum + maxLeftSum);
        }

        return ans;
    }
    int maxSumTwoNoOverlap(vector<int> &nums, int firstLen, int secondLen)
    {

        return max(fun(nums, firstLen, secondLen), fun(nums, secondLen, firstLen));
    }
};