#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
using namespace std;

stack<long> s1;
stack<long> s2;

int sp = 1; // pointing to s1 initially
void enqueue(long x){
    if(sp == 2){
        while(!s2.empty()){
            s1.push(s2.top());
            s2.pop();
            //cout << " in enqueue while" << endl;
        }
        sp = 1;
    }
    s1.push(x);
    
}

long deq(void){
    if(sp == 1){
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
            //cout << " in deq while" << endl;
        }
        sp = 2;
    }
    
    long x = -1;
    if (!s2.empty()){
        x = s2.top();
        s2.pop();
    }
    return x;
}

void print(){
    if(sp == 1){
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
            //cout << " in print while" << endl;
        }
        sp = 2;
    }
    if (!s2.empty()){
        cout << s2.top() << endl;
    }
    else{
        cout << -1 << endl;
    }
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    fstream myfile("Text.txt", ios_base::in);
    fstream outfile("Out.txt", ios_base::out | ios_base::app);

    int n;
    
    
    myfile >> n;
    
    for(int i=0;i<n;i++){
        int type = 0;
        long value = 0;
        myfile >> type;
        if(type == 1){
            myfile >> value;
            //cout << type << endl;
            //cout << value << endl;
            enqueue(value);
        }
        if (type == 2){
            long x = deq();
        }
        if(type == 3){
            print();
        }
    }
    return 0;
}
