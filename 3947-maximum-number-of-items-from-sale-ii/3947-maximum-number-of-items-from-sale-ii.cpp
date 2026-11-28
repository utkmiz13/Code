
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);

        for (auto &it : items) {
            freq[it[0]]++;
        }

        // Precompute divisible item counts
        vector<int> divCount(n + 1, 0);

        for (int f = 1; f <= n; f++) {
            for (int j = f; j <= n; j += f) {
                divCount[f] += freq[j];
            }
        }

        vector<int> d(n);

        for (int i = 0; i < n; i++) {
            d[i] = divCount[items[i][0]] - 1;
        }

        long long p = LLONG_MAX;

        for (auto &it : items) {
            p = min(p, (long long)it[1]);
        }

        vector<int> order(n);
        iota(order.begin(), order.end(), 0);

        sort(order.begin(), order.end(), [&](int a, int b) {
            return items[a][1] < items[b][1];
        });

        long long remaining = budget;
        long long ans = 0;

        for (int idx : order) {
            long long price = items[idx][1];

            if (price > 2 * p) break;

            long long take = min(
                (long long)d[idx],
                remaining / price
            );

            ans += 2 * take;
            remaining -= take * price;
        }

        ans += remaining / p;

        return (int)ans;
    }
};
