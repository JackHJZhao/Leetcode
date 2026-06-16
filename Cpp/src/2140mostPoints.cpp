#include <vector>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
2140. 解决智力问题 (Solving Questions With Brainpower)
给你一个下标从 0 开始的二维整数数组 questions，其中 questions[i] = [pointsi, brainpoweri]。
这个数组表示一场考试里的一系列题目，你需要按顺序（也就是从下标 0 开始依次完成）完成所有题目，
但在完成每道题目时，你有两种选择：
- 解决这道题：获得 pointsi 分，但接下来 brainpoweri 道题不能做。
- 跳过这道题：不获得分数，直接进入下一题。
请你返回这场考试能获得的最高分数。

示例:
  输入: questions = [[3,2],[4,3],[4,4],[2,5]]
  输出: 5
)";

// ========== 题解代码 ==========
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            int points = questions[i][0];
            int brainpower = questions[i][1];
            int next = i + brainpower + 1;
            long long solve = points + (next < n ? dp[next] : 0);
            long long skip = dp[i + 1];
            dp[i] = max(solve, skip);
        }
        return dp[0];
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<vector<int>> questions;
    long long expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{{3,2},{4,3},{4,4},{2,5}}, 5},
    {{{1,1},{2,2},{3,3},{4,4},{5,5}}, 7},
    {{{21,2},{1,2},{12,5},{7,3},{14,4}}, 35},
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
            auto q = tc.questions;
            long long result = s.mostPoints(q);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": questions = ";
            printVector2D(tc.questions);
            cout << " => " << result << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        auto questions = parseVector2D(argv[1]);
        long long result = s.mostPoints(questions);
        cout << "输入: questions = ";
        printVector2D(questions);
        cout << endl;
        cout << "输出: " << result << endl;

        if (argc >= 3) {
            long long expected = stoll(argv[2]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    }

    return 0;
}
