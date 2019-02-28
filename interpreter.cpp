#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

const int STACK_SIZE = 30000;
const int SHOW_SIZE = 5;

int rsp = 0;
bool skip = false;

unsigned char memStack[STACK_SIZE];

stack<int> recStack;

string line;

inline void inc_rsp() { rsp++; }
inline void dec_rsp() { rsp--; }
inline void add_rsp(int x) { memStack[rsp] += x; }

inline void print_exception(int i) {
    cout << "exception at index " << i << endl;
    int pos = (i < SHOW_SIZE ? i : SHOW_SIZE);
    cout << line.substr(i - pos, min(SHOW_SIZE * 2, (int)line.size() - i + pos)) << endl;
    for (int j = 0; j < pos; j++) cout << ' ';
    cout << "^" << endl;
}

inline bool out_of_bound() {
    return rsp < 0 || rsp >= 30000;
}

bool isZero() {
    return memStack[rsp] == 0;
}

inline void init() {
    line = "";
    while (recStack.size()) recStack.pop();
    memset(memStack, 0, sizeof memStack);
    rsp = 0;
    skip = false;
}

inline void output() { cout << (char)memStack[rsp]; }

inline void read() {
    cin >> memStack[rsp];
}

int main() {
    ios::sync_with_stdio(false);

    while (true) {
        cout << "brainfucker> ";
        
        init();
        cin >> line;

        for (int i = 0; i < line.size(); i++) {
            char c = line[i];
            if (c != ']' && skip) continue;
            
            else if (c == '.') { 
                if (out_of_bound()) { print_exception(i); break; }
                output();
            }

            else if (c == ',') {
                if (out_of_bound()) { print_exception(i); break; }
                read();
            }

            else if (c == ']') {
                if (!recStack.size() || out_of_bound()) { print_exception(i); break; }
                int prev = recStack.top(); recStack.pop();
                if (skip || isZero()) { skip = false; continue; }
                i = prev - 1;
            }

            else if (c == '<') { dec_rsp(); }
            
            else if (c == '>') { inc_rsp(); }
            
            else if (c == '-' || c == '+') {
                if (out_of_bound()) { print_exception(i); break; }
                add_rsp(c == '+' ? 1 : -1);
            }

            else if (c == '[') {
                if (out_of_bound()) { print_exception(i); break; }
                recStack.push(i);
                if (isZero()) { skip = true; }
            }
        }

    }
}