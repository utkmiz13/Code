
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct BIT {
        int n;
        vector<long long> bit;

        BIT(int n) : n(n), bit(n + 1, 0) {}

        void update(int i, long long val) {
            for (; i <= n; i += i & -i)
                bit[i] += val;
        }

        long long query(int i) {
            long long sum = 0;
            for (; i > 0; i -= i & -i)
                sum += bit[i];
            return sum;
        }

        int kth(int k) {
            int idx = 0;
            int mask = 1;

            while ((mask << 1) <= n)
                mask <<= 1;

            for (; mask; mask >>= 1) {
                int next = idx + mask;

                if (next <= n && bit[next] < k) {
                    idx = next;
                    k -= bit[next];
                }
            }

            return idx + 1;
        }
    };

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<int> a = nums;
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());

        int m = a.size();

        BIT cnt(m), sum(m);

        auto add = [&](int val, int delta) {
            int id = lower_bound(a.begin(), a.end(), val) - a.begin() + 1;
            cnt.update(id, delta);
            sum.update(id, 1LL * val * delta);
        };

        auto getCost = [&]() -> long long {
            int id = cnt.kth((x + 1) / 2);
            long long med = a[id - 1];

            long long c1 = cnt.query(id);
            long long s1 = sum.query(id);

            long long total = sum.query(m);

            return med * c1 - s1
                 + (total - s1) - med * (x - c1);
        };

        int windows = n - x + 1;
        vector<long long> cost(windows);

        for (int i = 0; i < x; i++)
            add(nums[i], 1);

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            add(nums[i - x], -1);
            add(nums[i], 1);

            cost[i - x + 1] = getCost();
        }

        const long long INF = LLONG_MAX / 4;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];

                if (i >= x) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
