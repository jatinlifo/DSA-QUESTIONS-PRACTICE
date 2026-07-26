// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.

// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.

// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.

// You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign weights to edges in the path such that the cost of the path between ui and vi is odd.

// Return an array answer, where answer[i] is the number of valid assignments for queries[i].

// Since the answer may be large, apply modulo 109 + 7 to each answer[i].

// Note: For each query, disregard all edges not in the path between node ui and vi.

 

// Example 1:

// Input: edges = [[1,2]], queries = [[1,1],[1,2]]

// Output: [0,1]

// Explanation:

// Query [1,1]: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
// Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
// Example 2:



// Input: edges = [[1,2],[1,3],[3,4],[3,5]], queries = [[1,4],[3,4],[2,5]]

// Output: [2,1,4]

// Explanation:

// Query [1,4]: The path from Node 1 to Node 4 consists of two edges (1 → 3 and 3 → 4). Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.
// Query [3,4]: The path from Node 3 to Node 4 consists of one edge (3 → 4). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
// Query [2,5]: The path from Node 2 to Node 5 consists of three edges (2 → 1, 1 → 3, and 3 → 5). Assigning (1,2,2), (2,1,2), (2,2,1), or (1,1,1) makes the cost odd. Thus, the number of valid assignments is 4.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
    public:

    unordered_map<int, vector<int>> adj;
    vector<int> depth;
    vector<vector<int>> ancestorTable;
    int n;
    int cols;
    int MOD = 1e9 + 7;

    void dfs(int root, int parent) {

        ancestorTable[root][0] = parent;

        for (int ngbr : adj[root]) {

            if (ngbr == parent) continue;

            depth[ngbr] = depth[root] + 1;

            dfs(ngbr, root);
        }
    }

    void buildAncestorTable() {

        for (int j=1; j<cols; j++) {
            for (int node=0; node<n; node++) {

                if (ancestorTable[node][j-1] != -1) {
                    ancestorTable[node][j] = ancestorTable[ ancestorTable[node][j-1] ][j-1];
                }
            }
        }
    }

    int findLCA(int u, int v) {

        if (u < v) {
            swap(u, v);
        }

        int k = depth[u] - depth[v];

        for (int j=0; j<cols; j++) {

            if (k & (1 << j)) { // jth bit set or not
                u = ancestorTable[u][j];
            }
        }

        if (u == v) {
            return u;
        }

        for (int j=cols-1; j>=0; j--) {

            if (ancestorTable[u][j] == -1) continue;

            if (ancestorTable[u][j] != ancestorTable[v][j]) {
                u = ancestorTable[u][j];
                v = ancestorTable[v][j];
            }
        }

        return ancestorTable[u][0];
    }


     vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        
        
        n = edges.size() + 1;
        cols = log2(n) + 1;
        for (auto & edge : edges) {
            
            int u = edge[0]-1;
            int v = edge[1]-1;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        depth.resize(n, 0);
        ancestorTable.resize(n, vector<int>(cols, -1));

        dfs(0, -1);
        buildAncestorTable();

        vector<long long> pow2(n+1);
        pow2[0] = 1;

        for (int i=1; i<=n; i++) {
            pow2[i] = (pow2[i-1] * 2LL) % MOD;
        }

        vector<int> ans;

        for (auto q : queries) {

            int u = q[0] - 1;
            int v = q[1] - 1;

            int lca = findLCA(u, v);

            int d = depth[u] + depth[v] - 2 * depth[lca];

            if (d == 0) {
                ans.push_back(0);
            } else {
                ans.push_back(pow2[d-1]);
            }
        }

        return ans;
    }
};