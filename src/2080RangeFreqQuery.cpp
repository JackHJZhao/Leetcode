#include <vector>
#include <algorithm>
#include <unordered_map>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
2080. 区间内查询数字的频率 (Range Frequency Queries)
请你设计一个数据结构，它能求出给定子数组内一个给定值的频率。
实现 RangeFreqQuery 类：
- RangeFreqQuery(int[] arr) 用下标从 0 开始的整数数组 arr 构造一个类的实例。
- int query(int left, int right, int value) 返回子数组 arr[left...right] 中 value 的频率。

示例:
  输入: ["RangeFreqQuery","query","query"]
        [[[12,33,4,56,22,2,34,33,22,12,34,56]],[1,2,4],[0,11,33]]
  输出: [null,1,2]
)";

// ========== 题解代码 ==========
class RangeFreqQuery {
    unordered_map<int, vector<int>> index;
public:
    RangeFreqQuery(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n; ++i) {
            index[arr[i]].push_back(i);
        }
    }
    
    int query(int left, int right, int value) {
        auto &pos = index[value];
        auto it1 = lower_bound(pos.begin(), pos.end(), left);
        if (it1 == pos.end()) {
            return 0;
        }
        auto it2 = upper_bound(pos.begin(), pos.end(), right);
        return it2 - it1;
    }
};

// ========== 默认测试用例 ==========
// 使用 arr 和一系列 query 操作

// ========== 主函数 ==========
int main(int argc, char* argv[]) {
    if (argc > 1 && (string(argv[1]) == "--help" || string(argv[1]) == "-h")) {
        cout << PROBLEM_DESC << endl;
        return 0;
    }

    cout << "=== 默认测试用例 ===" << endl;
    vector<int> arr = {12,33,4,56,22,2,34,33,22,12,34,56};
    RangeFreqQuery rfq(arr);
    
    int result1 = rfq.query(1, 2, 4);
    cout << "query(1, 2, 4) => " << result1 << " (期望: 1) [" << (result1 == 1 ? "通过" : "失败") << "]" << endl;
    
    int result2 = rfq.query(0, 11, 33);
    cout << "query(0, 11, 33) => " << result2 << " (期望: 2) [" << (result2 == 2 ? "通过" : "失败") << "]" << endl;

    int result3 = rfq.query(0, 5, 100);
    cout << "query(0, 5, 100) => " << result3 << " (期望: 0) [" << (result3 == 0 ? "通过" : "失败") << "]" << endl;

    return 0;
}
