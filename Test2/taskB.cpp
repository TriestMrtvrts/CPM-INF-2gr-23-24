#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;
int main() {
    string s, f;
    vector <char> glas = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};
    cin >> s >> f;
    long long l = 0, r = 0;
    bool flag;
    while (r < f.size() && l < s.size()) {
        flag = true;
        if (s[l] == f[r] || s[l] - 'a' == f[r] - 'A' || s[l] - 'A' == f[r] - 'a') {
            l++;
            r++;
        } else {
            for (int i = 0; i < glas.size(); i++) {
                if (f[r] == glas[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Different";
                return 0;
            } else {
                r++;
            }
        }
    }
    if (l != s.size()) {
        cout << "Different";
        return 0;
    }
    while (r < f.size()) {
        flag = true;
        for (int i = 0; i < glas.size(); i++) {
            if (f[r] == glas[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "Different";
            return 0;
        } else {
            r++;
        }
    }
    cout << "Same";
    return 0;
}