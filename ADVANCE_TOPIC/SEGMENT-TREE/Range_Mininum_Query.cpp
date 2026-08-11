#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class SegmentTree {
    public:

    vector<int> tree;
    int n;

    SegmentTree(vector<int>& nums) {
        n = nums.size();
        tree.resize(4*n);

        buildSegmentTree(0, 0, n-1, nums);
    }

    void buildSegmentTree(int i, int l, int r, vector<int>& nums) {

        if (l == r) {
            tree[i] = nums[l];
            return;
        }

        int mid = l + (r - l) / 2;

        buildSegmentTree(2*i+1, l, mid, nums);
        buildSegmentTree(2*i+2, mid+1, r, nums);

        tree[i] = min(tree[2*i+1], tree[2*i+2]);
    }

    int query(int st, int end) {
        return querySegmentTree(st, end, 0, 0, n-1);
    }

    int querySegmentTree(int st, int end, int i, int l, int r) {

        if (l > end || r < st) {
            return  INT_MAX;
        }

        if (l >= st && r <= end) {
            return tree[i];
        }

        int mid = l + (r - l) / 2;

        int left = querySegmentTree(st, end, 2*i+1, l, mid);
        int right = querySegmentTree(st, end, 2*i+2, mid+1, r);

        return min(left, right);
    }
};

class Solution {
public:

    vector<int> rangeMinimumQuery(vector<int>& nums, vector<vector<int>> queries) {

        SegmentTree segmentTree(nums);

        vector<int> ans;
        
        for (auto& q : queries) {

            int l = q[0];
            int r = q[1];

            ans.push_back(segmentTree.query(l, r));
        }

        return ans;
    }
};

int main () {

    vector<int> nums = {1, 2, 3, 4, 4, 5, 6, 2, 1, 4, 5};
    vector<vector<int>> queries{{1, 2}, {3, 4}, {5, 5}, {1, 10}};

    Solution obj;

    vector<int> ans = obj.rangeMinimumQuery(nums, queries);

    cout << ans.size() << endl;

    for (int i = 0; i < ans.size(); i++) {

        cout << "Query is :  " << queries[i][0] << " " << queries[i][1] << " " << "Ans:-->  " << ans[i] << endl;
    }

    return 0;
}