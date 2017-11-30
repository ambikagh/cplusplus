/* This program sorts an array using quick sort*/

#include <iostream>
#include <vector>

using namespace std;


int partition(int a[], int lb, int ub) {
    int pivot = a[lb];

    int i = lb+1;
    for (int j = lb+1; j <= ub; j++) {
        if (a[j] < pivot) {
            int temp = a[j];
            a[j] = a[i];
            a[i] = temp;
            i++;            
        }
    }
    a[lb] = a[i - 1];
    a[i - 1] = pivot;

    return i - 1;
}
void quicksort(int a[], int low, int high) {
    if (low > high) return;
    int j = partition(a, low, high-1);
    quicksort(a, low, j - 1);
    quicksort(a, j + 1, high);

}

int main() {
    int arr[] = { 1,7,4,8,6,5,2,9,0,3 };
    int size = sizeof(arr) / sizeof(int);

    quicksort(arr, 0, size);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}