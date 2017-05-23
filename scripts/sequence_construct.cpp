#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef unsigned long long ull;
typedef pair<ull, ull> pll;

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (argc != 3) {
        cerr << "usage: this_prog <map_file> <alignment_file> \n";
        return 1;
    }

    clock_t start;
    double duration;

    //start timer
    cerr << "started !!!!" << endl;
    start = clock();

    // start working
    string map_file = argv[1];
    string alignment_file = argv[2];

    ifstream mapf (map_file);
    ifstream alignf (alignment_file);
    map<pll, char> pll_map;

    string read;
    ull left, right;
    ull line_count = 0;
    while (mapf >> left >> right >> read) {
        pll_map[{left, right}] = read[0];
        line_count++;
        if (line_count % 1000000 == 0) {
            cerr << "@line: " << line_count << '\n';
        }
    }
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cerr << "generated mapping @ " << duration << "s\n";

    char c;
    left = right = 0;
    ull next;
    ull component_count = 0;
    // bool start_chain = false;
    while (alignf >> c) {
        if (c == '+') continue;
        alignf >> next;
        if (pll_map.find({right, next}) == pll_map.end()) {

            component_count++;
            if (component_count % 10000 == 0) {
                cerr << "component count: " << component_count << endl;
            }

            read = pll_map[{left, right}];
            // cout << read.substr(1, read.size() - 1) << ' ';
            left = right;
            right = next;
        } else {
            left = right;
            right = next;
            cout << pll_map[{left, right}];
        }

    }
    if (pll_map.find({left, right}) != pll_map.end()) {
        read = pll_map[{left, right}];
        cout << read.substr(1, read.size() - 1);
    }

    // stop timer
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cerr << "total time: " << duration << "s\n";

    return 0;
}