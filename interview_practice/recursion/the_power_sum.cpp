/*
Find the number of ways that a given integer, X

, can be expressed as the sum of the nth 


power of unique, natural numbers. 

Constraints
1<= X <= 1000
2<= N <= 10

Output Format
Output a single integer, the answer to the problem explained above. 
Sample Input 0
10
2

Sample Output 0
1

only one way 2 represent 10 as sum of unique squares 
10 = 1^2 + 3^2

*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int tot_power_sum(int X, int N, int num){
    if (pow(num,N) < X){
        return tot_power_sum(X, N, num+1) + tot_power_sum(X-pow(num,N), N, num+1);
    }
    else if(pow(num,N) == X){
        return 1;
    }
    else return 0;
}

int main() {
    int X,N;
    cin>>X>>N;
    cout<<tot_power_sum(X,N,1);
    return 0;
}