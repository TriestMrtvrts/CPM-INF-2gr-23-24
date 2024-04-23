#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    long long k;
    cin >> n >> k;

    vector<long long> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    const long long M = 2520;
    k *= M;

    const int T = 11;
    vector<long long> q(T);

    for (int i = 0; i < n; i++) {
        q[s[i]] += abs(a[i] - s[i]);
    }

    long long sum = 0;
    for (int i = 1; i < T; i++) {
        sum += q[i] * M / i;
    }

    long long ans = 0;
    for (int i = 1; i < T; i++) {
        auto one = M / i;
        if (sum - one * q[i] > k) {
            sum -= one * q[i];
            ans += q[i];
            continue;
        }
        auto need = sum - k;
        if (need > 0) {
            ans += (need - 1) / one + 1;
        }
        break;
    }

    cout << ans << '\n';

    return 0;
}