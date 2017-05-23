#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;

/*
format for input 
for each line : 
    <left:size_t> <right:size_t> // where size_t is 8 bytes (according to testing machines)
*/
typedef unsigned long long ull;
typedef pair<ull,ull> node;

void Hierholzer(map<ull, vector<ull>> &adj, clock_t start) {

    map<ull, int> edge_count;
    for (auto p: adj) {
        edge_count[p.first] = p.second.size();
    }

    stack<ull> current_path;
    vector<ull> circuit;

    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cerr << "finished preparing for Hierholzer @" << duration << "s" << endl;

    for (auto it = adj.begin(); it != adj.end(); it++) {
        if (edge_count[it->first] == 0) 
            continue;
        
        // print separator for each component
        cout << "+" << '\n';

        ull u = it->first;
        current_path.push(u);

        while (!current_path.empty()) {
            if (edge_count[u]) {
                current_path.push(u);
                ull v = adj[u].back();
                edge_count[u]--;
                adj[u].pop_back();
                u = v;
            } else {
                circuit.push_back(u);
                u = current_path.top();
                current_path.pop();
            }
        }
    }

    for (int i = circuit.size() - 1; i >= 0; i--) {
        cout << "@ " << circuit[i] << '\n';
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    clock_t start;
    double duration;
    
    // start timer
    start = clock();

    // start working
    map<ull, vector<ull>> adj;
    int nodes = 0;
    ull left, right;
    string line;
    while (cin >> left >> right) {
        adj[left].push_back(right);
    }

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cerr << "finished creating graph @" << duration << "s" << endl;
    
    // Hierholzer
    Hierholzer(adj, start);
    
    // stop timer
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cerr << "total time used: " << duration << "s" << endl;

}