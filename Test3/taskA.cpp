#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        vector <int> a(26, 0);
        bool f = 1;
        if (n % 2) {
            for (int i = 0; i < n; i += 2) {
                a[(int)s[i] - 97]++;
            }
            int c = 0;
            for (int i = 0; i < 26; i++) {
                if (a[i]%2) c++;
            }
            if ((n % 4 == 1 && c > 1) || (n % 4 == 3 && c > 0)) f = 0;
            c = 0;
            for (int i = 0; i < 26; i++)
                a[i] = 0;
            for (int i = 1; i < n; i += 2) {
                a[(int)s[i] - 97]++;
            }
            for (int i = 0; i < 26; i++) {
                if (a[i] % 2) c++;
            }
            if ((n % 4 == 3 && c > 1) || (n % 4 == 1 && c > 0)) f = 0;
        } else {
            for (int i = 0; i < n; i += 2) {
                a[(int)s[i] - 97]++;
            }
            for (int i = 1; i < n; i += 2) {
                a[(int)s[i] - 97]--;
            }
            for (int i = 0; i < 26; i++) {
                if (a[i]) f = 0;
            }
        }
        if (f) cout << "Yes\n";
        else
            cout << "No\n";
    }
}