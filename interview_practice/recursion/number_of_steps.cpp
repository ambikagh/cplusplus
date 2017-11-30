/* Program calculates number of steps that can be taken to reach top of the stairs
if number of steps taken is 1, 2 and 3 at a time*/

#include <iostream>
#include <vector>

using namespace std;

int count_ways(int n, int memo[]){
  if(n<0){
    return 0;
  }
  else if( n = 0) return 1;
  else if (memo[n]>-1) return memo[n];
  else return count_ways(n-1, memo)+count_ways(n-2, memo)+count_ways(n-3, memo);
}
int  count_ways_dp(int num){
  int *memo = new int[num];
  for(int i=0;i<num;i++){
    memo[i]= -1;
  }
  return count_ways(num, memo);
}

int count_ways_rec(int n){
  if(n<0){
    return 0;
  }
  else if( n = 0) return 1;
  else return count_ways_rec(n-1)+count_ways_rec(n-2)+count_ways_rec(n-3);
}

int main(){
  int num;
  cout << "Enter number of steps" << endl;
  cin >> num;

  cout << count_ways_dp(num);
  cout << endl;
  return 0;
}