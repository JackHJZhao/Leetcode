#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
2829. k-avoiding 数组的最小总和 (Determine the Minimum Sum of a k-avoiding Array)
给你两个整数 n 和 k。
对于一个由不同正整数组成的数组，如果不存在任何一对元素之和等于 k，则称为 k-avoiding 数组。
返回长度为 n 的 k-avoiding 数组可能的最小总和。

示例:
  输入: n = 5, k = 4
  输出: 18
  解释: 数组 [1,2,4,5,6] 是最小的 k-avoiding 数组，和为 18。
)";

// ========== 题解代码 ==========
class Solution {
public:
    int minimumSum(int n, int k) {
        if (n <= k / 2) {
            return arithmeticSeriesSum(1, 1, n);
        } else {
            return arithmeticSeriesSum(1, 1, k / 2) + arithmeticSeriesSum(k, 1, n - k / 2);
        }
    }

private:
    int arithmeticSeriesSum(int a1, int d, int n) {
        return (a1 + a1 + (n - 1) * d) * n / 2;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    int n;
    int k;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {5, 4, 18},
    {2, 6, 3},
    {1, 1, 1},
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
            int result = s.minimumSum(tc.n, tc.k);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": n = " << tc.n << ", k = " << tc.k
                 << " => " << result << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 3) {
        int n = stoi(argv[1]);
        int k = stoi(argv[2]);
        int result = s.minimumSum(n, k);
        cout << "输入: n = " << n << ", k = " << k << endl;
        cout << "输出: " << result << endl;

        if (argc >= 4) {
            int expected = stoi(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <n> <k> [期望输出]" << endl;
        return 1;
    }

    return 0;
}
