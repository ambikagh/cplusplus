

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <string>

using namespace std;



int main() {
    vector<int> v = { 1,2,3,4,5 };
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        cout << *iter << endl;
    }

    for (const auto &a : v) {
        cout << a << endl;
    }

    map<char, int> m = { {'a', 1}, {'b',2}, {'c',5} };
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        cout << iter->first << ":" << iter->second << endl;
    }

    for (const auto& i : m) {
        cout << i.first << ":" << i.second << endl;
    }

    pair<int, int> p = make_pair(1, 2);
    pair<string, int> n("a", 3);
    cout << " pairs";
    cout << p.first << ":" << p.second << endl;
    cout << n.first << ":" << n.second << endl;
    return 0;
}