/* Merge sort */

#include <iostream>
#include <vector>

#define MAX_SIZE 100
using namespace std;

void merge(int a[], int low, int mid, int high) {
    int i = low, j = mid + 1, k = 0;
    int *ta = new int[MAX_SIZE];
    while (i <= mid && j <= high) {
        if (a[i] <= a[j]) {
            ta[k++] = a[i++];
        }
        else {
            ta[k++] = a[j++];
        }
    }
    while (i <= mid) {
        ta[k++] = a[i++];
    }
    while (j <= high) {
        ta[k++] = a[j++];
    }

    k--;

    while (k >= 0) {
        a[low + k] = ta[k];
        k--;
    }

    free(ta);
}
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
void mergesort(int a[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergesort(a, low, mid);
        mergesort(a, mid + 1, high);
        merge(a, low, mid, high);
    }    

}

int main() {
    int arr[] = { 1,7,4,2,6,5,2,9,0,3 };
    int size = sizeof(arr) / sizeof(int);

    mergesort(arr, 0, size-1);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}