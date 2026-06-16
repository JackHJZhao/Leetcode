#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
3. 无重复字符的最长子串 (Longest Substring Without Repeating Characters)
给定一个字符串 s，请你找出其中不含有重复字符的最长子串的长度。

示例:
  输入: s = "abcabcbb"
  输出: 3
  解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
)";

// ========== 题解代码 ==========
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        vector<int> last_index(128, -1);
        int ans = 0;
        int j = -1;
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            j = std::max(j, last_index[c]);
            ans = std::max(ans, i - j);
            last_index[c] = i;
        } 
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    string s;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {"abcabcbb", 3},
    {"bbbbb", 1},
    {"pwwkew", 3},
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
            int result = s.lengthOfLongestSubstring(tc.s);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": s = \"" << tc.s << "\" => " << result
                 << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        string input = parseString(argv[1]);
        int result = s.lengthOfLongestSubstring(input);
        cout << "输入: s = \"" << input << "\"" << endl;
        cout << "输出: " << result << endl;

        if (argc >= 3) {
            int expected = stoi(argv[2]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    }

    return 0;
}
