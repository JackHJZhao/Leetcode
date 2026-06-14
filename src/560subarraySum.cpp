#include <vector>
#include <unordered_map>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
560. 和为 K 的子数组 (Subarray Sum Equals K)
给你一个整数数组 nums 和一个整数 k，请你统计并返回该数组中和为 k 的子数组的个数。
子数组是数组中元素的连续非空序列。

示例:
  输入: nums = [1,1,1], k = 2
  输出: 2
)";

// ========== 题解代码 ==========
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> presum_cnt; 
        presum_cnt[0] = 1;
        int ans = 0;
        int presum = 0;
        for (auto num : nums) {
            presum += num;
            int t = presum - k;
            if (presum_cnt.find(t) != presum_cnt.end()) {
                ans += presum_cnt[t];
            }
            presum_cnt[presum]++;
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<int> nums;
    int k;
    int expected;
};

static TestCase DEFAULT_TESTS[] = {
    {{1,1,1}, 2, 2},
    {{1,2,3}, 3, 2},
    {{1}, 0, 0},
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
            int result = s.subarraySum(nums, tc.k);
            bool passed = testPassed(result, tc.expected);
            cout << "测试 " << (i + 1) << ": nums = ";
            printVector(tc.nums);
            cout << ", k = " << tc.k << " => " << result
                 << " (期望: " << tc.expected << ") [" << (passed ? "通过" : "失败") << "]" << endl;
        }
        return 0;
    }

    if (argc >= 3) {
        auto nums = parseVector(argv[1]);
        int k = stoi(argv[2]);
        int result = s.subarraySum(nums, k);
        cout << "输入: nums = ";
        printVector(nums);
        cout << ", k = " << k << endl;
        cout << "输出: " << result << endl;

        if (argc >= 4) {
            int expected = stoi(argv[3]);
            bool passed = testPassed(result, expected);
            cout << "期望: " << expected << " [" << (passed ? "通过" : "失败") << "]" << endl;
            return passed ? 0 : 1;
        }
    } else {
        cerr << "用法: " << argv[0] << " <数组> <k> [期望输出]" << endl;
        return 1;
    }

    return 0;
}
