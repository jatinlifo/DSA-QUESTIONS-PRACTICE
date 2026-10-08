// Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.

// Return the number of nice sub-arrays.

 

// Example 1:

// Input: nums = [1,1,2,1,1], k = 3
// Output: 2
// Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
// Example 2:

// Input: nums = [2,4,6], k = 1
// Output: 0
// Explanation: There are no odd numbers in the array.
// Example 3:

// Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
// Output: 16

// Approach 1 T.C O(n) , S.C O(n)

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        
        int n = nums.size();
        unordered_map<int, int> map;
        map[0] = 1;
        int count = 0;

        int ans = 0;

        for (int i = 0; i < n; i++) {

            if (nums[i] % 2 == 1) {
                count++;
            }

            if (map.count(count - k)) {
                ans += map[count - k];
            }

            map[count]++;
        }

        return ans;

        int n = nums.size();
        int i = 0;
        int ans = 0;
        int oddCount = 0;
        int prevAns = 0;

        for (int j = 0; j < n; j++) {

            if (nums[j] % 2 == 1) {
                oddCount++;
                prevAns = 0;
            }

            while (i <= j && oddCount == k) {
                oddCount -= (nums[i] % 2);
                prevAns++;
                i++;
            }

            ans += prevAns;

        }

        return ans;
    }
};