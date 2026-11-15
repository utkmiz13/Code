
class Solution {
public:
    vector<string> ans;

    void solve(string &num, int target, int index,
               long long curr, long long prev,
               string expr) {

        // Base case
        if (index == num.size()) {
            if (curr == target) {
                ans.push_back(expr);
            }
            return;
        }

        long long n = 0;

        // Generate all possible operands
        for (int i = index; i < num.size(); i++) {

            // Avoid leading zeros
            if (i > index && num[index] == '0')
                break;

            n = n * 10 + (num[i] - '0');

            string part = num.substr(index, i - index + 1);

            // First operand: no operator needed
            if (index == 0) {
                solve(num, target, i + 1,
                      n, n, part);
            }
            else {

                // Addition
                solve(num, target, i + 1,
                      curr + n, n,
                      expr + "+" + part);

                // Subtraction
                solve(num, target, i + 1,
                      curr - n, -n,
                      expr + "-" + part);

                // Multiplication
                solve(num, target, i + 1,
                      curr - prev + prev * n,
                      prev * n,
                      expr + "*" + part);
            }
        }
    }

    vector<string> addOperators(string num, int target) {
        ans.clear();

        solve(num, target, 0, 0, 0, "");

        return ans;
    }
};
