#include <vector>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
1742. 盒子中小球的最大数量 (Maximum Number of Balls in a Box)
你在一家生产小球的玩具厂工作，有 n 个小球，编号从 lowLimit 开始，到 highLimit 结束
（包括 lowLimit 和 highLimit，即 n = highLimit - lowLimit + 1）。
另有无限数量的盒子，编号从 1 到无穷大。
你的工作是将每个小球放入盒子中，盒子的编号等于小球编号上每位数字的和。
给你两个整数 lowLimit 和 highLimit，返回放有最多小球的盒子中的小球数量。

示例:
  输入: lowLimit = 1, highLimit = 10
  输出: 2
)";

// ========== 题解代码 ==========
class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        int max_num = 0;
        std::vector<int> backet(46, 0);
        while (lowLimit <= highLimit)
        {
            int sum = 0;
            int num = lowLimit;
            while (num)
            {
                sum += num % 10;
                num /= 10;
            }
            backet[sum]++;
            if (backet[sum] > max_num)
            {
                max_num = backet[sum];
            }
            lowLimit++;
        }
        return max_num;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    int lowLimit;
    int highLimit;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {1, 10, 2},
    {5, 15, 2},
    {19, 28, 2},
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
            int result = s.countBalls(tc.lowLimit, tc.highLimit);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": lowLimit = " << tc.lowLimit
                 << ", highLimit = " << tc.highLimit << " => " << result
                 << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 3) {
        int low = stoi(argv[1]);
        int high = stoi(argv[2]);
        int result = s.countBalls(low, high);
        cout << "输入: lowLimit = " << low << ", highLimit = " << high << endl;
        cout << "输出: " << result << endl;

        if (argc >= 4) {
            int expected = stoi(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <lowLimit> <highLimit> [期望输出]" << endl;
        return 1;
    }

    return 0;
}
