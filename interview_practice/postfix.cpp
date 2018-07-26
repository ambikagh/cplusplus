#include <iostream>
#include <queue>
#include <string>
#include <stack>


using namespace std;

int evaluate(queue<string> postfix){
  stack<int> s;
  while(!postfix.empty()){
    string str = postfix.front();
    postfix.pop();

    if(atoi(str))
  }

}