
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);

        dp[0] = 1;

        int i2 = 0, i3 = 0, i5 = 0;

        for (int i = 1; i < n; i++) {

            int a = dp[i2] * 2;
            int b = dp[i3] * 3;
            int c = dp[i5] * 5;

            int next = min({a, b, c});

            dp[i] = next;

            if (next == a) i2++;
            if (next == b) i3++;
            if (next == c) i5++;
        }

        return dp[n - 1];
    }
};
