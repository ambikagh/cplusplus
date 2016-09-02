// ---------------------------------------------------------------------------
// Author: Mukambika Hegde  
// Date: 2/2/2016
// Course: 502, Heap and Heapsort

// ---------------------------------------------------------------------------
// comparison: 
// Function to compare two data of type 'T', function decides whether 
//       comparison is '>' or '<'
//       Overloaded function '>' or '<' in T class is responsible for 
//       actual comparison
// Return: true if left_data <= right_data
//         false otherwise
template <typename T>
bool Heap<T>::comparedata(const T *left, const T *right) {
    return *left > *right ?  false : true;
}

// ---------------------------------------------------------------------------
// Heap: Constructor
template <typename T>
Heap<T>::Heap() {
    lastIndex = 0;
    T dummy;
    heapdata.push_back(&dummy);
}

// ---------------------------------------------------------------------------
// Heap: Constructor
// Takes function pointer and initializes 'compare' member variable to 
//      function pointer
template <typename T>
Heap<T>::Heap(funcp comp) {
    compare = comp;
    lastIndex = 0;
    T dummy; 
    heapdata.push_back(&dummy);
}

// ---------------------------------------------------------------------------
// is_empty:
// Checks whether heap is empty or not, returns 'true' if heap is empty
//        returns 'false' otherwise
template <typename T>
bool Heap<T>::is_empty()const {
    return lastIndex == EMPTY ?  true : false;
}

// ---------------------------------------------------------------------------
// ~Heap: Destructor
template <typename T>
Heap<T>::~Heap() {
    destroyHeap();
}

// ---------------------------------------------------------------------------
// destroyHeap: Clean up allocated memory
template <typename T>
void Heap<T>::destroyHeap() {
    if (this->is_empty()) {
        return;
    }
    size_t size = heapdata.size();
    for (int i = 1; i < size; i++) {
        delete heapdata[i];
    }
    while (!heapdata.empty()) {
        heapdata.pop_back();
    }
}

// ---------------------------------------------------------------------------
// push: push data on to heap
// Data is added at the end of heap, heap structure is restored by 
//     repeatedly checking the heap structure all the way upto the first 
//     element ( sift up operation)
template <typename T>
void Heap<T>::push(T *data) {
    heapdata.push_back(data);
    ++lastIndex;
    int newIndex = lastIndex;
    // sift up
    while (newIndex/2 != 0) {
        if (!compare(heapdata[newIndex/2], heapdata[newIndex])) {
            T *temp;
            temp = heapdata[newIndex/2];
            heapdata[newIndex/2] = heapdata[newIndex];
            heapdata[newIndex] = temp;
        }
        else {// already a heap
            break;
        }
        newIndex = newIndex / 2;
    }
}

// ---------------------------------------------------------------------------
// pop: pop data from heap and return the data
// First data in heap is removed. Data is replaced with the last element and 
//    heap structure is restored by sifting down recursively
template <typename T>
T* Heap<T>::pop(void) {
    if (this->is_empty()) {
        return NULL;
    }
    T *temp = heapdata[ROOT];
    heapdata[ROOT] = heapdata[lastIndex--];
    int newIndex = ROOT * 2;
    // sift down
    while (newIndex <= lastIndex) {
        // newIndex now points to smallest among the children
        if (!compare(heapdata[newIndex], heapdata[newIndex + 1])) {
            newIndex = newIndex + 1;
        }
        if (!compare(heapdata[newIndex / 2],heapdata[newIndex])) {
            T *temp;
            temp = heapdata[newIndex/2];
            heapdata[newIndex/2] = heapdata[newIndex];
            heapdata[newIndex] = temp;
        }
        newIndex = newIndex * 2;
    }
    return temp;
}

// ---------------------------------------------------------------------------
// sort:
// Does a in place sort on heap data, and arrages data in reverse sorted 
//   order
template <typename T>
void Heap<T>::sort() {
    int newlastndex = lastIndex;
    while (lastIndex) {
        T* temp = pop();
        // Popped data is placed in the empty slot at the end of heap
	heapdata[lastIndex + 1] = temp; 
    }
    lastIndex = newlastndex;
    // Heap begins at the index 1(ROOT)
    std::reverse((heapdata.begin()+ROOT),heapdata.end());
}
