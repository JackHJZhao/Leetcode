#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
1. 两数之和 (Two Sum)
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
你可以按任意顺序返回答案。

示例:
  输入: nums = [2,7,11,15], target = 9
  输出: [0,1]
)";

// ========== 题解代码 ==========
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); ++i) {
            int t = target - nums[i];
            if (m.find(t) != m.end()) {
                return {i, m[t]};
            }
            m[nums[i]] = i;
        }
        return {0, 0};
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<int> nums;
    int target;
    vector<int> expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{2, 7, 11, 15}, 9, {1, 0}},
    {{3, 2, 4}, 6, {2, 1}},
    {{3, 3}, 6, {1, 0}},
};

// ========== 主函数 ==========
int main(int argc, char* argv[]) {
    if (argc > 1 && (string(argv[1]) == "--help" || string(argv[1]) == "-h")) {
        cout << PROBLEM_DESC << endl;
        return 0;
    }

    Solution s;

    if (argc == 1) {
        // 运行默认测试用例
        cout << "=== 默认测试用例 ===" << endl;
        for (int i = 0; i < 3; ++i) {
            auto& tc = DEFAULT_TESTS[i];
            auto nums = tc.nums;
            auto result = s.twoSum(nums, tc.target);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": nums = ";
            printVector(tc.nums);
            cout << ", target = " << tc.target;
            cout << " => ";
            printVector(result);
            cout << " (期望: ";
            printVector(tc.expected);
            cout << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    // 从命令行参数解析输入: <nums数组> <target> [期望输出]
    if (argc >= 3) {
        vector<int> nums = parseVector(argv[1]);
        int target = stoi(argv[2]);
        auto result = s.twoSum(nums, target);

        cout << "输入: nums = ";
        printVector(nums);
        cout << ", target = " << target << endl;
        cout << "输出: ";
        printVector(result);
        cout << endl;

        if (argc >= 4) {
            vector<int> expected = parseVector(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: ";
            printVector(expected);
            cout << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <数组> <target> [期望输出]" << endl;
        cerr << "示例: " << argv[0] << " \"[2,7,11,15]\" 9 \"[0,1]\"" << endl;
        return 1;
    }

    return 0;
}
