#include <vector>
#include <iostream>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
11. 盛最多水的容器 (Container With Most Water)
给定一个长度为 n 的整数数组 height。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i])。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。

示例:
  输入: [1,8,6,2,5,4,8,3,7]
  输出: 49
)";

// ========== 题解代码 ==========
class Solution {
    int lower_bound(int target, vector<int> &index, vector<int> &nums) {
        int ans = nums.size();
        int i = 0, j = index.size();
        while(i < j) {
            int mid = i + (j - i) / 2;
            if (nums[index[mid]] >= target) {
                ans = index[mid];
                j = mid;
            } else {
                i = mid + 1;
            }
        }
        return ans;
    }

public:
    int maxArea(vector<int>& height) {
        if (height.size() == 2) {
            return std::min(height[0], height[1]);
        }
        vector<int> left;
        left.emplace_back(0);
        for (int i = 1; i < height.size(); ++i) {
            if (height[i] > height[left.back()]) {
                left.emplace_back(i);
            }
        }
        int ans = 0;
        vector<int> right;
        right.emplace_back(height.size() - 1);
        for (int i = height.size() - 1; i >= 0; --i) {
            int left_index = lower_bound(height[i], left, height);
            int right_index = lower_bound(height[i], right, height);
            left_index = std::min(left_index, i);
            if (right_index == height.size()) {
                right_index = i;
            }
            ans = std::max(ans, (right_index - left_index) * height[i]);
            if (height[i] > height[right.back()]) {
                right.emplace_back(i);
            }
        }
        return ans;
    }

    int maxArea2(vector<int> &nums) {
        int i = 0, j = nums.size() - 1;
        int ans = 0;
        while (i < j)
        {
            ans = std::max(ans, std::min(nums[i], nums[j]) * (j - i));
            if (nums[i] < nums[j]) {
                ++i;
            } else {
                --j;
            }
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
    {{1,8,6,2,5,4,8,3,7}, 49},
    {{1,1}, 1},
    {{4,3,2,1,4}, 16},
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
            int result = s.maxArea2(nums);
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
        int result = s.maxArea2(nums);
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
