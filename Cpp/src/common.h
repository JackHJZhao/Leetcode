#ifndef LEETCODE_COMMON_H
#define LEETCODE_COMMON_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

// ========== Leetcode 风格输入解析 ==========

// 去除字符串首尾空格
inline std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

// 解析 Leetcode 风格的数组: "[1,2,3]" 或 "1,2,3" 或 "1 2 3"
inline std::vector<int> parseVector(const std::string& s) {
    std::vector<int> result;
    std::string cleaned;
    for (char c : s) {
        if (c == '[' || c == ']') continue;
        cleaned += c;
    }
    std::stringstream ss(cleaned);
    std::string token;
    while (std::getline(ss, token, ',')) {
        token = trim(token);
        if (!token.empty()) {
            // 也支持空格分隔
            std::stringstream ts(token);
            std::string subtoken;
            while (ts >> subtoken) {
                if (!subtoken.empty()) {
                    result.push_back(std::stoi(subtoken));
                }
            }
        }
    }
    return result;
}

// 解析二维数组: "[[1,2],[3,4]]"
inline std::vector<std::vector<int>> parseVector2D(const std::string& s) {
    std::vector<std::vector<int>> result;
    std::string cleaned;
    bool inBracket = false;
    for (char c : s) {
        if (c == '[') {
            if (inBracket) cleaned += c;
            inBracket = true;
        } else if (c == ']') {
            if (cleaned.empty() || cleaned.back() != '[') {
                result.push_back(parseVector("[" + cleaned + "]"));
                cleaned.clear();
            }
            inBracket = false;
        } else {
            if (inBracket) cleaned += c;
        }
    }
    return result;
}

// 解析字符串输入（支持引号包裹或裸字符串）
inline std::string parseString(const std::string& s) {
    std::string t = trim(s);
    if (t.size() >= 2 && t.front() == '"' && t.back() == '"') {
        return t.substr(1, t.size() - 2);
    }
    return t;
}

// ========== Leetcode 风格输出格式化 ==========

// 输出 vector
inline void printVector(const std::vector<int>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ",";
        std::cout << v[i];
    }
    std::cout << "]";
}

// 输出 vector<string>
inline void printVectorString(const std::vector<std::string>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ",";
        std::cout << "\"" << v[i] << "\"";
    }
    std::cout << "]";
}

// 输出 vector<vector<int>>
inline void printVector2D(const std::vector<std::vector<int>>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ",";
        printVector(v[i]);
    }
    std::cout << "]";
}

// 输出 vector<vector<string>>
inline void printVector2DString(const std::vector<std::vector<std::string>>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ",";
        printVectorString(v[i]);
    }
    std::cout << "]";
}

// 输出 bool
inline void printBool(bool b) {
    std::cout << (b ? "true" : "false");
}

// ========== 测试框架 ==========

// 测试结果比较
inline bool testPassed(int actual, int expected) { return actual == expected; }
inline bool testPassed(long long actual, long long expected) { return actual == expected; }
inline bool testPassed(bool actual, bool expected) { return actual == expected; }
inline bool testPassed(const std::string& actual, const std::string& expected) { return actual == expected; }
inline bool testPassed(const std::vector<int>& actual, const std::vector<int>& expected) {
    return actual == expected;
}
inline bool testPassed(const std::vector<std::vector<int>>& actual, const std::vector<std::vector<int>>& expected) {
    return actual == expected;
}

// 打印测试结果
inline void printTestResult(int testNum, bool passed) {
    std::cout << "测试用例 " << testNum << ": " << (passed ? "通过" : "失败") << std::endl;
}

#endif // LEETCODE_COMMON_H
