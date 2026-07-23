// Time limit: 1.00 s
// Memory limit: 512 MB

// You are given an array of n numbers. In how many ways can you choose a subset of the numbers with sum x?
// Input
// The first input line has two numbers n and x: the array size and the required sum.
// The second line has n integers t_1,t_2,\dots,t_n: the numbers in the array.
// Output
// Print the number of ways you can create the sum x.
// Constraints

// 1 \le n \le 40
// 1 \le x \le 10^9
// 1 \le t_i \le 10^9

// Example
// Input:
// 4 5
// 1 2 3 2

// Output:
// 3


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {

    int n;
    long long x;
    cin >> n >> x;

    vector<long long> t(n);

    for (int i=0; i<n; i++) {
        cin >> t[i];
    }

    int n1 = n/2;
    int n2 = n-n1;

    vector<long long> sumsA(1LL << n1);

    for (int mask = 0; mask < (1 << n1); mask++) {

        long long sum = 0;

        for (int i=0; i<n1; i++) {

            if (mask & (1 << i)) {
                sum += t[i];
            }
        }

        sumsA[mask] = sum;
    }

    vector<long long> sumsB(1LL << n2);

    for (int mask=0; mask < (1 << n2); mask++) {

        long long sum = 0;

        for (int i=0; i<n2; i++) {

            if (mask & (1 << i)) {
                sum += t[n1+i];
            }
        }

        sumsB[mask] = sum;
    }

    sort(begin(sumsB), end(sumsB));


    long long count = 0;

    for (long long s : sumsA) {

        long long need = x - s;

        auto low = lower_bound(begin(sumsB), end(sumsB), need);
        auto high = upper_bound(begin(sumsB), end(sumsB), need);

        count += (high - low);
    }

    cout << count << endl;

    return 0;
};