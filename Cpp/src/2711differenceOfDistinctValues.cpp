#include <vector>
#include <unordered_set>
#include <iostream>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
2711. 对角线上不同值的数量差 (Difference of Number of Distinct Values on Diagonals)
给你一个下标从 0 开始、大小为 m x n 的二维数组 grid，求解一个同样大小的二维数组 answer。
answer[i][j] = |左上对角线不同元素个数 - 右下对角线不同元素个数|。
左上对角线：从 (i, j) 开始往左上角方向的对角线。
右下对角线：从 (i, j) 开始往右下角方向的对角线。

示例:
  输入: grid = [[1,2,3],[3,1,5],[3,2,1]]
  输出: [[1,1,0],[1,0,1],[0,1,1]]
)";

// ========== 题解代码 ==========
class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));

        for (int t = m - 1; t >= 0; --t) {
            unordered_set<int> cnt;
            int i = t, j = 0;
            for ( ; i < m && j < n; ++i, ++j) {
                ans[i][j] = cnt.size();
                cnt.emplace(grid[i][j]);
            }

            --i;
            --j;
            cnt = unordered_set<int>();
            for ( ; j >= 0; --i, --j) {
                ans[i][j] = ans[i][j] > cnt.size() ? ans[i][j] - cnt.size() : cnt.size() - ans[i][j];
                cnt.emplace(grid[i][j]);
            }
        }

        for (int t = 1; t < n; ++t) {
            unordered_set<int> cnt;
            int i = 0, j = t;
            for (; i < m && j < n; ++i, ++j) {
                ans[i][j] = cnt.size();
                cnt.emplace(grid[i][j]);
            }
            --i;
            --j;
            cnt = unordered_set<int>();
            for ( ; i >= 0; --i, --j) {
                ans[i][j] = ans[i][j] > cnt.size() ? ans[i][j] - cnt.size() : cnt.size() - ans[i][j];
                cnt.emplace(grid[i][j]);
            }
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<vector<int>> grid;
    vector<vector<int>> expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{{1,2,3},{3,1,5},{3,2,1}}, {{1,1,0},{1,0,1},{0,1,1}}},
    {{{1}}, {{0}}},
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
        for (int i = 0; i < 2; ++i) {
            auto& tc = DEFAULT_TESTS[i];
            auto grid = tc.grid;
            auto result = s.differenceOfDistinctValues(grid);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": grid = ";
            printVector2D(tc.grid);
            cout << " => ";
            printVector2D(result);
            cout << " (期望: ";
            printVector2D(tc.expected);
            cout << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        auto grid = parseVector2D(argv[1]);
        auto result = s.differenceOfDistinctValues(grid);
        cout << "输入: grid = ";
        printVector2D(grid);
        cout << endl;
        cout << "输出: ";
        printVector2D(result);
        cout << endl;

        if (argc >= 3) {
            auto expected = parseVector2D(argv[2]);
            bool passed = testPassed(result, expected);
            cout << "期望: ";
            printVector2D(expected);
            cout << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    }

    return 0;
}
