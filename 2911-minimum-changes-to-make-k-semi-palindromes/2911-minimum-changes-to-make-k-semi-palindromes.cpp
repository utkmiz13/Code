
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Precompute cost of making every substring semi-palindrome
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                int len = r - l + 1;

                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;

                    for (int i = 0; i < d; i++) {
                        int left = i;
                        int right = i + ((len - 1 - i) / d) * d;

                        while (left < right) {
                            if (s[l + left] != s[l + right]) {
                                changes++;
                            }

                            left += d;
                            right -= d;
                        }
                    }

                    cost[l][r] = min(cost[l][r], changes);
                }
            }
        }

        // DP: minimum changes to divide first j characters into i parts
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));

        dp[0][0] = 0;

        for (int i = 1; i <= k; i++) {
            for (int j = 2 * i; j <= n; j++) {
                for (int p = 2 * (i - 1); p <= j - 2; p++) {
                    if (dp[i - 1][p] == INF) continue;

                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - 1][p] + cost[p][j - 1]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
