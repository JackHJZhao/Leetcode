#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
using namespace std;

// 题目文件映射表（文件名前缀 -> 完整文件名）
// 使用数字前缀作为key
static map<string, string> PROBLEM_MAP = {
    {"1", "1twoSum"},
    {"3", "3lengthOfLongestSubstring"},
    {"11", "11maxArea"},
    {"15", "15threeSum"},
    {"42", "42trap"},
    {"49", "49groupAnagrams"},
    {"128", "128longestConsecutive"},
    {"416", "416canPartition"},
    {"438", "438findAnagrams"},
    {"560", "560subarraySum"},
    {"1278", "1278palindromePartition"},
    {"1552", "1552maxDistance"},
    {"1742", "1742countBalls"},
    {"2012", "2012sumOfBeauties"},
    {"2080", "2080RangeFreqQuery"},
    {"2140", "2140mostPoints"},
    {"2269", "2269divisorSubstrings"},
    {"2711", "2711differenceOfDistinctValues"},
    {"2829", "2829minimumSum"},
    {"3306", "3306countOfSubstrings"},
};

// 最长前缀匹配：找到匹配的题目
static string findProblem(const string& prefix) {
    // 1. 优先精确匹配
    auto it = PROBLEM_MAP.find(prefix);
    if (it != PROBLEM_MAP.end()) {
        return it->second;
    }

    // 2. 最长前缀匹配：用户输入是 key 的前缀（从短到长优先匹配更长的 key）
    string bestMatch;
    for (const auto& kv : PROBLEM_MAP) {
        const string& key = kv.first;
        if (key.find(prefix) == 0) {
            // 用户输入是 key 的前缀，选最长匹配的 key
            if (key.size() > bestMatch.size()) {
                bestMatch = key;
            }
        }
    }
    if (!bestMatch.empty()) {
        return PROBLEM_MAP[bestMatch];
    }

    // 3. 回退：key 是用户输入的前缀（用于用户输入了更长的数字，但只部分匹配）
    for (const auto& kv : PROBLEM_MAP) {
        const string& key = kv.first;
        if (prefix.find(key) == 0) {
            if (key.size() > bestMatch.size()) {
                bestMatch = key;
            }
        }
    }
    return bestMatch.empty() ? "" : PROBLEM_MAP[bestMatch];
}

// 打印帮助信息
static void printHelp() {
    cout << "Leetcode 题解运行器" << endl;
    cout << endl;
    cout << "用法:" << endl;
    cout << "  ./leetcode help                      - 显示此帮助" << endl;
    cout << "  ./leetcode list                      - 列出所有题目" << endl;
    cout << "  ./leetcode <题号>                     - 运行指定题目的默认测试用例" << endl;
    cout << "  ./leetcode <题号> <测试输入>           - 运行指定题目并传入测试输入" << endl;
    cout << "  ./leetcode <题号> <测试输入> <期望输出>  - 运行并比较输出结果" << endl;
    cout << endl;
    cout << "示例:" << endl;
    cout << "  ./leetcode 1                         - 运行第1题（两数之和）默认测试" << endl;
    cout << "  ./leetcode 1 \"[2,7,11,15] 9\"        - 用自定义输入运行第1题" << endl;
    cout << "  ./leetcode 1 \"[2,7,11,15] 9\" \"[0,1]\" - 运行并验证输出" << endl;
    cout << "  ./leetcode 42                        - 运行第42题（接雨水）默认测试" << endl;
    cout << endl;
    cout << "题号支持最长前缀匹配，输入'1'可匹配'1twoSum'，输入'15'可匹配'15threeSum'" << endl;
    cout << endl;
    cout << "题目列表:" << endl;
    for (const auto& kv : PROBLEM_MAP) {
        cout << "  " << kv.first << " - " << kv.second << endl;
    }
}

// 列出所有题目
static void listProblems() {
    cout << "题目列表:" << endl;
    for (const auto& kv : PROBLEM_MAP) {
        cout << "  " << kv.first << " - " << kv.second << endl;
    }
}

// 运行指定的二进制文件
static int runBinary(const string& name, int argc, char* argv[], int startIdx) {
    string binPath = "./bin/" + name;
    
    // 构建参数列表
    vector<char*> execArgs;
    execArgs.push_back(const_cast<char*>(name.c_str()));
    for (int i = startIdx; i < argc; ++i) {
        execArgs.push_back(argv[i]);
    }
    execArgs.push_back(nullptr);

    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        execv(binPath.c_str(), execArgs.data());
        // execv 失败
        cerr << "错误: 无法执行 " << binPath << "，请先运行 'make' 编译" << endl;
        exit(1);
    } else if (pid > 0) {
        // 父进程
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    } else {
        cerr << "错误: fork 失败" << endl;
        return 1;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 0;
    }

    string arg1 = argv[1];

    // 帮助命令
    if (arg1 == "help" || arg1 == "--help" || arg1 == "-h") {
        printHelp();
        return 0;
    }

    // 列出题目
    if (arg1 == "list" || arg1 == "-l") {
        listProblems();
        return 0;
    }

    // 查找题目
    string problemName = findProblem(arg1);
    if (problemName.empty()) {
        cerr << "错误: 未找到匹配的题目 '" << arg1 << "'" << endl;
        cerr << "使用 './leetcode list' 查看所有题目" << endl;
        return 1;
    }

    // 运行题目
    return runBinary(problemName, argc, argv, 2);
}