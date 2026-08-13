// You are given a 0-indexed string s. You are also given a 0-indexed string queryCharacters of length k and a 0-indexed array of integer indices queryIndices of length k, both of which are used to describe k queries.

// The ith query updates the character in s at index queryIndices[i] to the character queryCharacters[i].

// Return an array lengths of length k where lengths[i] is the length of the longest substring of s consisting of only one repeating character after the ith query is performed.

// Example 1:

// Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
// Output: [3,3,4]
// Explanation: 
// - 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
// - 2nd query updates s = "bbbccc". 
//   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
// - 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
// Thus, we return [3,3,4].
// Example 2:

// Input: s = "abyzz", queryCharacters = "aa", queryIndices = [2,1]
// Output: [2,3]
// Explanation:
// - 1st query updates s = "abazz". The longest substring consisting of one repeating character is "zz" with length 2.
// - 2nd query updates s = "aaazz". The longest substring consisting of one repeating character is "aaa" with length 3.
// Thus, we return [2,3].
 

// Constraints:

// 1 <= s.length <= 105
// s consists of lowercase English letters.
// k == queryCharacters.length == queryIndices.length
// 1 <= k <= 105
// queryCharacters consists of lowercase English letters.
// 0 <= queryIndices[i] < s.length


#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    
    struct Node {

        int len; // store this segment string length
        int best; // now yet best answer
        int suffix; // store the current node of suffix
        int prefix; // store the current node of prefix
        char leftChar; // current  string ka first char
        char rightChar; // current string ka last cahr
    };

    Node merge(Node left, Node right) {

        Node parent; // create new root node

        // take left = aaba , right = aaba 
        // parent = "aabaaaba" i.e
        parent.len = left.len + right.len; // root node length is left + right
        parent.best = max(left.best, right.best); // store maximum of left segment or right segment
        // current root ka staring and last char yahi hoga always
        parent.leftChar = left.leftChar;
        parent.rightChar = right.rightChar;

        // if left ka right most equal huva right ka left most sa
        // means left = "aaba", right = "aaba"
        //                  ^            ^
        // parent = "aabaaaba" length = 3 maximum

        if (left.rightChar == right.leftChar) {

            parent.best = max(parent.best, left.suffix + right.prefix);

            // if left ka pora suffix aapni len ka equal huva toh parent ka prefix hoga
            // left.prefix + right.prefix ex. left = "aaaa", right "aabb"

            if (left.prefix == left.len) {
                parent.prefix = left.len + right.prefix;
            } else {
                parent.prefix = left.prefix;
            }

            if (right.suffix == right.len) {
                parent.suffix = right.len + left.suffix;
            } else {
                parent.suffix = right.suffix;
            }
        } else {
            parent.prefix = left.prefix;
            parent.suffix = right.suffix;
        }

        return parent;

    }
    
    void buildSegmentTree(int i, int l, int r, string& s, vector<Node>& segmentTree) {

        if (l == r) {
            segmentTree[i].len = 1;
            segmentTree[i].best = 1;
            segmentTree[i].prefix = 1;
            segmentTree[i].suffix = 1;
            segmentTree[i].leftChar = s[l];
            segmentTree[i].rightChar = s[l];
            return;
        }

        int mid = l + (r - l) / 2;

        buildSegmentTree(2*i+1, l, mid, s, segmentTree);
        buildSegmentTree(2*i+2, mid+1, r, s, segmentTree);

        segmentTree[i] = merge(segmentTree[2*i+1], segmentTree[2*i+2]);
    }

    void update(int idx, char ch, int i, int l, int r, vector<Node>& segmentTree) {

        if (l == r) {
            segmentTree[i].leftChar = ch;
            segmentTree[i].rightChar = ch;
            segmentTree[i].len = 1;
            segmentTree[i].prefix = 1;
            segmentTree[i].suffix = 1;
            segmentTree[i].best = 1;
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid) {
            update(idx, ch, 2*i+1, l, mid, segmentTree);
        } else {
            update(idx, ch, 2*i+2, mid+1, r, segmentTree);
        }

        segmentTree[i] = merge(segmentTree[2*i+1], segmentTree[2*i+2]);
    }

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        
        int n = s.length();
        vector<Node> segmentTree(4*n);

        buildSegmentTree(0, 0, n-1, s, segmentTree);
        int Q = queryCharacters.size();
        vector<int> ans(Q);

        for (int i = 0; i < Q; i++) {

            char ch = queryCharacters[i];
            int idx = queryIndices[i];

            update(idx, ch, 0, 0, n-1, segmentTree);

            ans[i] = segmentTree[0].best;
        }

        return ans;
    }
};