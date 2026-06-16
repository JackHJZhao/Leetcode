#include <vector>
#include <algorithm>
#include <iostream>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
15. 三数之和 (3Sum)
给你一个整数数组 nums，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k，
同时还满足 nums[i] + nums[j] + nums[k] == 0。请你返回所有和为 0 且不重复的三元组。

示例:
  输入: nums = [-1,0,1,2,-1,-4]
  输出: [[-1,-1,2],[-1,0,1]]
)";

// ========== 题解代码 ==========
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int j = i + 1;
            while(j < n) {
                int target = nums[i] + nums[j];
                if (target <= 0) {
                    int k = std::lower_bound(nums.begin() + j + 1, nums.end(), -target) - nums.begin(); 
                    if (k < n && nums[k] == -target) {
                        ans.emplace_back(vector<int>{nums[i], nums[j], nums[k]});
                    }
                }
                ++j;
                while (j < n && nums[j] == nums[j-1]) {
                    ++j;
                }
            }
        }
        return ans;
    }

    vector<vector<int>> threeSum_pointer(vector<int>& nums) {
        vector<vector<int>> ans;
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int k = 0; k < n; ++k) {
            if (k > 0 && nums[k] == nums[k-1]) {
                continue;
            }
            int i = k + 1, j = n - 1;
            int target = -nums[k];
            while (i < j)
            {
                int sum = nums[i] + nums[j];
                if (sum == target) {
                    ans.emplace_back(vector<int>{nums[k], nums[i], nums[j]});
                    ++i;
                    --j;
                    while(i < j && nums[i] == nums[i-1]) {
                        ++i;
                    }
                    while(i < j && nums[j] == nums[j+1]) {
                        --j;
                    }
                } else if (sum > target) {
                    --j;
                } else {
                    ++i;
                }
            } 
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<int> nums;
    vector<vector<int>> expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{-1,0,1,2,-1,-4}, {{-1,-1,2},{-1,0,1}}},
    {{0,1,1}, {}},
    {{0,0,0}, {{0,0,0}}},
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
            auto result = s.threeSum_pointer(nums);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": nums = ";
            printVector(tc.nums);
            cout << " => ";
            printVector2D(result);
            cout << " (期望: ";
            printVector2D(tc.expected);
            cout << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        auto nums = parseVector(argv[1]);
        auto result = s.threeSum_pointer(nums);
        cout << "输入: nums = ";
        printVector(nums);
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
