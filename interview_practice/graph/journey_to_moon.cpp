#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector> 
#include <list>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cassert>

using namespace std; // }}}
 
int main()
{ 
    unsigned long long N, I;
    cin >> N >> I;
    vector<vector<int> > pairs(N);
    for (int i = 0; i < I; ++i) {
        int a, b;
        cin >> a >> b;
        pairs[a].push_back(b);
        pairs[b].push_back(a);
    }
 
    unsigned long long result = 0;
    queue<int> q;
    vector<int> visited(N);
    vector<unsigned long> set;
    /** Write code to compute the result using N,I,pairs **/
    for(int i=0;i<N;i++){
        int count = 0;
        if (!visited[i]){
            q.push(i);
            visited[i] = 1;
            while(!q.empty()){
                int j = q.front();    
                q.pop();
                for(auto &a: pairs[j]){
                    // if a is not visited
                    if(!visited[a]){
                        // push a to st
                        q.push(a);
                        visited[a] = 1;
                    }
                }
                count++;
           }
           set.push_back(count);
        }
    }
    
    unsigned long long same = 0;
    
    for(int i=0;i<set.size();i++){
        same += (set[i]*(set[i] - 1))/2;
    }
    
    result = (N*(N-1)/2) - same;
    cout << result << endl;
    return 0;
}
