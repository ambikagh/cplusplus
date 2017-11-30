#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;


class IceCream {

public:
    int flavor;
    int index;

    IceCream(int flavo, int inde) {
        flavor = flavo;
        index = inde;
    }
};

int binarySearch(int first, int last, vector<IceCream> arr, int search) {
    if (first <= last) {
        int mid = (first + last) / 2;
        if (arr[mid].flavor == search) return arr[mid].index;
        else if (arr[mid].flavor > search) {
            return binarySearch(first, mid - 1, arr, search);
        }
        else {
            return binarySearch(mid + 1, last, arr, search);
        }
    }
    else return -1;
}

bool compare(IceCream l, IceCream r) {
    if (l.flavor < r.flavor) return true;
    else return false;
}

int main() {
    fstream myfile("Text.txt", std::ios_base::in);
    int t;
    int n, m;
    myfile>> t;
    for (int test = 0; test < t; test++) {
        myfile>> m >> n;
        vector<IceCream> arr;
        arr.reserve(n);

        for (int i = 0; i < n; i++) {
            
            int cost;
            myfile>> cost;
            arr.push_back(IceCream(cost, i + 1));
        }

        sort(arr.begin(), arr.end(), compare);
        int firstIndex = 100000, secondIndex = 100000;
        for (int i = 0; i < n - 1; i++) {
            int search = m - arr[i].flavor;
            if (search >= arr[i].flavor) {
                int index = binarySearch(i + 1, n - 1, arr, search);
                if (index != -1) {
                    cout << min(arr[i].index, index) << " " << max(arr[i].index, index) << endl;
                    break;

                }
            }
        }

    }
    return 0;
}

