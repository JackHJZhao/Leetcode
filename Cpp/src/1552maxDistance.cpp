#include <vector>
#include <algorithm>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
1552. 两球之间的磁力 (Magnetic Force Between Two Balls)
在代号为 C-137 的地球上，Rick 发现如果他将两个球放在他新发明的篮子里，它们之间会形成特殊形式的磁力。
Rick 有 n 个空的篮子，第 i 个篮子的位置在 position[i]，Morty 想把 m 个球放到这些篮子里，
使得任意两球间的最小磁力最大。
已知两个球如果分别位于 x 和 y，那么它们之间的磁力为 |x - y|。
给你一个整数数组 position 和一个整数 m，请你返回最大化的最小磁力。

示例:
  输入: position = [1,2,3,4,7], m = 3
  输出: 3
)";

// ========== 题解代码 ==========
class Solution {
    bool check(vector<int>& position, int m, int mid) {
        int n = position.size();
        int pre = position[0];
        --m;
        for (int i = 1; i < n; ++i) {
            if (m == 0) {
                return true;
            }
            if (position[i] - pre >= mid) {
                --m;
                pre = position[i];
            }
        }
        return m == 0;
    }
public:
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        int left = 1, right = position.back() - position[0];
        int ans = 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if (check(position, m, mid)) {
                left = mid + 1;
                ans = mid;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<int> position;
    int m;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{1,2,3,4,7}, 3, 3},
    {{5,4,3,2,1,1000000000}, 2, 999999999},
    {{79,74,57,22}, 4, 5},
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
            auto pos = tc.position;
            int result = s.maxDistance(pos, tc.m);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": position = ";
            printVector(tc.position);
            cout << ", m = " << tc.m << " => " << result
                 << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 3) {
        auto position = parseVector(argv[1]);
        int m = stoi(argv[2]);
        int result = s.maxDistance(position, m);
        cout << "输入: position = ";
        printVector(position);
        cout << ", m = " << m << endl;
        cout << "输出: " << result << endl;

        if (argc >= 4) {
            int expected = stoi(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <数组> <m> [期望输出]" << endl;
        return 1;
    }

    return 0;
}
