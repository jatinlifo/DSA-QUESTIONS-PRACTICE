// You are given two strings word1 and word2.

// A string x is called almost equal to y if you can change at most one character in x to make it identical to y.

// A sequence of indices seq is called valid if:

// The indices are sorted in ascending order.
// Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal to word2.
// Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. If no such sequence of indices exists, return an empty array.

// Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by those indices.

 

// Example 1:

// Input: word1 = "vbcca", word2 = "abc"

// Output: [0,1,2]

// Explanation:

// The lexicographically smallest valid sequence of indices is [0, 1, 2]:

// Change word1[0] to 'a'.
// word1[1] is already 'b'.
// word1[2] is already 'c'.
// Example 2:

// Input: word1 = "bacdc", word2 = "abc"

// Output: [1,2,4]

// Explanation:

// The lexicographically smallest valid sequence of indices is [1, 2, 4]:

// word1[1] is already 'a'.
// Change word1[2] to 'b'.
// word1[4] is already 'c'.
// Example 3:

// Input: word1 = "aaaaaa", word2 = "aaabc"

// Output: []

// Explanation:

// There is no valid sequence of indices.

// Example 4:

// Input: word1 = "abc", word2 = "ab"

// Output: [0,1]

 

// Constraints:

// 1 <= word2.length < word1.length <= 3 * 105
// word1 and word2 consist only of lowercase English letters.


#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        
        int n = word1.length();
        int m = word2.length();

        vector<int> suffix(n, 0); // we store honw many element exist i to i+1 which is match in word2
        int rightMatchCount = 0;

        int i = n-1;
        int j = m-1;

        while (i >= 0) {

            if (j >= 0 && word1[i] == word2[j]) { // store all suffix count
                rightMatchCount++;
                j--;
            }
            suffix[i] = rightMatchCount;
            i--;
        }

        vector<int> ans;
        bool canChange = true;
        i = 0;
        j = 0;

        while (i < n && j < m) {

            if  (j == m) return ans;

            if (word1[i] == word2[j]) {
                ans.push_back(i); // choose greedly since question ma lexciographically diya hai
                j++;
            } else if (canChange && i + 1 < n && suffix[i+1] >= m - j - 1) { // check j+1 ka all character match ho jayega future ma or not yadi ma current ko pick kar lo
                ans.push_back(i);
                canChange = false;
                j++;
            }

            i++;
        }

        return (j == m) ? ans : vector<int>();
    }
};