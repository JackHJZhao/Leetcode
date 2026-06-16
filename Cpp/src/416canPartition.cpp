#include <vector>
#include <numeric>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
416. 分割等和子集 (Partition Equal Subset Sum)
给你一个只包含正整数的非空数组 nums。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

示例:
  输入: nums = [1,5,11,5]
  输出: true
  解释: 数组可以分割成 [1, 5, 5] 和 [11]。
)";

// ========== 题解代码 ==========
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = target; j >= nums[i]; j--) {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<int> nums;
    bool expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{1,5,11,5}, true},
    {{1,2,3,5}, false},
    {{2,2,3,5}, false},
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
            auto nums = tc.nums;
            bool result = s.canPartition(nums);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": nums = ";
            printVector(tc.nums);
            cout << " => ";
            printBool(result);
            cout << " (期望: ";
            printBool(tc.expected);
            cout << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        auto nums = parseVector(argv[1]);
        bool result = s.canPartition(nums);
        cout << "输入: nums = ";
        printVector(nums);
        cout << endl;
        cout << "输出: ";
        printBool(result);
        cout << endl;

        if (argc >= 3) {
            bool expected = (string(argv[2]) == "true" || string(argv[2]) == "1");
            bool passed = testPassed(result, expected);
            cout << "期望: ";
            printBool(expected);
            cout << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    }

    return 0;
}
