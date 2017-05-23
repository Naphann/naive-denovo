#include<iostream>
#include<functional>

using namespace std;

typedef unsigned long long ull;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    clock_t start;
    double duration;
    
    // start timer
    start = clock();

    // start working
    ull line_count = 0;
    string line;
    while (getline(cin, line)) {
        line_count++;
        if ((line_count & 3) != 2) 
            continue;
        size_t n = line.size();
        hash<string> str_hash;
        cout << str_hash(line.substr(0, n-1)) << ' ' << str_hash(line.substr(1, n-1)) << ' ' << line << '\n';

        if (line_count % 10000002 == 0) {
            duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
            cerr << "current line: " << line_count << '\n';
            cerr << "current time used: " << duration << "s" << endl;
        }
    }

    // stop timer
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cerr << "total time used: " << duration << "s" << endl;
}