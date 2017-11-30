#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;

int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    fstream myfile("Text.txt", ios_base::in);
    int n;
    myfile >> n;
    if (n == 0) return 0;
    int *arr = new int[n];
    float mean, median;
    int mode;
    map<int, int> count;
    mean = 0;
    int max = 0;
    for (int i = 0; i<n; i++) {
        myfile >> arr[i];
        mean += arr[i];
        if (count.find(arr[i]) != count.end()) {
            count[arr[i]] += 1;

        }
        else {
            count[arr[i]] = 1;
        }
        if (count[arr[i]]> max) {
            max = count[arr[i]];
            mode = arr[i];
        }
    }
    mean = (float)mean / n;
    cout << mean << endl;

    qsort(arr, n, sizeof(int), compare);
    if (max == 1) mode = arr[0];

    if (n % 2) {
        median = arr[n / 2];
    }
    else {
        int mid = n / 2;
        median = (arr[mid] + arr[mid - 1]) / 2;
    }

    cout << mean << " " << median << " " << mode << endl;
    return 0;

}
