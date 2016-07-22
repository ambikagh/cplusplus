#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cout << "Enter the number upto which you wish to calculate prime numbers";
    int num;
    cin >> num;
    const int size = num;
    int *arr = new int[size + 1];
    for (int i = 0; i <= size; i++) {
        arr[i] = i;
    }
    int sr_num = sqrt(num);
    
    for (int i = 2; i <= sr_num; i++) {
        for (int j = 2; i*j <= size; j++) {
            if (arr[i*j] % i == 0) arr[i*j] = 0;
        }
    }
    for (int i = 2; i <= size; i++) {
        if (arr[i])cout << arr[i] << " ";
    }

    delete[] arr;
    return 0;
}