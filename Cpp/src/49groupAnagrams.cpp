#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "common.h"
using namespace std;

// ========== 题目描述 ==========
static const char* PROBLEM_DESC = R"(
49. 字母异位词分组 (Group Anagrams)
给你一个字符串数组，请你将字母异位词组合在一起。可以按任意顺序返回结果列表。
字母异位词是由重新排列源单词的所有字母得到的一个新单词。

示例:
  输入: strs = ["eat","tea","tan","ate","nat","bat"]
  输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
)";

// ========== 题解代码 ==========
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, int> index_maps;
        for (auto s : strs) {
            string ss = s;
            std::sort(ss.begin(), ss.end());
            if (index_maps.find(ss) != index_maps.end()) {
                ans[index_maps[ss]].emplace_back(s);
            } else {
                ans.emplace_back(vector<string>{s});
                index_maps[ss] = ans.size() - 1;
            }
        }
        return ans;
    }
};

// ========== 默认测试用例 ==========
struct TestCase {
    vector<string> strs;
};

static TestCase DEFAULT_TESTS[] = {
    {{"eat","tea","tan","ate","nat","bat"}},
    {{""}},
    {{"a"}},
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
            auto strs = tc.strs;
            auto result = s.groupAnagrams(strs);
            cout << "测试 " << (i + 1) << ": strs = ";
            printVectorString(tc.strs);
            cout << " => ";
            printVector2DString(result);
            cout << endl;
        }
        return 0;
    }

    if (argc >= 2) {
        // 解析逗号分隔的字符串数组: "eat,tea,tan"
        vector<string> strs;
        string input = argv[1];
        stringstream ss(input);
        string token;
        while (getline(ss, token, ',')) {
            token = trim(token);
            token = parseString(token);
            if (!token.empty()) strs.push_back(token);
        }
        auto result = s.groupAnagrams(strs);
        cout << "输入: strs = ";
        printVectorString(strs);
        cout << endl;
        cout << "输出: ";
        printVector2DString(result);
        cout << endl;
    }

    return 0;
}
