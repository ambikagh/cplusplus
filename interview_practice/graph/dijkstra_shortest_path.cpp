#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cassert>

using namespace std;
#define MAX_NODES 3000

vector<pair<int,int>> graph[MAX_NODES]; // (node, weight)


int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int m;
        cin >> n >> m;
        
        assert(2 <= n && n <= MAX_NODES);
        assert(1 <= m && m <= 1LL * n * (n-1)/2);
        
        for(int i=0;i<n;i++) graph[i].clear();
        
        for(int a1 = 0; a1 < m; a1++){
            int x;
            int y;
            int r;
            cin >> x >> y >> r;
            x--;
            y--;
            graph[x].push_back({y,r});
            graph[y].push_back({x,r});
        }
        int s;
        cin >> s;
        s--;
        
        vector<int> distance(n);
        vector<int> visited(n);
        fill(distance.begin(), distance.end(), INT_MAX);
        fill(visited.begin(), visited.end(), 0);
        
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
        distance[s] = 0;
        q.push({0, s});
        
        while(!q.empty()){
            int source = q.top().second;
            int weight = q.top().first;
            q.pop();
            if(visited[source])continue;
            visited[source] = 1;
            for(const auto &a: graph[source]){
                int dist = weight + a.second;
                if(dist < distance[a.first]){
                    distance[a.first] = dist;
                    q.push({distance[a.first], a.first});
                }
            }
        }
        for(int i=0;i<n;i++){
            if(i==s) continue;
            
            if(distance[i] == INT_MAX){
                cout << -1 << " ";
            }
            else {
                cout << distance[i] << " ";
            }
            
        }
        
    }
    return 0;
}
