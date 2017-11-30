#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cassert>
using namespace std;
typedef unsigned long ulong;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    priority_queue<ulong, vector<ulong>, greater<ulong>> pq;
    ulong n, k;
    ulong result = 0;
    ulong num_op = 0;
    cin >> n >> k;
    //assert(n >= 1 && n <= 1e6);
    //assert(k >= 0 && k <= 1e9);
    
    ulong val;
    bool possible = true;
    
    for (ulong i = 0; i<n; i++) {
        cin >> val;
        pq.push(val);
        //cout << pq.top() << endl;
    }
    if(n == 1 || pq.top() >= k){
        if(pq.top() >= k){
            cout << num_op;
            return 0;
        }
    }
    while (!pq.empty() && pq.size() >= 2) {
        ulong top1 = 0, top2 = 0;
        top1 = pq.top();
        pq.pop();
        
        top2 = pq.top();
        pq.pop();

        if (top1 >= k) {
            break;
        }

        result = 1 * top1 + 2 * top2;
        pq.push(result);
        num_op++;
    }

    if (result >= k) {
        cout << num_op;
    }
    else {
        cout << -1;
    }
    return 0;
}
