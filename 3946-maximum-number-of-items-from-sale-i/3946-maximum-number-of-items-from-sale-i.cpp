
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int minPrice = INT_MAX;

        vector<int> dp(budget + 1, 0);

        // Find the cheapest item
        for (auto& item : items) {
            minPrice = min(minPrice, item[1]);
        }

  
        for (int i = 0; i < n; i++) {
            int factor = items[i][0];
            int price = items[i][1];

            
            int cnt = 0;

            for (int j = 0; j < n; j++) {
                if (items[j][0] % factor == 0) {
                    cnt++;
                }
            }

            
            for (int j = budget; j >= price; j--) {
                dp[j] = max(dp[j], dp[j - price] + cnt);
            }
        }


        int ans = 0;

        for (int i = 0; i <= budget; i++) {
            ans = max(ans, dp[i] + (budget - i) / minPrice);
        }

        return ans;
    }
};
