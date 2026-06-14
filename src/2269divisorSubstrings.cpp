#include <iostream>
#include <string>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
2269. 找到一个数字的 K 美丽值 (Find the K-Beauty of a Number)
一个整数 num 的 k 美丽值定义为 num 中符合以下条件的子字符串数目：
- 子字符串长度为 k。
- 子字符串能整除 num（即 num % 子字符串整数值 == 0）。
给你整数 num 和 k，请你返回 num 的 k 美丽值。

示例:
  输入: num = 240, k = 2
  输出: 2
  解释: 子字符串 "24" (24) 和 "40" (40) 都能整除 240。
)";

// ========== 题解代码 ==========
class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string s = std::to_string(num);
        int ans = 0;
        long long n = 0;
        long long m = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (i < k) {
                m *= 10;
                n *= 10;
                n += (s[i] - '0');
            } else {
                if (n != 0 && num % n == 0) {
                    ans++;
                }
                n *= 10;
                n += (s[i] - '0');
                n %= m;
            }
        }    
        if (n != 0 && num % n == 0) {
            ++ans;
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    int num;
    int k;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {240, 2, 2},
    {430043, 2, 2},
    {10, 1, 1},
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
            int result = s.divisorSubstrings(tc.num, tc.k);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": num = " << tc.num << ", k = " << tc.k
                 << " => " << result << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 3) {
        int num = stoi(argv[1]);
        int k = stoi(argv[2]);
        int result = s.divisorSubstrings(num, k);
        cout << "输入: num = " << num << ", k = " << k << endl;
        cout << "输出: " << result << endl;

        if (argc >= 4) {
            int expected = stoi(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <num> <k> [期望输出]" << endl;
        return 1;
    }

    return 0;
}
