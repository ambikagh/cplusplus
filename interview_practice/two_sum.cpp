#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> two_sum(vector<int>&, int );


int main() {
    int t_arr[6] = { 2, 4, 6, 12, 45, 13 };
    vector<int> nums;

    for (int i = 0; i < 6; i++) {
        nums.push_back(t_arr[i]);
    }

    cout << "two numbers are" << endl;
    vector<int> ind = two_sum(nums, 19);
    for (vector<int>::iterator i = ind.begin(); i < ind.end(); i++) {
        cout << *i << " ";
    }

    return 0;

}

/*
Using brute force(O(n2))
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

*/
/*
// using hash map O(n) two pass

vector<int> two_sum(vector<int>& v_num, int target) {
    vector<int> index;
    map<int, int> n_map;

    for (int i = 0; i < v_num.size(); i++) {
        n_map[v_num[i]] = i;
    }

    for (int i = 0; i < v_num.size(); i++) {
        if (n_map.find(target - v_num[i]) != n_map.end()) {
            index.push_back(i);
            index.push_back(n_map[target - v_num[i]]);
            return index;
        }
    }
    
    if (!index.size()) index.push_back(-1);
    return index;
}
*/
// using hash map O(n) one pass
vector<int> two_sum(vector<int>& v_num, int target) {
    vector<int> index;
    map<int, int> n_map;
     

    for (int i = 0; i < v_num.size(); i++) {
        n_map[v_num[i]] = i;
        if (n_map.find(target - v_num[i]) != n_map.end()) {
            index.push_back(i);
            index.push_back(n_map[target - v_num[i]]);
            return index;
        }
    }

    if (!index.size()) index.push_back(-1);
    return index;
}