/* Find shortest distance to from node s to all other nodes, if there is no edge
existing between node s and node n, distance is -1
Input format:
2  // #of queries
4 2 // no_nodes no_edges
1 2 // edge between node 1 and node 2
1 3
1 // source node for query 1
3 1
2 3
2 // source node for query 2

Output format:
6 6 -1  // there is no edge between 1 and 4
-1 6 // no edge between 2 and 1

These distances should be listed sequentially by node number (i.e.,1,2,...n), but should not include node s.
If some node is unreachable from node s, print -1 as the distance to that node.
*/

#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include <limits>

#define MAX_NODES 1000

using namespace std;
enum node_color {WHITE, GREY, BLACK};

struct node {
    int name;
    int distance;
    int color;
    node() {} 

    node(int n, int d, int c) {
        name = n; distance = d; color = c;
    }

    bool operator<(const node rhs)const {
        return distance > rhs.distance;
    }
};

int main(int argc, char * argv[]) {
    fstream myfile("Text.txt", std::ios_base::in);

    int **graph = new int*[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++) {
        graph[i] = new int[MAX_NODES];
    }
    map<int, node> vertices;
    map<int, int> shortest;
    int num_queries;
    myfile >> num_queries;
    for (int a0 = 0; a0 < num_queries; a0++) {
        int num_nodes;

        int num_edges;
        myfile >> num_nodes >> num_edges;
        for (int i = 1; i <= num_nodes; i++) {
            node n(i, INT_MAX, WHITE);
            vertices[i] = n;
            for (int j = 1; j <= num_nodes; j++) {
                graph[i][j] = 0;
            }
            shortest[i] = -1;
        }
        for (int a1 = 0; a1 < num_edges; a1++) {
            int u;
            int v;
            myfile >> u >> v;
            if (u != v) {
                graph[u][v] = 6;
                graph[v][u] = 6;
            }
        }
        int s;
        myfile >> s;
        vertices[s].distance = 0;
        vertices[s].color = GREY;
        priority_queue<node> q;
        q.push(vertices[s]);
        while (!q.empty()) {
            node start = q.top();
            q.pop();
            if (vertices[start.name].color != BLACK) {
                for (int i = 1; i <= num_nodes; i++) {
                    if (graph[start.name][i] && vertices[i].color == WHITE) {
                        int distance = vertices[start.name].distance + graph[start.name][i];
                        if (distance < vertices[i].distance) {
                            vertices[i].distance = distance;
                            vertices[i].color = GREY;
                        }
                        q.push(vertices[i]);
                    }                   

                }
            }
            vertices[start.name].color = BLACK;
            shortest[start.name] = start.distance;
            
        }

        for (int i = 1; i <= num_nodes; i++) {
            if (i != s) {
                cout << shortest[i] << " ";
            }
        }

        cout << endl;

    }
    return 0;
}




/* version 2 */
/*
#include <bits/stdc++.h>
#include<limits>
#include<vector>


using namespace std;

#define unsigned long long LONG

int main() {
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        int n;
        int m;
        cin >> n >> m;
        vector<vector<int>> pairs(n+1);
        vector<int> visited(n+1);
        vector<int> distance(n+1);
        for(int i=1;i<=n;i++){
            distance[i] = INT_MAX;
        }
        queue<int> q;
        for(int a1 = 0; a1 < m; a1++){
            int u;
            int v;
            cin >> u >> v;
            pairs[u].push_back(v);
            pairs[v].push_back(u);
        }
        int s;
        cin >> s;
        
        distance[s] = 0;
        q.push(s);
        visited[s] = 1;
        while(!q.empty()){
            int source = q.front();
            q.pop();
            for(auto &a: pairs[source]){
                if(!visited[a]){
                    distance[a] = distance[source]+6;
                    q.push(a);
                    visited[a] = 1;
                }
            }
        }
        
        for(int i=1;i<=n;i++){
            if(i != s){
                if(visited[i]){
                    cout << distance[i] << " ";
                }
                else{
                    distance[i] = -1;
                    cout << distance[i] << " ";
                }
            }
        }
        cout << endl;
        
    }
    return 0;
}
*/