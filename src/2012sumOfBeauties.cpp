#include <vector>
#include <stack>
#include <iostream>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
2012. 数组美丽值求和 (Sum of Beauty in the Array)
给你一个下标从 0 开始的整数数组 nums。对于每个下标 i（1 <= i <= nums.length - 2），
nums[i] 的美丽值等于：
- 2，如果 nums[i] 严格大于 nums[i-1] 且严格小于 nums[i+1]，且 nums[i] 严格大于所有左边的元素，严格小于所有右边的元素
- 1，如果 nums[i-1] < nums[i] < nums[i+1]，且前面的条件不成立
- 0，如果以上条件都不成立
返回所有 nums[i] 的美丽值之和。

示例:
  输入: nums = [1,2,3]
  输出: 2
)";

// ========== 题解代码 ==========
class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        vector<int> right(n, 0);
        right[n-1] = nums[n-1];
        for (int i = n - 2; i >= 0; --i) {
            right[i] = std::min(nums[i], right[i+1]);
        }

        --n;
        int pre_max = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > pre_max && nums[i] < right[i+1]) {
                ans += 2;
            } else if (nums[i] > nums[i-1] && nums[i] < nums[i+1]) {
                ++ans;
            }
            pre_max = std::max(pre_max, nums[i]);
        }
        return ans;
    }

    int sumOfBeautiesStack(vector<int>& nums) {
        stack<int> stk;
        int n = nums.size();
        int ans = 0;
        int pre_max = nums[0];
        for (int i = 1; i < n; ++i) {
            while(!stk.empty() && nums[stk.top()] >= nums[i]) {
                int j = stk.top();
                if (nums[j - 1] < nums[j] && nums[j] < nums[j+1]) {
                    ans++;
                }
                stk.pop();
            }
            if (nums[i] > pre_max) {
                pre_max = nums[i];
                stk.push(i);
            } else {
                if (nums[i-1] < nums[i] && nums[i] < nums[i+1]) {
                    ans++;
                }
            }
        }
        ans += stk.size() * 2;
        if (!stk.empty() && stk.top() == n - 1) {
            ans -= 2;
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<int> nums;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{1,2,3}, 2},
    {{2,4,6,4}, 1},
    {{3,2,1}, 0},
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
            int result = s.sumOfBeauties(nums);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": nums = ";
            printVector(tc.nums);
            cout << " => " << result << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        auto nums = parseVector(argv[1]);
        int result = s.sumOfBeauties(nums);
        cout << "输入: nums = ";
        printVector(nums);
        cout << endl;
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
