
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 1;

        while ((1 << LOG) <= n) LOG++;

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Next greater element
        vector<int> nxt(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }

            if (!st.empty()) {
                nxt[i] = st.top();
            }

            st.push(i);
        }

        // Binary lifting
        vector<vector<int>> up(LOG, vector<int>(n, n));
        vector<vector<long long>> cost(LOG, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];

            cost[0][i] =
                1LL * nums[i] * (nxt[i] - i)
                - (pref[nxt[i]] - pref[i]);
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = up[j - 1][i];

                if (mid < n) {
                    up[j][i] = up[j - 1][mid];

                    cost[j][i] =
                        cost[j - 1][i] + cost[j - 1][mid];
                }
            }
        }

        // Calculate operations for [l, r]
        auto getCost = [&](int l, int r) {
            long long res = 0;
            int cur = l;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][cur] <= r) {
                    res += cost[j][cur];
                    cur = up[j][cur];
                }
            }

            res += 1LL * nums[cur] * (r - cur + 1)
                   - (pref[r + 1] - pref[cur]);

            return res;
        };

        // Sliding window
        long long ans = 0;
        int r = 0;

        for (int l = 0; l < n; l++) {
            while (r < n && getCost(l, r) <= k) {
                r++;
            }

            ans += r - l;

            if (r < l + 1) {
                r = l + 1;
            }
        }

        return ans;
    }
};
