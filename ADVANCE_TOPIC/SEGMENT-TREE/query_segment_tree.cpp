#include <iostream>
#include <vector>

using namespace std;

/* now we find the every query range sum like given query array [[1,4], [3,5], [3,9]] find each query sum now doing Segment tree 

segment tree reach maximum height of tree that means height is log2(n) and every query take only log2(n) + log2(n) => O(log2(n))

so, searching time we have only three possiblity 

1. my range is tottally out of bound that means st > r || end < l so it's totlly out of bound condition return 0
2. my range is tottally inside the range means  l >= st && r <= end return that node hold all sum l to r
3. overlap one left overlap second is right overlap

we have only 3 case so, we will handle it

*/

int query(vector<int>& segementTree, int st, int end, int i, int l, int r) {

    if (l > end || r < st) { // l start after query end , r end after query start
        return 0;
    }

    if (l >= st && r <= end) {
        segementTree[i]; // properly laye my  range
    }

    // overlap case so we will go both side and explore
    int mid = (l + r) / 2;

    return query(segementTree, st, end, 2*i+1, l, mid) + query(segementTree, st, end, 2*i+2, mid+1, r);
    
}