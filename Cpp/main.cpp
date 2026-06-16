#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

// ===================== src 扫描 =====================

struct ProblemEntry {
    string num;   // 数字前缀
    string name;  // 不含扩展名的文件名（如 "1twoSum"）
    string fname; // 完整文件名（如 "1twoSum.cpp"）
};

// 扫描 src/ 目录，返回排序后的题目列表
static vector<ProblemEntry> scanSrc() {
    vector<ProblemEntry> results;
    DIR* dir = opendir("src");
    if (!dir) return results;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;
        // 只处理 .cpp 文件
        if (name.size() < 5 || name.substr(name.size() - 4) != ".cpp") {
            continue;
        }

        // 提取数字前缀
        string num;
        for (char c : name) {
            if (isdigit(c)) num += c;
            else break;
        }
        if (!num.empty()) {
            results.push_back({num, name.substr(0, name.size() - 4), name});
        }
    }
    closedir(dir);

    // 按数字前缀排序
    sort(results.begin(), results.end(),
         [](const ProblemEntry& a, const ProblemEntry& b) {
             if (a.num.size() != b.num.size()) return a.num.size() < b.num.size();
             return a.num < b.num;
         });
    return results;
}

// 在 src/ 中精确匹配题号
static string findProblem(const string& prefix) {
    auto problems = scanSrc();
    // 精确匹配：num == prefix
    for (const auto& p : problems) {
        if (p.num == prefix) return p.name;
    }
    // 前缀匹配：num 以 prefix 开头，且 num 的下一个字符非数字
    for (const auto& p : problems) {
        if (p.num.find(prefix) == 0) {
            string suffix = p.num.substr(prefix.size());
            if (!suffix.empty() && isdigit(suffix[0])) continue;
            return p.name;
        }
    }
    return "";
}

// ===================== 命令处理 =====================

static void printHelp() {
    auto problems = scanSrc();

    cout << "Leetcode 题解运行器 (C++)" << endl;
    cout << endl;
    cout << "用法:" << endl;
    cout << "  ./leetcode help                      - 显示此帮助" << endl;
    cout << "  ./leetcode list                      - 列出所有题目" << endl;
    cout << "  ./leetcode <题号>                     - 运行指定题目的默认测试用例" << endl;
    cout << "  ./leetcode <题号> <测试输入>           - 运行指定题目并传入测试输入" << endl;
    cout << "  ./leetcode <题号> <测试输入> <期望输出>  - 运行并比较输出结果" << endl;
    cout << endl;
    cout << "示例:" << endl;
    cout << "  ./leetcode 1                         - 运行第1题" << endl;
    cout << "  ./leetcode 1 \"[2,7,11,15]\" 9 \"[0,1]\" - 运行并验证输出" << endl;
    cout << "  ./leetcode 42                        - 运行第42题" << endl;
    cout << endl;
    cout << "题号支持精确数字前缀匹配" << endl;
    cout << endl;
    cout << "题目列表:" << endl;
    for (const auto& p : problems) {
        cout << "  " << p.num << " - " << p.name << endl;
    }
}

static void listProblems() {
    cout << "题目列表:" << endl;
    for (const auto& p : scanSrc()) {
        cout << "  " << p.num << " - " << p.name << endl;
    }
}

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
        execv(binPath.c_str(), execArgs.data());
        cerr << "错误: 无法执行 " << binPath << "，请先编译" << endl;
        exit(1);
    } else if (pid > 0) {
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

    if (arg1 == "help" || arg1 == "--help" || arg1 == "-h") {
        printHelp();
        return 0;
    }

    if (arg1 == "list" || arg1 == "-l") {
        listProblems();
        return 0;
    }

    string problemName = findProblem(arg1);
    if (problemName.empty()) {
        cerr << "错误: 未找到匹配的题目 '" << arg1 << "'" << endl;
        cerr << "使用 './leetcode list' 查看所有题目" << endl;
        return 1;
    }

    return runBinary(problemName, argc, argv, 2);
}