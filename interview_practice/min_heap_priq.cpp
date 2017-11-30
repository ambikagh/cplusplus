#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int weight;
    int visited;

    Node(int w) {
        weight = w;
        visited = 0;
    }

    bool operator<(const Node rhs) const{
        return weight > rhs.weight;
    }
};
int main() {
    priority_queue<Node> pri_q;
    Node a(5), b(7), c(9), d(3), e(2);
    pri_q.push(a);
    pri_q.push(b);
    pri_q.push(c);
    pri_q.push(d);
    pri_q.push(e);
    cout << "size of priority queue is " << pri_q.size() << endl;
    while(!pri_q.empty()) {
        cout << pri_q.top().weight << " ";
        pri_q.pop();
    }
    return 0;
}