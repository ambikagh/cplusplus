

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    string op, subs;
    cin >> n;
    map<string, int> word_map;
    for(int i=0;i<n;i++){
        cin >> op >> subs;
        if(op.compare("add") == 0){
            for(int i = 1;i<=subs.size();i++){
                string substring = subs.substr(0,i);
                if(word_map.find(substring) == word_map.end()){
                    word_map[substring] = 1;
                }
                else{
                    word_map[substring]+=1;
                }
            }
        }
        else if(op.compare("find") == 0){
            if(word_map.find(subs) != word_map.end()){
                cout << word_map[subs] << endl;
            }
            else{
                cout << 0 << endl;
            }
        }
    }
    return 0;
}
