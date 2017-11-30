/* Magic index in an array is defined as index such that A[i] = i ,
following program searches for magic index, if one exisists in array A.
Array is SORTED */

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
int magic_index_brute(int a[], int size) {
    for (int i = 0; i<size; i++) {
        if (a[i] == i) return i;
    }
    return -1;
}

int magic_index_r(int a[], int lb, int ub) {
    if (ub < lb) return -1;
    int mid = (ub + lb) / 2;
    if (a[mid] == mid) return mid;
    else if (a[mid]<mid) {
        return magic_index_r(a, mid + 1, ub);
    }
    else {
        return magic_index_r(a, lb, mid - 1);
    }
}

// recursive implementation
int magic_index_rec(int a[], int size) {
    return magic_index_r(a, 0, size);
}


// recursive implementation for duplicates
int magic_index_rd(int a[], int lb, int ub) {
    if (ub < lb) return -1;
    int midIndex = (ub + lb) / 2;
    int midValue = a[midIndex];

    if (midIndex == midValue) return midIndex;

    // search left
    int leftIndex = min(midIndex - 1, midValue);
    int left = magic_index_rd(a, lb, leftIndex);
    if (left >= 0) return left;

    // search right
    int rightIndex = max(midIndex + 1, midValue);
    int right = magic_index_rd(a, rightIndex, ub);

    return right;
}

int magic_index_rd(int a[], int size) {
    return magic_index_rd(a, 0, size);
}
int main() {
    int array[] = { -40,-20,-1,1,2,3,5,7,9,12,13 };
    int array1[] = { -10,-5,2,2,2,3,4,7,9,12,13 };
    cout << magic_index_brute(array, 11);
    cout << magic_index_rec(array, 11);
    cout << magic_index_rd(array1, 11);
    return 0;
}