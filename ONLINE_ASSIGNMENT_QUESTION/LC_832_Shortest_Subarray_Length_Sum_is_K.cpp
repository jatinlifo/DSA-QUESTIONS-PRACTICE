// Given an integer array nums and an integer k, return the length of the shortest non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.

// A subarray is a contiguous part of an array.

 

// Example 1:

// Input: nums = [1], k = 1
// Output: 1
// Example 2:

// Input: nums = [1,2], k = 4
// Output: -1
// Example 3:

// Input: nums = [2,-1,2], k = 3
// Output: 3
 

// Constraints:

// 1 <= nums.length <= 105
// -105 <= nums[i] <= 105
// 1 <= k <= 109

// T.C  O(n) , S.C O(N)

#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        
        int n = nums.size();
        vector<int> prefixSum(n, 0);
        deque<int> deq; 
        int ans = INT_MAX;

        for (int j = 0; j < n; j++) {

            if (j == 0) {
                prefixSum[0] = nums[0];
            } else {
                prefixSum[j] = nums[j] + prefixSum[j-1];
            }

            if (prefixSum[j] >= k) {
                ans = min(ans, j+1); // if curr sum is >= store length
            }

            while (!deq.empty() && prefixSum[j] - prefixSum[deq.front()] >= k) { // if i have right sum remove left sum and still >= so find minimum length basically maintan increasing sequence like 1 2, 3, 4, 5 ....etc
                ans = min(ans, j - deq.front());
                deq.pop_front();
            }

            while (!deq.empty() && prefixSum[j] <= prefixSum[deq.back()]) { // if current sum is minimum of previous sum so remove that bcz this sum add now increase my length so in future maximum sum mil sakta hai abhi sum minimum ho gaye like 1, 5, 8, 2, 15, 30 so 1, 5, 8 ko hum remove kar denga jis sa future ma minimum length and maxium sum mil saki in future huma or minimum sum milta raha toh upar prefixSum aapna ap compare karta rahega and r to l tail tak ka sum bhi compare hota rahega
                deq.pop_back();
            }

            deq.push_back(j);
        }

        return (ans == INT_MAX) ? -1 : ans;
    }
};