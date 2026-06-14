#include <vector>
#include <unordered_set>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
128. 最长连续序列 (Longest Consecutive Sequence)
给定一个未排序的整数数组 nums，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例:
  输入: nums = [100,4,200,1,3,2]
  输出: 4
  解释: 最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
)";

// ========== 题解代码 ==========
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> nums_set;
        for (auto num : nums) {
            nums_set.insert(num);
        }
        int ans = 0;

        for (int num : nums_set) {
            if (!nums_set.count(num - 1)) {
                int cur_num = num;
                int count = 1;
                while(nums_set.count(cur_num + 1)) {
                    cur_num++;
                    count++;
                }
                ans = max(ans, count);
            }
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
    {{100,4,200,1,3,2}, 4},
    {{0,3,7,2,5,8,4,6,0,1}, 9},
    {{}, 0},
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
            int result = s.longestConsecutive(nums);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": nums = ";
            printVector(tc.nums);
            cout << " => " << result << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        auto nums = parseVector(argv[1]);
        int result = s.longestConsecutive(nums);
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
