// You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].

// The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.

// Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.

 

// Example 1:

// Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
// Output: [3,3,7]
// Explanation:
// 1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
// 2) 1 XOR 2 = 3.
// 3) 5 XOR 2 = 7.
// Example 2:

// Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
// Output: [15,-1,5]
 

// Constraints:

// 1 <= nums.length, queries.length <= 105
// queries[i].length == 2
// 0 <= nums[j], xi, mi <= 109


#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;



class TrieNode {
public:

    TrieNode* left;
    TrieNode* right;

    TrieNode () {
        left = nullptr;
        right = nullptr;
    }

    void insert(TrieNode* root, int num) {

        TrieNode* ptr = root;

        for (int i=31; i>=0; i--) {

            int ith_bit = (num >> i) & 1;

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
        }
    }

    int findMaxXor(TrieNode* root, int num) {

        TrieNode* ptr = root;
        int maxXor = 0;

        for (int i=31; i>=0; i--) {

            int ith_bit = (num >> i) & 1;

            if (ith_bit == 1) {

                if (ptr->left) {
                    maxXor += (1 << i);
                    ptr = ptr->left;
                } else {
                    ptr = ptr->right;
                }
            } else {

                if (ptr->right) {
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
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        
        sort(begin(nums), end(nums)); // minimum pick first

        vector<tuple<int, int, int>> sortedQueries;
        int Q = queries.size();

        for (int i=0; i<Q; i++) {
            sortedQueries.push_back({queries[i][0], queries[i][1], i});
        }
        sort(begin(sortedQueries), end(sortedQueries), [](auto& a, auto& b) { // mi ko increasing order ma sort karo
            return get<1>(a) < get<1>(b);
        });

        int min = nums[0];

        TrieNode* root = new TrieNode();

        int idx = 0;
        int n = nums.size();
        vector<int> ans(Q);

        for (auto& query : sortedQueries) {
            int xi = get<0>(query);
            int mi = get<1>(query);
            int i = get<2>(query);

            if (mi < min) {
                ans[i] = -1;
                continue;
            }

            while (idx < n && nums[idx] <= mi) {
                insert(root, nums[idx]);
                idx++;
            }

            int maxXor = findMaxXor(root, xi);

            ans[i] = maxXor;
        }

        return ans;
    }
};



