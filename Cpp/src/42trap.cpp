#include <vector>
#include <stack>
#include <iostream>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
42. 接雨水 (Trapping Rain Water)
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例:
  输入: height = [0,1,0,2,1,0,1,3,2,1,2,1]
  输出: 6
)";

// ========== 题解代码 ==========
class Solution {
public:
    int trap(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        vector<int> right(n);
        stack<int> stk;
        right[n-1] = n;
        stk.push(n-1);
        for (int i = n - 2; i >= 0; --i) {
            while(!stk.empty() && nums[stk.top()] <= nums[i]) {
                stk.pop();
            }
            if (stk.empty()) {
                right[i] = n;
            } else {
                right[i] = stk.top();
            }
            stk.push(i);
        }

        auto &left = stk;
        left = stack<int>();
        for (int i = 0; i < n; ++i) {
            while(!left.empty() && nums[left.top()] < nums[i]) {
                left.pop();
            }
            if (left.empty() || nums[left.top()] == nums[i]) {
                left.push(i);
            } else {
                if (right[i] < n) {
                    ans += (min(nums[left.top()], nums[right[i]]) - nums[i]) * (right[i] - left.top() - 1);
                }
                left.push(i);
            }
        }
        return ans;
    }

    int trapdp(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        vector<int> leftMax(n);
        leftMax[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = std::max(nums[i], leftMax[i-1]);
        }
        int rightMax = nums[n-1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax = std::max(rightMax, nums[i]);
            ans += (std::min(leftMax[i], rightMax) - nums[i]);
        }
        return ans;
    }

    int trapstk(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        stack<int> stk;
        stk.push(0);
        for(int i = 1; i < n; ++i) {
            while(!stk.empty() && nums[stk.top()] < nums[i]) {
                int top = stk.top();
                stk.pop();
                if(stk.empty()) {
                    break;
                }
                int left = stk.top();
                ans += (std::min(nums[left], nums[i]) - nums[top]) * (i - left - 1);
            }
            stk.push(i);
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<int> height;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{0,1,0,2,1,0,1,3,2,1,2,1}, 6},
    {{4,2,0,3,2,5}, 9},
    {{5,2,1,2,1,5}, 14},
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
            auto nums = tc.height;
            int result = s.trapstk(nums);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": height = ";
            printVector(tc.height);
            cout << " => " << result << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        auto height = parseVector(argv[1]);
        auto nums = height;
        int result = s.trapstk(nums);
        cout << "输入: height = ";
        printVector(height);
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
