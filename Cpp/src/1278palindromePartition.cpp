#include <string>
#include <vector>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
1278. 分割回文串 III (Palindrome Partitioning III)
给你一个由小写字母组成的字符串 s，和一个整数 k。
请你按下面的要求分割字符串：
- 首先，你可以将 s 中的部分字符修改为其他的小写英文字母。
- 接着，你需要把 s 分割成 k 个非空且不相交的子串，并且每个子串都是回文串。
请返回以这种方式分割字符串所需要修改的最少字符数。

示例:
  输入: s = "abc", k = 2
  输出: 1
  解释: 把 "abc" 分割成 "ab" 和 "c"，修改 1 个字符（将 'a' 改为 'b' 或将 'b' 改为 'a'）即可。
)";

// ========== 题解代码 ==========
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
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT32_MAX));
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = cost(s, 0, i-1);
            for (int j = 2; j <= std::min(i, k); ++j) {
                for (int t = j-1; t < i; ++t) {
                    dp[i][j] = std::min(dp[i][j], dp[t][j-1] + cost(s, t, i-1));
                }
            }
        }
        return dp[n][k];
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    string s;
    int k;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {"abc", 2, 1},
    {"aabbc", 3, 0},
    {"leetcode", 8, 0},
};

// ========== 主函数 ==========
int main(int argc, char* argv[]) {
    if (argc > 1 && (string(argv[1]) == "--help" || string(argv[1]) == "-h")) {
        cout << PROBLEM_DESC << endl;
        return 0;
    }

    Solution s;

    if (argc == 1) {
        cout << "=== 默认测试用例 ===" << endl;
        for (int i = 0; i < 3; ++i) {
            auto& tc = DEFAULT_TESTS[i];
            int result = s.palindromePartition(tc.s, tc.k);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": s = \"" << tc.s << "\", k = " << tc.k << " => " << result
                 << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 3) {
        string ss = parseString(argv[1]);
        int k = stoi(argv[2]);
        int result = s.palindromePartition(ss, k);
        cout << "输入: s = \"" << ss << "\", k = " << k << endl;
        cout << "输出: " << result << endl;

        if (argc >= 4) {
            int expected = stoi(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <字符串> <k> [期望输出]" << endl;
        return 1;
    }

    return 0;
}
