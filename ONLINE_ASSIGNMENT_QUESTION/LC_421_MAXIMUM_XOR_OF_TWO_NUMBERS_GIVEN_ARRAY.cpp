// Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.

 

// Example 1:

// Input: nums = [3,10,5,25,2,8]
// Output: 28
// Explanation: The maximum result is 5 XOR 25 = 28.
// Example 2:

// Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
// Output: 127
 

// Constraints:

// 1 <= nums.length <= 2 * 105
// 0 <= nums[i] <= 231 - 1

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class TrieNode {
public:
    TrieNode* left;
    TrieNode* right;

    TrieNode() {
        left = NULL;
        right = NULL;
    }

    void insert(TrieNode* root, int num) {

        TrieNode* ptr = root;

        for (int i=31; i>=0; i--) {

            int ith_bit = (num >> i) & 1; // which bit 0, 1

            if (ith_bit == 1) { // ith bit 1 this bit insert right side

                if (ptr->right == NULL) { // if bit is null then create new bit
                    ptr->right = new TrieNode();
                }
                ptr = ptr->right; // already bit exist and ptr move next node
            } else {
                // bit is 0
                if (ptr->left == NULL) { // if bit is null then create new bit
                    ptr->left = new TrieNode();
                }
                ptr = ptr->left; // already bit exist and ptr move next node
            }
        }
    }

    int findMaxXor(TrieNode* root, int num) {

        int maxXor = 0;
        TrieNode* ptr = root;

        for (int i=31; i>=0; i--) {

            int ith_bit = (num >> i) & 1;

            if (ith_bit == 1) {

                if (ptr->left) { // if bit 1 then xor to 0 now moving left side if exist 
                    maxXor += pow(2, i); // pow(2, i) * (1 ^ 0)  = pow(2, i) * 1 // (1 ^ 0) after xor ka bad jo bit aai
                    // like 101 i find 0 so suppose 0 find then 101
                    //                                          0...
                    //                                          1... iska matlab ya hai
                    ptr = ptr->left;
                } else { // now moving right side always exist
                    // maxXor += pow(2, i);  pow(2, i) * (1 ^ 1) = pow(2, i) * 0 means 0 no add
                    ptr = ptr->right;
                }
            } else {

                if (ptr->right) { // if current bit is 0 now find always 1 bcz perfume xor every time find maximum 
                // number bcz xor hold the property MST bit jitni 1 hogi utna bada number
                    maxXor += pow(2, i); // pow(2, i) * (0 ^ 1) = pow(2, i) * 1 means 1 ko multiple
                    ptr = ptr->right;
                } else {
                    // maxXor += pow(2, i); pow(2, i) * (0 ^ 0) = pow(2, i) * 0 means 0 no add
                    ptr = ptr->left;
                }
            }
        }

        return maxXor;
    }
};

class Solution : public TrieNode {
public:
    int findMaximumXOR(vector<int>& nums) {

        /* 
        create trie to search log(n) time to which next bit move
        means my current number 5 -> 101
        3rd bit is 1 so whose bit i choose to find maximum xor that is 0
        so, this is efficent search using trie

        called BitTrie 
        hold only two child left, right left hold 0 and right hold 1

        */

        TrieNode* root = new TrieNode();

        for (int num : nums) {
            insert(root, num);
        }

        int ans = 0;

        for (int num : nums) {

            ans = max(ans, findMaxXor(root, num));
        }

        return ans;
    }
};