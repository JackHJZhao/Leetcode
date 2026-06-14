#include <string>
#include <vector>
#include <iostream>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
3306. 元音辅音字符串计数 II (Count of Substrings Containing Every Vowel and K Consonants II)
给你一个字符串 word 和一个整数 k。
返回 word 的子字符串中，每个元音字母（'a'、'e'、'i'、'o'、'u'）至少出现一次，并且恰好包含 k 个辅音字母的子字符串数量。

示例:
  输入: word = "ieaouqqieaouqq", k = 1
  输出: 8
)";

// ========== 题解代码 ==========
class Solution {
public:
    long long countOfSubstrings(string s, int k) {
        long long ans = 0;
        int n = s.size();
        int aeiou_mask = (1 << ('a' - 'a')) + (1 << ('e' - 'a')) + (1 << ('i' - 'a')) + (1 << ('o' - 'a')) + (1 << ('u' - 'a'));
        int mask = 0;
        vector<int> aeiou_last(26, -1);
        int j = 0;
        int i = 0;
        int t = 0;
        int cur_k = 0;
        for (; i < n; ++i) {
            int idx = (s[i] - 'a');
            if ((aeiou_mask >> idx) & 0x01) {
                aeiou_last[idx] = i;
                mask |= (1 << idx);
                if (cur_k == k && mask == aeiou_mask) {
                    t = std::max(t, j);
                    for ( ; t < i; ++t) {
                        int index = (s[t] - 'a');
                        if (aeiou_last[index] == t || ((aeiou_mask >> index) & 0x01) == 0) {
                            break;
                        }
                    }
                    ans += (t - j + 1);
                }
            } else {
                cur_k++;
                if (cur_k > k) {
                    for ( ; j <= i; ++j) {
                        int index = (s[j] - 'a');
                        if (((aeiou_mask >> index) & 0x01) == 0) {
                            ++j;
                            --cur_k;
                            break;
                        }
                        if (aeiou_last[index] == j) {
                            mask &= (~ (1 << index));
                            aeiou_last[index] = -1;
                        }
                    }
                }
                if (cur_k == k && mask == aeiou_mask) {
                    t = std::max(t, j);
                    for (; t < i; ++t) {
                        int index = (s[t] - 'a');
                        if (aeiou_last[index] == t || ((aeiou_mask >> index) & 0x01) == 0) {
                            break;
                        }
                    }
                    ans += (t - j + 1);
                }
            }
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    string word;
    int k;
    long long expected;
};

static TestCase DEFAULT_TESTS[] = {
    {"ieaouqqieaouqq", 1, 8},
    {"aeiou", 0, 1},
    {"aeioqq", 1, 0},
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
            long long result = s.countOfSubstrings(tc.word, tc.k);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": word = \"" << tc.word << "\", k = " << tc.k
                 << " => " << result << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 3) {
        string word = parseString(argv[1]);
        int k = stoi(argv[2]);
        long long result = s.countOfSubstrings(word, k);
        cout << "输入: word = \"" << word << "\", k = " << k << endl;
        cout << "输出: " << result << endl;

        if (argc >= 4) {
            long long expected = stoll(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <word> <k> [期望输出]" << endl;
        return 1;
    }

    return 0;
}
