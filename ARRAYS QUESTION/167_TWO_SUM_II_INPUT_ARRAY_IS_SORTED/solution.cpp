// Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
// Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
// The tests are generated such that there is exactly one solution. You may not use the same element twice.
// Your solution must use only constant extra space.
// Example 1:
// Input: numbers = [2,7,11,15], target = 9
// Output: [1,2]
// Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
// Example 2:

// Input: numbers = [2,3,4], target = 6
// Output: [1,3]
// Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].

#include<iostream>
#include<vector>

using namespace std;

class Solution{
    public:

    vector<int> twoSumII(vector<int>& nums, int target){
        
        int n = nums.size();
        int left = 0;
        int right = n-1;
        int currSum = 0;
        while(left <= right)
        {
            currSum = nums[left]+nums[right];

            if(currSum > target){
                right--;
            }
            else if(currSum < target){
                left++;
            }
            else{
                return{left+1,right+1};
            }
        }
        return {-1,-1};
    }
};

int main () {
    int n;
    
    cout<<"Enter the size of array : ";
    cin>>n;
    vector<int> nums(n);
    cout<<"Enter the element's of array : ";
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    int target;
    cout<<"Enter the target value : ";
    cin>>target;
    vector<int> ans(2);
    Solution obj;
    ans = obj.twoSumII(nums,target);
    cout<<"Idx is "<<ans[0]<<" "<<ans[1]<<endl;
    return 0;
}