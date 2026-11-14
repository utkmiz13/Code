
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_set<string> seen;
        unordered_set<string> repeated;
        
        for (int i = 0; i + 10 <= s.length(); i++) {
            string sub = s.substr(i, 10);
            
            if (seen.find(sub) != seen.end()) {
                repeated.insert(sub);
            } 
            else {
                seen.insert(sub);
            }
        }
        
        return vector<string>(repeated.begin(), repeated.end());
    }
};
