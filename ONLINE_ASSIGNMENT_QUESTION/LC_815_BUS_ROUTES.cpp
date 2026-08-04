// You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.

// For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
// You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.

// Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.

 

// Example 1:

// Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
// Output: 2
// Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
// Example 2:

// Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
// Output: -1
 

 

// Constraints:

// 1 <= routes.length <= 500.
// 1 <= routes[i].length <= 105
// All the values of routes[i] are unique.
// sum(routes[i].length) <= 105
// 0 <= routes[i][j] < 106
// 0 <= source, target < 106

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        

        if (source == target) {
            return 0;
        }
        int n = routes.size();
        
        unordered_map<int, vector<int>> adj; // store buses to stop like = stop : [bus0, bus1, bus2]
        vector<bool> visited(n+1, false); // store which bus visited not return again that bus

        // T.C O(n * m) where n is the number of route and m is number of stop
        for (int route = 0; route < n; route++) {

            for (int stop : routes[route]) { 

                adj[stop].push_back(route);
            }
        }

        // apply bfs to find minimum time to reach destination
        queue<int> q;

        for (int route : adj[source]) {

            q.push(route); // in buses pa ja sakta hu is source stop sa
            visited[route] = true;
        }

        int busCount = 1; // clamib first bus

        
        // T.C O(n * m) inside the queue maxium n element entry only 
        while (!q.empty()) { // T.C O(n) where n = number of route

            int N = q.size();

            while (N--) { // explore all buses at this level

                int route = q.front();
                q.pop();

                // traveres all stops worst case T.C O(m)
                for (int stop : routes[route]) { // i am here this bus check all stop 

                    if (stop == target) {
                        return busCount;
                    }

                    for (int nextRoute : adj[stop]) { // no find move another bus
                        
                        if (!visited[nextRoute]) {
                            q.push(nextRoute);
                            visited[nextRoute] = true;
                        }
                    }
                }
            }

            busCount++;
        }

        return -1;
    }
};