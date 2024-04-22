#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n, m;
    long long k;
    scanf("%d %d %lld", &n, &m, &k);
    vector <pair<long long, int> > w(n);
    for (int i = 0; i < n; ++i)
        scanf("%lld", &w[i].first), w[i].second = i;
    vector <bool> isSpecial(n, 0);
    for (int i = 0; i < m; ++i) {
        int t;
        scanf("%d", &t);
        isSpecial[t - 1] = 1;
    }
    int minSpecial = n;
    sort(w.begin(), w.end());
    for (int i = 0; i < n; ++i) {
        if (isSpecial[w[i].second]) {
            minSpecial = i;
            while (minSpecial && w[minSpecial - 1].first == w[minSpecial].first)
                --minSpecial;
            break;
        }
    }

    long long minimalCost = 0;
    long long lastGiven = 0;
    long long low = 0;
    for (int i = 1; i < n; ++i) {
        if (w[i - 1].first != w[i].first)
            ++lastGiven;
        minimalCost += lastGiven;
        if (i == minSpecial)
            low = lastGiven;
    }
    if (k < minimalCost) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    long long high = k + 1;
    while (low != high -  1) {
        long long middle = (low + high) / 2;
        lastGiven = 0;
        minimalCost = 0;
        bool flag = 1;
        for (int i = 1; i < minSpecial && flag; ++i) {
            if (w[i - 1].first != w[i].first)
                ++lastGiven;
            minimalCost += lastGiven;
            if (minimalCost > k)
                flag = 0;
        }
        lastGiven = middle;
        for (int i = minSpecial; i < n; ++i) {
            minimalCost += lastGiven;
            if (minimalCost > k)
                flag = 0;
            if (i + 1 != n && w[i + 1].first != w[i].first)
                ++lastGiven;
        }
        if (minimalCost > k)
            flag = 0;
        if (flag)
            low = middle;
        else
            high = middle;
    }
    printf("POSSIBLE\n");
    vector <long long> answer(n, 0);
    for (int i = 1; i < minSpecial; ++i) {
        answer[i] = answer[i - 1];
        if (w[i - 1].first != w[i].first)
            ++answer[i];
    }
    if (minSpecial != n)
        answer[minSpecial] = low;
    for (int i = minSpecial + 1; i < n; ++i) {
        answer[i] = answer[i - 1];
        if (w[i - 1].first != w[i].first)
            ++answer[i];
    }
    vector <long long> trueAns(n);
    for (int i = 0; i < n; ++i)
        trueAns[w[i].second] = answer[i];
    for (int i = 0; i < n; ++i)
        printf("%lld ", trueAns[i]);
    printf("\n");
    return 0;
}