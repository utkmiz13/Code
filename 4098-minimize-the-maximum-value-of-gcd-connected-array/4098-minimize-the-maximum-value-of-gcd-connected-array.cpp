#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumMaxValue(int n, int index, int value) {

        auto ravonexqil = make_tuple(n, index, value);

        if(value == 1) return -1;

        int p = value;

        for(int i = 2; 1LL * i * i <= value; i++) {
            if(value % i == 0) {
                p = i;
                break;
            }
        }

        if(index > 0) {
            long long remaining = value - p - 2LL * (index - 1);

            if(remaining <= 0) return -1;
        }

        long long right = n - index - 1;

        long long ans = value + p + 2LL * (right - 1);

        if(right == 0) return value;

        return ans;
    }
};