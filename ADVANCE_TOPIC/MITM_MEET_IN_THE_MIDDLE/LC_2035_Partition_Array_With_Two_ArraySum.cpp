// 2035. Partition Array Into Two Arrays to Minimize Sum Difference
// Solved
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.

// Return the minimum possible absolute difference.

// Example 1:

// example-1
// Input: nums = [3,9,7,3]
// Output: 2
// Explanation: One optimal partition is: [3,9] and [7,3].
// The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
// Example 2:

// Input: nums = [-36,36]
// Output: 72
// Explanation: One optimal partition is: [-36] and [36].
// The absolute difference between the sums of the arrays is abs((-36) - (36)) = 72.
// Example 3:

// example-3
// Input: nums = [2,-1,0,4,-2,-9]
// Output: 0
// Explanation: One optimal partition is: [2,4,-9] and [-1,0,-2].
// The absolute difference between the sums of the arrays is abs((2 + 4 + -9) - (-1 + 0 + -2)) = 0.
 

// Constraints:

// 1 <= n <= 15
// nums.length == 2 * n
// -107 <= nums[i] <= 107

// direct apply Meet in the middle 

/*

  find = abs(sum1 - sum2) where  sum1 = left part n / 2 element sum , sum2 = right part n/2 element sum
  Called totalSum = S
  so,
  S = s1 + s2 , where s1 = sum1 , s2 = sum2 
  find s2 value
  s2 = S - s1 ............(1) Eqn(1)
  given -> abs(s1 - s2) ........(2) Eqn(2)
  put the value s2 in eqn(1)

  abs(s1 - S + s1)
  abs(2s1 - S) so now find only this

  2 is constant also S given so find only s1 sum now apply recursion , dp all TLE 
  then, apply MITM

  given s1 find all subset sum 

  so divide into two part leftPart or rightPart 
  means leftSum , RightSum so,
  s1 = leftSum + RightSum

  this sum find using mitm technique

  so, abs(2 * (leftSum + rightSum) - S)

  we were build both array leftSubSum , rightSubSum now find minimum difference
  
  so reduce the formula

  = 2*(leftSum + rightSum) = S
  = rightSum  = S/2 - leftSum
  = rightSum = (S - 2*leftSum) / 2
  then, 
  sort the rightSum array and find mininum value
  now find rightSum and leftSum then put main formula 

  abs(2 * (leftSum + rightSum) - S) 

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // sorting
#include <numeric> // accumulate function
#include <climits> // INT_MIN or INT_MAX

using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        
        int N = nums.size(); // 2 * N
        int n = N / 2;

        int n1 = n; // left part
        int n2 = n; // right part

        unordered_map<int, vector<int>> leftSum;
        unordered_map<int, vector<int>> rightSum;

        for (int mask = 0; mask < (1 << n1); mask++) {

            int sum = 0;
            int count = 0;

            for (int i = 0; i < n1; i++) {

                if (mask & (1 << i)) {// ith bit set then add this element my subset
                    sum += nums[i];
                    count++;
                }
            }

            leftSum[count].push_back(sum);
        }

        for (int mask = 0; mask < (1 << n2); mask++) {

            int sum = 0;
            int count = 0;

            for (int i = 0; i < n2; i++) {

                if (mask & (1 << i)) {
                    sum += nums[n1+i]; // access right array element
                    count++;
                }
            }

            rightSum[count].push_back(sum);
        }

        // now sort the all subset for rightSum

        for (int count = 0; count <= n2; count++) {
            sort(rightSum[count].begin(), rightSum[count].end());
        }

        int S = accumulate(begin(nums), end(nums), 0);
        int ans = INT_MAX;

        for (int k=0; k<=n1; k++) { // traversh every size of  leftSubset sum

            int m = n1 - k;

            for (int leftSubSum : leftSum[k]) {

                int need = (S - 2*leftSubSum) / 2;

                int low = lower_bound(rightSum[m].begin(), rightSum[m].end(), need) - rightSum[m].begin();

                if (low < rightSum[m].size()) {
                    int rightSubSum = rightSum[m][low];

                    ans = min(ans, abs(2*(leftSubSum + rightSubSum) - S));
                }

                if (low - 1 >= 0) {
                    int rightSubSum = rightSum[m][low-1];

                    ans = min(ans, abs(2*(leftSubSum + rightSubSum) - S));
                }
            }
        }

        return ans;
    }
};