#include<bits/stdc++.h>
using namespace std;
int t, n, k, x, a[200002], sum[200002], maxn;
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> k >> x; maxn = -2100000000;
        for (int i=1; i <= n; i++) cin >> a[i];
        sort(a+1, a+n+1);
        for (int i=1; i <= n; i++) sum[i]=sum[i-1]+a[i];
        for (int i=n-k; i <= n; i++) maxn=max(maxn, sum[max(0, i-x)]-(sum[i]-sum[max(0, i-x)]));
        cout << maxn << "\n";
    }
    return 0;
}