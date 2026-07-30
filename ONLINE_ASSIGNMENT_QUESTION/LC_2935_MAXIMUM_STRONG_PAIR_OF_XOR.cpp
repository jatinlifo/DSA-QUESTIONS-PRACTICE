// You are given a 0-indexed integer array nums. A pair of integers x and y is called a strong pair if it satisfies the condition:

// |x - y| <= min(x, y)
// You need to select two integers from nums such that they form a strong pair and their bitwise XOR is the maximum among all strong pairs in the array.

// Return the maximum XOR value out of all possible strong pairs in the array nums.

// Note that you can pick the same integer twice to form a pair.

 

// Example 1:

// Input: nums = [1,2,3,4,5]
// Output: 7
// Explanation: There are 11 strong pairs in the array nums: (1, 1), (1, 2), (2, 2), (2, 3), (2, 4), (3, 3), (3, 4), (3, 5), (4, 4), (4, 5) and (5, 5).
// The maximum XOR possible from these pairs is 3 XOR 4 = 7.
// Example 2:

// Input: nums = [10,100]
// Output: 0
// Explanation: There are 2 strong pairs in the array nums: (10, 10) and (100, 100).
// The maximum XOR possible from these pairs is 10 XOR 10 = 0 since the pair (100, 100) also gives 100 XOR 100 = 0.
// Example 3:

// Input: nums = [500,520,2500,3000]
// Output: 1020
// Explanation: There are 6 strong pairs in the array nums: (500, 500), (500, 520), (520, 520), (2500, 2500), (2500, 3000) and (3000, 3000).
// The maximum XOR possible from these pairs is 500 XOR 520 = 1020 since the only other non-zero XOR value is 2500 XOR 3000 = 636.
 

// Constraints:

// 1 <= nums.length <= 5 * 104
// 1 <= nums[i] <= 220 - 1

// ******** ya approach samjhana ka liya leetcode 421 ka code dekhna usma pora explain hai  ********


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class TrieNode {
public:

    TrieNode* left; // left bit is 0
    TrieNode* right; // right bit is 1
    int count; // store how many number store current node 

    TrieNode() {
        left = nullptr;
        right = nullptr;
        count = 0;
    }

    void insert(TrieNode* root, int num) {

        TrieNode* ptr = root;


        for (int i=31; i>=0; i--) {

            int ith_bit = (num >> i) & 1; // which bit

            if (ith_bit == 1) {

                if (ptr->right == nullptr) {
                    ptr->right = new TrieNode();
                }

                ptr = ptr->right;
            } else {

                if (ptr->left == nullptr) {
                    ptr->left = new TrieNode();
                }

                ptr = ptr->left;
            }

            ptr->count++; // comes new number count++ that node
        }
    }

    void erase(TrieNode* root, int num) {

        TrieNode* ptr = root;

        for (int i=31; i>=0; i--) {

            int ith_bit = (num >> i) & 1;

            if (ith_bit == 1) {
                ptr = ptr->right;
            } else {
                ptr = ptr->left;
            }

            ptr->count--; // this number remove my trie
        }
    }


    int maximumXor(TrieNode* root, int num) {

        int maxXor = 0;
        TrieNode* ptr = root;

        for (int i=31; i>=0; i--) {

            int ith_bit = (num >> i) & 1;

            if (ith_bit == 1) {

                if (ptr->left && ptr->left->count > 0) {
                    maxXor += (1 << i);
                    ptr = ptr->left;
                } else {
                    ptr = ptr->right;
                }
            } else {

                if (ptr->right && ptr->right->count > 0) {
                    maxXor += (1 << i);
                    ptr = ptr->right;
                } else {
                    ptr = ptr->left;
                }
            }
        }

        return maxXor;
    }
};


class Solution : public TrieNode {
public:
    int maximumStrongPairXor(vector<int>& nums) {
        
        /*
        abs(x - y) <= min(x, y)
        
        assume y always greater than x then

        abs(y - x) <= min(x, y) now remove abs
        y - x <= min(x, y) i assume y always greater so x always minimum
        then,
        y - x <= x
        y <= 2x , this is genric form 
        */

        TrieNode* root = new TrieNode();

        sort(begin(nums), end(nums));
        int ans = 0;

        int i = 0;
        int n = nums.size();

        for (int j=0; j<n; j++) {

            insert(root, nums[j]);

            while (i < n && nums[j] > nums[i] * 2) {
                erase(root, nums[i]); // this elment remove my trie bcz it is very minimum future ma kisi sa pair nee banega or nums sort hai j element always maximum hoga
                i++;
            }

            ans = max(ans, maximumXor(root, nums[j]));
        }

        return ans;
    }
};