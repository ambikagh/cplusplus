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

using namespace std;

bool ransom_note(vector<string> magazine, vector<string> ransom) {
    int m_size = magazine.size();
    int r_size = ransom.size();
    if (r_size > m_size) return false;
    int found = 1;
    map<string, int> word_map;
    map<string, int> r_map;

    for (int i = 0; i<m_size; i++) {
        if (word_map.find(magazine[i]) == word_map.end())
            word_map[magazine[i]] = 1;
        else {
            word_map[magazine[i]] += 1;
        }
    }

    for (int i = 0; i<r_size; i++) {
        if (r_map.find(ransom[i]) == r_map.end())
            r_map[ransom[i]] = 1;
        else {
            r_map[ransom[i]] += 1;
        }
    }

    for (int i = 0; i<r_size; i++) {
        if (word_map.find(ransom[i]) == word_map.end() || word_map[ransom[i]] != r_map[ransom[i]])
            return false;
    }

    return true;
}

int main() {
    int m;
    int n;
    cin >> m >> n;
    vector<string> magazine(m);
    for (int magazine_i = 0; magazine_i < m; magazine_i++) {
        cin >> magazine[magazine_i];
    }
    vector<string> ransom(n);
    for (int ransom_i = 0; ransom_i < n; ransom_i++) {
        cin >> ransom[ransom_i];
    }
    if (ransom_note(magazine, ransom))
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}
