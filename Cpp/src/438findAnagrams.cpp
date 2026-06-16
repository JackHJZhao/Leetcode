#include <vector>
#include <string>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
438. 找到字符串中所有字母异位词 (Find All Anagrams in a String)
给定两个字符串 s 和 p，找到 s 中所有 p 的异位词的子串，返回这些子串的起始索引。
不考虑答案输出的顺序。

示例:
  输入: s = "cbaebabacd", p = "abc"
  输出: [0,6]
)";

// ========== 题解代码 ==========
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int m = s.size(), n = p.size();
        if (m < n) {
            return vector<int>();
        }
        vector<int> pchar(26, 0);
        for (auto c : p) {
            pchar[c - 'a']++;
        }

        vector<int> schar(26, 0);
        for (int i = 0; i < n; ++i) {
            schar[s[i] - 'a']++;
        }

        vector<int> ans;
        int i = n;
        do {
            if (schar == pchar) {
                ans.emplace_back(i - n);
            }
            if (i == m) {
                break;
            }
            schar[s[i-n] - 'a']--;
            schar[s[i] - 'a']++;
            ++i;
        } while(true);
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    string s;
    string p;
    vector<int> expected;
};

static TestCase DEFAULT_TESTS[] = {
    {"cbaebabacd", "abc", {0, 6}},
    {"abab", "ab", {0, 1, 2}},
    {"aaaaaaaaaa", "aaaaaaaaaaaaa", {}},
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
            auto result = s.findAnagrams(tc.s, tc.p);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": s = \"" << tc.s << "\", p = \"" << tc.p << "\" => ";
            printVector(result);
            cout << " (期望: ";
            printVector(tc.expected);
            cout << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 3) {
        string ss = parseString(argv[1]);
        string pp = parseString(argv[2]);
        auto result = s.findAnagrams(ss, pp);
        cout << "输入: s = \"" << ss << "\", p = \"" << pp << "\"" << endl;
        cout << "输出: ";
        printVector(result);
        cout << endl;

        if (argc >= 4) {
            auto expected = parseVector(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: ";
            printVector(expected);
            cout << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <s> <p> [期望输出]" << endl;
        return 1;
    }

    return 0;
}
