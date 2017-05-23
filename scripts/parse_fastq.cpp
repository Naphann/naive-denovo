#include <iostream>
#include <fstream>
#include <deque>
#include <unordered_map>
#include <ctime>
using namespace std;

typedef unsigned long long ull;
#define MAPLEN 32
#define SHIFT_LEN (MAPLEN * 2 - 2)

deque<char> temp;
unordered_map<char, ull> char_map;

inline ull deque_to_ull(string s) {
    ull ret = 0;
    for (int i = 0, shift = SHIFT_LEN; i < MAPLEN; i++, shift-= 2) {
        ret |= (char_map[s[i]] << shift);
    }
    return ret;
}

inline void raw_read_to_ull(string line) {
    int n = line.size() - MAPLEN + 1;

    for (int i = 0; i < n; i++) {
        ull out = deque_to_ull(line.substr(i, MAPLEN));
        cout << out << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    clock_t start;
    double duration;
    
    // start timer
    start = clock();

    // working part
    string line;
    char_map['A'] = 0;
    char_map['C'] = 1;
    char_map['G'] = 2;
    char_map['T'] = 3;
    temp.assign(MAPLEN, 'X');
    ull line_count = 0;
    while (getline(cin, line)) {
        // cerr << "printing " << line_count << endl;
        line_count++;
        if ((line_count & 3ULL) == 2) {
            // cerr << "in here" << endl;
            raw_read_to_ull(line);
        }

        if ((line_count & 0xffff) == 0) {
            cerr << "current line: " << line_count << endl;
        }
    }

    // stop timer
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cerr << "time used: " << duration << "s" << endl;
}