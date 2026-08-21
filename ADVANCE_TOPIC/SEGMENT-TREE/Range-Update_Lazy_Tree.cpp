

/*
any query given raneg [l, r] or val = 2 and update each value of laye the index l to r
this type of query we use segmenttree lazy propogation bcz we could not use simple update segmenttree code 
bcz we have multiple query assume given query is length almost Q and each updation complexity is O(Q * log(H)) this is huge

T.C = > O(log(n))
S.C = > O(4*n)

*/

#include <iostream>
#include <vector>

using namespace std;



void rangeUpdateSegmentTree(int st, int end, int val, int i, int l, int r, vector<int>& segmentTree, vector<int>& lazy) {

    if (lazy[i] != 0) {
        int totalNodesInsideThisCurrentRoot = (r - l) + 1;
        // lazy bhai value bss mere ma add kar da nicha mere neibors pa mat ja ma khud dekh lunga
        segmentTree[i] += lazy[i] * totalNodesInsideThisCurrentRoot;

        if (l != r) { // not leaf node always exist left and right child bcz proper binary tree
            lazy[2*i+1] = lazy[i]; // abhi lazy[i] hold kar ra tha but in future tumha ya value add karni hai understand
            lazy[2*i+2] = lazy[i];
        }

        lazy[i] = 0; // mena ya information aga provide kar dee tu mere holidy ho gaya ab
    }

    // out of bound
    if (l > end || st > r || l > r) {
        return;
    }

    // in range

    if (l >= st && r <= end) {
        
        int totalNodesInsideMe = (r - l) + 1;
        segmentTree[i] = (totalNodesInsideMe * val);

        // ab bss mere left child or right child ko bata do

        if (l != r) {
            lazy[2*i+1] += val;
            lazy[2*i+2] += val;
        }

        return;
    }

    // now i am standing overlap condition

    int mid = l + (r - l) / 2;

    rangeUpdateSegmentTree(st, end, val, 2*i+1, l, mid, segmentTree, lazy);
    rangeUpdateSegmentTree(st, end, val, 2*i+2, mid+1, r, segmentTree, lazy);

    segmentTree[i] = segmentTree[2*i+1] + segmentTree[2*i+2];

}

void update(int st, int end, int val, vector<int>& nums) {

    int n = nums.size();
    vector<int> segmentTree(4*n); // build first
    vector<int> lazy(4*n);

    rangeUpdateSegmentTree(st, end, val, 0, 0, n-1, segmentTree, lazy);
}