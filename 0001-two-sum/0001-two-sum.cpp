
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;

        for (int i = 0; i < nums.size(); i++) {
            int required = target - nums[i];

            // Check if complement already exists
            if (mp.find(required) != mp.end()) {
                return {mp[required], i};
            }

            // Store current number and its index
            mp[nums[i]] = i;
        }

        return {};
    }
};
