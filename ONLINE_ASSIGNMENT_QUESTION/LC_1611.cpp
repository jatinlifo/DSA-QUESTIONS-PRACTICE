// Given an integer n, you must transform it into 0 using the following operations any number of times:

// Change the rightmost (0th) bit in the binary representation of n.
// Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are set to 0.
// Return the minimum number of operations to transform n into 0.

 

// Example 1:

// Input: n = 3
// Output: 2
// Explanation: The binary representation of 3 is "11".
// "11" -> "01" with the 2nd operation since the 0th bit is 1.
// "01" -> "00" with the 1st operation.
// Example 2:

// Input: n = 6
// Output: 4
// Explanation: The binary representation of 6 is "110".
// "110" -> "010" with the 2nd operation since the 1st bit is 1 and 0th through 0th bits are 0.
// "010" -> "011" with the 1st operation.
// "011" -> "001" with the 2nd operation since the 0th bit is 1.
// "001" -> "000" with the 1st operation.
 

// Constraints:

// 0 <= n <= 109

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minimumOneBitOperations(int n) {
        
        vector<long long> F(31, 0);
        F[0] = 1;
        // ======= Ek Dam wahit Question =================
        for (int i=1; i<=30; i++) {
            F[i] = 2 * F[i-1] + 1;
        }
        
        int ans = 0;
        int sign = 1;

        for (int i=30; i>=0; i--) {

            int ith_bit = (n & (1 << i));

            if (ith_bit != 0) {
                ans += (sign * F[i]);
                sign *= -1;
            }
        }
        return ans;
    }
};