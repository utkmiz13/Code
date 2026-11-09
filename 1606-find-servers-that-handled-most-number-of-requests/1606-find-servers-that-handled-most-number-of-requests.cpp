
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        
        set<int> available;
        
        for(int i = 0; i < k; i++) {
            available.insert(i);
        }
        
        // {finish time, server}
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> busy;
        
        vector<int> cnt(k, 0);
        
        for(int i = 0; i < arrival.size(); i++) {
            
            // Free all servers whose requests are completed
            while(!busy.empty() && busy.top().first <= arrival[i]) {
                available.insert(busy.top().second);
                busy.pop();
            }
            
            if(available.empty()) {
                continue;
            }
            
            int target = i % k;
            
            // Find first available server >= target
            auto it = available.lower_bound(target);
            
            // Wrap around if no server is found
            if(it == available.end()) {
                it = available.begin();
            }
            
            int server = *it;
            
            available.erase(it);
            
            cnt[server]++;
            
            long long finishTime = (long long)arrival[i] + load[i];
            
            busy.push({finishTime, server});
        }
        
        int mx = *max_element(cnt.begin(), cnt.end());
        
        vector<int> ans;
        
        for(int i = 0; i < k; i++) {
            if(cnt[i] == mx) {
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};
