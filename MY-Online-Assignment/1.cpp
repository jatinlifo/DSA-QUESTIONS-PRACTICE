/*

This is Amazone OA question 

We have a string s and k we need to find maximum consecutive ones for any substring and also we have a k
you can apply at most one operation of any substring where the substring length and this substring choose k length and 
you can convert consecutive zeros to ones then after peform this operation your final substring has only ones 
your task to find maximum length of substring where has all ones could not find length return -1


Input:
S = "101001"
k = 2

Explanation:

s = "101001" choose index 0 to 1 and convert s = "111001" len = 3
s = "101001" choose index 3 to 4 and convert s ="101111" len = 4

Output = 4


*/

// i am not sure this solution is completely working or not but i did run many test cases and give me correct output
// Anyone know about this problem so please share me your approach and give me some sample test cases. 

#include <iostream>
#include <string>

using namespace std;

int findLen(string s, int k) {

    int n = s.length();
    int i = 0;
    int ans = 0;
    int zeros = 0;
    bool isCon = true;

    // "100101001";

    for (int j = 0; j < n; ++j) {

        if (s[j] == '0') {

            if (isCon == false) {

                while (i < j && zeros > 0) {
                    
                    if (s[i]  == '0') {
                        zeros--;
                    }

                    i++;
                }

                isCon = true;
            }

            zeros++;

        } else {

            if (zeros > 0) {
                isCon = false;
            }
        }

        while (i < j && zeros > k) {

            if (s[i] == '0') {
                zeros--;
            }
            i++;
        }

        ans = max(ans, j  - i + 1);
    }

    if (ans < k) return -1;

    return ans;
}

int main ()  {

    string s = "100000";
    int k = 2;

    int ans = findLen(s, k);

    cout << "Maximum Len is : " << ans << endl;
}