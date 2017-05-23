#include<iostream>
#include<functional>

using namespace std;

typedef unsigned long long ull;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    clock_t start;
    double duration;

    bool use_flag = false;
    int read_len = 0;
    if (argc == 3) {
        string flag = argv[1];
        string len_str = argv[2];
        use_flag = true;
        read_len = stoi(len_str);
        cerr << "arguments: " << flag << ' ' << read_len << endl;
    } else if (argc != 1 && argc != 3) {
        cerr << "wrong usage" << endl;
        return 1;
    }
    
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
        if (!use_flag) {
            cout << str_hash(line.substr(0, n-1)) << ' ' << str_hash(line.substr(1, n-1)) << ' ' << line << '\n';
        } else {
            for (int i = 0; i < line.size() - read_len + 1; i++) {
                cout << str_hash(line.substr(i, read_len - 1)) << ' ' << str_hash(line.substr(i + 1, read_len - 1)) << ' ' << line.substr(i, read_len) << '\n';
            }
        }
        if (line_count % 1000002 == 0) {
            duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
            cerr << "current line: " << line_count << '\n';
            cerr << "current time used: " << duration << "s" << endl;
        }
    }

    // stop timer
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cerr << "total time used: " << duration << "s" << endl;
}