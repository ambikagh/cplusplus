/* Program finds the number to the right of a[i] such that,
(number=a[j]) > a[i] such that j>i and it is the next largest
For example:
arr = {3, 1, 2, 5, 9, 6, 1}; then resulting array is
res = {5, 2, 5, 6, -1, -1, -1};

*/


#include <iostream>
#include <vector>
using namespace std;

int main() {
    int a[] = { 3, 1, 2, 5, 9, 6, 1};
    //int a[] = { 9,8,7,6,5,4,3,2,1 };
    int length = sizeof(a) / sizeof(int);
    //int *res = new int[length];
    int res[7];
    if (res == NULL) cout << "Mem alloc error" << endl;
    vector<int> stack;

    for (int i = 0; i<length - 1; i++) {
        if (a[i] >= a[i + 1]) {
            stack.push_back(i);
        }
        else {
            res[i] = a[i + 1];
            if (!stack.empty()) {
                if (a[stack.back()] < a[i + 1]) {
                    res[stack.back()] = a[i + 1];
                    stack.pop_back();
                }
            }            
        }
    }
    res[length - 1] = -1;
    int n = length - 1;
    while (!stack.empty() && n >= 0) {
        res[stack.back()] = res[n--];
        stack.pop_back();
    }

    for (int i = 0; i<length; i++) {
        cout << res[i] << " ";
    }

    cout << endl;

    return 0;
}