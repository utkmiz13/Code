
class Solution {
public:
    vector<string> below20 = {
        "", "One", "Two", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine", "Ten",
        "Eleven", "Twelve", "Thirteen", "Fourteen",
        "Fifteen", "Sixteen", "Seventeen", "Eighteen",
        "Nineteen"
    };

    vector<string> tens = {
        "", "", "Twenty", "Thirty", "Forty",
        "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
    };

    string helper(int num) {
        if (num == 0) return "";

        if (num < 20)
            return below20[num] + " ";

        if (num < 100)
            return tens[num / 10] + " " + helper(num % 10);

        return below20[num / 100] + " Hundred " + helper(num % 100);
    }

    string numberToWords(int num) {
        if (num == 0) return "Zero";

        vector<string> units = {
            "", "Thousand", "Million", "Billion"
        };

        string ans = "";
        int i = 0;

        while (num > 0) {
            int chunk = num % 1000;

            if (chunk != 0) {
                string part = helper(chunk);

                if (i > 0)
                    part += units[i] + " ";

                ans = part + ans;
            }

            num /= 1000;
            i++;
        }

        // Remove trailing space
        while (!ans.empty() && ans.back() == ' ')
            ans.pop_back();

        return ans;
    }
};
