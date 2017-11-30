/* Folders and cows program */
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
enum folder_type { SF, CF };
struct info {
    int type; // 0 ->SF 1->CF
    map<int, int> member_cows;
    vector<int> children;
};
int main(int argc, char* argv[]) {
    fstream myfile("Text.txt", std::ios_base::in);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int no_of_cows;
    myfile >> no_of_cows;
    int num_shared, num_confi;
    myfile >> num_shared >> num_confi;
    vector<struct info> folder_info;
    map<int, info> folders;
    map<int, int> uncool_cows;
    for (int i = 0; i < no_of_cows; i++) {
        uncool_cows[i] = 0;
    }
    info dummy_info;
    folders[-1] = dummy_info;
    // read shared folder details
    for (int i = 0; i < num_shared; i++) {
        int id;
        myfile >> id;
        info f;
        f.type = SF;
        for (int j = 0; j < no_of_cows; j++) {
            f.member_cows[j] = 0;
        }
        int cows;
        myfile >> cows;
        for (int j = 0; j < cows; j++) {
            int cow_id;
            myfile >> cow_id;
            if (f.member_cows.find(cow_id) != f.member_cows.end()) {
                f.member_cows[cow_id] += 1;
            }
        }
        folders[id] = f;
        folders[-1].children.push_back(id);
    }

    // read confidential folder details
    for (int i = 0; i < num_confi; i++) {
        int id;
        myfile >> id;
        info f;
        f.type = CF;
        for (int j = 0; j < no_of_cows; j++) {
            f.member_cows[j] = 0;
        }
        int cows;
        myfile >> cows;
        for (int j = 0; j < cows; j++) {
            int cow_id;
            myfile >> cow_id;
            if (f.member_cows.find(cow_id) != f.member_cows.end()) {
                f.member_cows[cow_id] += 1;
            }
        }
        folders[id] = f;
        folders[-1].children.push_back(id);
    }

    int g;
    myfile >> g;

    for (int i = 0; i < g; i++) {
        int parent, child;
        myfile >> parent;
        myfile >> child;
        folders[parent].children.push_back(child);
        for (int i = 0; i < folders[-1].children.size(); i++) {
            if (folders[-1].children[i] == child) {
                folders[-1].children.erase(folders[-1].children.begin() + i);
            }
        }
    }

    queue<int> f_q;

    for (int i = 0; i < folders[-1].children.size(); i++) {
        f_q.push(folders[-1].children[i]);
    }

    while (!f_q.empty()) {
        int f_id = f_q.front();
        f_q.pop();
        for (int i = 0; i < folders[f_id].children.size(); i++) {
            int child = folders[f_id].children[i];
            if (folders[child].type == SF) {
                for (int j = 0; j < folders[f_id].member_cows.size(); j++) {
                    if (folders[f_id].member_cows[j] != 0) {
                        if (folders[child].member_cows[j] == 0) {
                            folders[child].member_cows[j] += 1;
                        }
                    }
                }
            } 
            f_q.push(child);
        }
        if (folders[f_id].children.size() == 0) {
            for (int i = 0; i < folders[f_id].member_cows.size(); i++) {
                if (folders[f_id].member_cows[i] == 0) {
                    uncool_cows[i] = 1;
                }
            }
            
        }
    }

    for (int i = 0; i < no_of_cows; i++) {
        if (uncool_cows[i]) cout << i << " ";
    }
    return 0;
}
