// You are given an integer array nums.

// You should move each element of nums into one of the two arrays A and B such that A and B are non-empty, and average(A) == average(B).

// Return true if it is possible to achieve that and false otherwise.

// Note that for an array arr, average(arr) is the sum of all the elements of arr over the length of arr.

 

// Example 1:

// Input: nums = [1,2,3,4,5,6,7,8]
// Output: true
// Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have an average of 4.5.
// Example 2:

// Input: nums = [3,1]
// Output: false
 

// Constraints:

// 1 <= nums.length <= 30
// 0 <= nums[i] <= 104

#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    
    bool binarySearch(vector<int>& arr, int target) { // O(log(n2))
 
        int low = 0;
        int high = arr.size()-1;

        while (low <= high) {

            int mid = low  + (high - low) / 2;

            if (arr[mid] == target) return true;
            else if (arr[mid] < target) low = mid + 1;
            else high = mid -1;
        }

        return false;
    }
    bool splitArraySameAverage(vector<int>& nums) {
        

        /*
        Question asking -> average(A) == average(B) A is left array exist some element and B is right array exist some element

        we know that
        called S = totalSum

        S = sumA + sumB , N = nA + nB , where nA is number of element on sumA array and nB is sumB element count

        we find it
        sumA / nA = sumB / nB ..... main eqn...

        so assume S = sumA + sumB.......(1) eqn first and N = nA + nB .............(2) eqn two
        from eqn (1) , (2)
        sumB = S - sumA  , nB = N - nA

        puth those value in main eqn

        sumA/nA = S - SumA / N - nA

        (N - nA) * sumA = (S - sumA) * nA
        N * sumA - nA * sumA = nA * S - nA * sumA
        N * sumA = nA * S
        [sumA / nA == S / N] , means averge of sumA array exactly equal average of whole array

        sumA ko ab meet int he middle sa karega

        sumA split two array means leftsubsets sum and rightsubset sum

        assume split two array that is called the leftSums and rightSums

        now,

        sumA = leftSubSum  + rightSubSum 
        nA =   sizeof(l) + sizeof(r) called k, m 
        nA = k + m

        main formula = [sumA / nA == S / N]
        put the value

        leftSubSum + rightSubSum / k + m = S / N 
        now this time fix leftSubSum and find rightSum equation rearrange
        now called = k + m = size

       {rightSubSum = S * size / N - leftSubSum}

        ab huma exactuly rightSubSum ke value yahi chaiya isliya hum rightSums ko sort karka every m size ka subsetsum ma search kar lena binary search ke help sa 

        one more optimization rightSums ma set bana lo O(1) ma search

         */
        int N = nums.size();
        int S = accumulate(begin(nums), end(nums), 0);

        int n1 = N / 2;
        int n2 = N - n1;

        unordered_map<int, vector<int>> leftSums;
        
        // T.C = (2 ^N/2 * N/2)
        for (int mask = 0; mask < (1 << n1); mask++) { // explore all subset 2 ^ n

            int count = 0;
            int sum = 0;

            for (int i = 0; i < n1; i++) {

                if (mask & (1 << i)) {
                    sum += nums[i];
                    count++;
                }
            }

            leftSums[count].push_back(sum);
        }

        // unordered_map<int, vector<int>> rightSums;
        unordered_map<int, set<int>> rightSums;

        // T.C = O(2 ^ N/2 * N/2)
        for (int mask = 0; mask < (1 << n2); mask++) {

            int sum = 0;
            int count = 0;

            for (int i = 0; i < n2; i++) {

                if (mask & (1 << i)) {
                    sum += nums[n1+i];
                    count++;
                }
            }

            // rightSums[count].push_back(sum);
            rightSums[count].insert(sum);
        }

        // T.C = O(n2 * log2(2^n2)) = > O(n2 * n2 log2(2)) = O(n * n)
        // for (int count = 0; count <= n2; count++) {
        //     sort(begin(rightSums[count]), end(rightSums[count])); // sort target efficent search
        // }

        // T.C = (N/2 * 2^N/2 * N/2 * log2(2 ^ N/2)) = > ((N/2)cube * 2^N/2 * )
        for (int k=0; k<=n1; k++) {

            for (int leftSubSum : leftSums[k]) {

                for (int m = 0; m <= n2; m++) {

                    int size = k + m; // size of whole SumA array

                    if (size == 0 || size == N) { // arrA can't be empty and no take whole element bcz arrB can't empty
                        continue;
                    }

                    if (S * size % N != 0) continue; // exactly equal hona chaiya 

                    int rightSubSum = S * size / N - leftSubSum;

                    if (rightSums[m].count(rightSubSum)) return true;

                    // if (binarySearch(rightSums[m], rightSubSum)) {
                    //     return true;
                    // }
                }
            }
        }

        return false;
    }
};