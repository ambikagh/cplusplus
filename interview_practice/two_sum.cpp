/*Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
For example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> two_sum(vector<int>&, int );


int main() {
    int t_arr[6] = { 2, 4, 6, 12, 45, 13 };
    vector<int> nums;

    for (int i = 0; i < 6; i++) {
        nums.push_back(t_arr[i]);
    }

    cout << "two numbers are" << endl;
    vector<int> ind = two_sum(nums, 15);
    for (vector<int>::iterator i = ind.begin(); i < ind.end(); i++) {
        cout << *i << " ";
    }

    return 0;

}

vector<int> two_sum(vector<int>& v_num, int target) {
    vector<int> index;
    for (int i = 0; i < v_num.size()-1; i++) {
        for (int j = i + 1; j < v_num.size(); j++) {
            if (v_num[i] == target - v_num[j]) {
                index.push_back(i);
                index.push_back(j);
                return index;
            }
        }
    }
}