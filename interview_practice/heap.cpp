#include <iostream>
#include <vector>

using namespace std;

int left(int i) {
    return 2*i;
}

int right(int i) {
    return 2*i + 1;
}

int parent(int i) {
    return i / 2;
}

void max_heapify(vector<int> &a, int i) {
    int l = left(i);
    int r = right(i);
    int largest = 0;
    if (l <= a.size()-1 && a[l]>a[i]) {
        largest = l;
    }
    else largest = i;
    if (r <= a.size()-1 && a[r] > a[largest]) {
        largest = r;
    }
    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        max_heapify(a, largest);
    }
    return;
}

void build_max_heap(vector<int> &a) {
    int size = a.size();
    for (int i = size / 2; i >= 1; i--) {
        max_heapify(a, i);
    }
}

void print(vector<int>& a) {
    for (int i = 1; i<a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}


// increase key
void increase_key(vector<int>& a, int i, int key){
    if(key < a[i]){
        cerr << "Key is smaller" << endl;
    }
    a[i] = key;
    while(i>1 && a[parent(i)] < a[i]){
        int temp = a[parent(i)];
        a[parent(i)] = a[i];
        a[i] = temp;
        i = parent(i);
    }
}

// insert key
void insert_key(vector<int>& a, key){
    a.push_back(-123456);
    increase_key(a, a.size(), key);
}

// extract max
int extract_max(vector<int>& a){
    if(a.size()<2){
        cerr("Heap underflow");
    }
    int max = a[1];
    a[1] = a[a.size()];
    a.pop_back();
    a[0]--;
    max_heapify(a, 1);
    return max;
}

// heapsort
void heapsort(vector<int>& a){
    build_max_heap(a);
    for(i = a.size();i>=2;i--){
        int temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        max_heapify(a, 1);
    }
}


int main() {
    vector<int> a;
    int arr[] = { 16,4,10,14,7,9,3,2,8,1 };
    //int arr[] = { 4,1,3,2,16,9,10,14,8,7 };
    int length = sizeof(arr) / sizeof(int);
    a.push_back(length);
    for (int i = 0; i < length; i++) {
        a.push_back(arr[i]);
    }
    print(a);
    max_heapify(a, 2);
    //build_max_heap(a);
    print(a);
    return 0;
}