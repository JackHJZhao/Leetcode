#include <string>
#include <vector>
using namespace std;

class Solution {
    int cost(string s, int l, int r) {
        int ans = 0;
        while(l < r) {
            if (s[l] != s[r]) {
                ++ans;
            }
            ++l;
            --r;
        }
        return ans;
    }
public:
    int palindromePartition(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT32_MAX));       // [0, i-1] 分割为j个子串，使得每个子串是回文串需要修改的最小次数
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = cost(s, 0, i-1);       // 前i个字符分割为1个子串，需要修改的次数
            for (int j = 2; j <= std::min(i, k); ++j) {
                for (int t = j-1; t < i; ++t) {
                    // dp[t][j-1] 前t个分为j-1个字符串时，需要修改的次数
                    dp[i][j] = std::min(dp[i][j], dp[t][j-1] + cost(s, t, i-1));
                }
            }
        }
        return dp[n][k];
    }
};