// You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:

// A cell containing a thief if grid[r][c] = 1
// An empty cell if grid[r][c] = 0
// You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.

// The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.

// Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

// An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.

// The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.

 

// Example 1:


// Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
// Output: 0
// Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
// Example 2:


// Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
// Output: 2
// Explanation: The path depicted in the picture above has a safeness factor of 2 since:
// - The closest cell of the path to the thief at cell (0, 2) is cell (0, 0). The distance between them is | 0 - 0 | + | 0 - 2 | = 2.
// It can be shown that there are no other paths with a higher safeness factor.
// Example 3:


// Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
// Output: 2
// Explanation: The path depicted in the picture above has a safeness factor of 2 since:
// - The closest cell of the path to the thief at cell (0, 3) is cell (1, 2). The distance between them is | 0 - 1 | + | 3 - 2 | = 2.
// - The closest cell of the path to the thief at cell (3, 0) is cell (3, 2). The distance between them is | 3 - 3 | + | 0 - 2 | = 2.
// It can be shown that there are no other paths with a higher safeness factor.
 

// Constraints:

// 1 <= grid.length == n <= 400
// grid[i].length == n
// grid[i][j] is either 0 or 1.
// There is at least one thief in the grid.a



#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;




class Solution {
public:
    
    vector<vector<int>> directions{{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

    bool can(vector<vector<int>>& distanceThiefToCell, int target) {

        if (distanceThiefToCell[0][0] < target) return false;
        int n = distanceThiefToCell.size();
        
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        queue<pair<int, int>> q;

        q.push({0, 0});
        visited[0][0] = true;

        while (!q.empty()) {

            int i = q.front().first;
            int j = q.front().second;
            q.pop();

            if (i == n-1 && j == n-1) {
                return true;
            }

            for (auto & dir : directions) {

                int x = i + dir[0];
                int y = j + dir[1];

                if (x < n && x >= 0 && y < n && y >=0 && !visited[x][y]) {
                    if (distanceThiefToCell[x][y] < target) continue;

                    q.push({x, y});
                    visited[x][y] = true;
                }
            }
        }

        return false;
    }

    int maximumSafenessFactor(vector<vector<int>>& grid) {
        

        /*
        we find safest factor so assume your father called son you go to market and buy some fruits and go carefully bceause some thief is walking sourding market son yeah papa so, after come at home your after asking beta jab tum aye toh tumsa thief ke distance kiti thee
        beta say papa 2 and next time again beta say papa now distance 3 papa bar bar bhejka distance puch ra kabhi 1 , 2, 3, 4 ya 8 7 6 5 1

        get a pattern continue increasing or continue decreasing this patter hint to binary search on answer 

        approach hum left to right range jayega or mid find karka pucha ga ke can do this distance or and moving left, right

        now another step find distance cell to theif this is very huge so hum reverse find karega like find distance theif to cell and apply 
        multi source BFS

        and every cell moving level by level and cover most cells at one time
        */

        int n = grid.size();
        vector<vector<int>> distanceThiefToCell(n, vector<int>(n, 0));
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {
                    q.push({i, j});
                    visited[i][j] = true;
                }
            }
        }

        int level = 1;
        while (!q.empty()) {

            int N = q.size();

            while (N--) {

                int i = q.front().first;
                int j = q.front().second;
                q.pop();

                for (auto& dir : directions) {

                    int x = i + dir[0];
                    int y = j + dir[1];

                    if (x < n && x >= 0 && y < n && y >=0 && !visited[x][y]) {
                        visited[x][y] = true;
                        distanceThiefToCell[x][y] = level;
                        q.push({x, y});
                    }
                }
            }

            level++;
        }

        int low = 1;
        int high = 400;
        int ans = 0;

        while (low <= high) {

            int mid_sf = low + (high - low) / 2;

            if (can(distanceThiefToCell, mid_sf)) {
                ans = mid_sf;
                low = mid_sf + 1;
            } else {
                high = mid_sf - 1;
            }
        }

        return ans;
    }
};