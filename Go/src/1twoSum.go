package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

// ========== 题目描述 ==========
const problemDesc = `
1. 两数之和 (Two Sum)
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
你可以按任意顺序返回答案。

示例:
  输入: nums = [2,7,11,15], target = 9
  输出: [0,1]
`

// ========== 题解代码 ==========
func twoSum(nums []int, target int) []int {
	m := make(map[int]int)
	for i, v := range nums {
		t := target - v
		if j, ok := m[t]; ok {
			return []int{i, j}
		}
		m[v] = i
	}
	return []int{0, 0}
}

// ========== 工具函数 ==========

// 解析 Leetcode 风格的数组: "[1,2,3]" 或 "1,2,3" 或 "1 2 3"
func parseVector(s string) []int {
	s = strings.TrimSpace(s)
	s = strings.TrimPrefix(s, "[")
	s = strings.TrimSuffix(s, "]")

	var result []int
	parts := strings.FieldsFunc(s, func(r rune) bool {
		return r == ',' || r == ' '
	})
	for _, p := range parts {
		p = strings.TrimSpace(p)
		if p == "" {
			continue
		}
		v, err := strconv.Atoi(p)
		if err != nil {
			fmt.Fprintf(os.Stderr, "解析错误: 无法将 '%s' 转换为整数\n", p)
			os.Exit(1)
		}
		result = append(result, v)
	}
	return result
}

// 格式化输出 vector
func formatVector(v []int) string {
	parts := make([]string, len(v))
	for i, n := range v {
		parts[i] = strconv.Itoa(n)
	}
	return "[" + strings.Join(parts, ",") + "]"
}

// 比较两个 vector 是否相等
func vectorEqual(a, b []int) bool {
	if len(a) != len(b) {
		return false
	}
	// 由于题目允许任意顺序，使用 map 比较
	countA := make(map[int]int)
	countB := make(map[int]int)
	for _, v := range a {
		countA[v]++
	}
	for _, v := range b {
		countB[v]++
	}
	for k, v := range countA {
		if countB[k] != v {
			return false
		}
	}
	return true
}

// ========== 默认测试用例 ==========
type testCase struct {
	nums     []int
	target   int
	expected []int
}

var defaultTests = []testCase{
	{[]int{2, 7, 11, 15}, 9, []int{1, 0}},
	{[]int{3, 2, 4}, 6, []int{2, 1}},
	{[]int{3, 3}, 6, []int{1, 0}},
}

// ========== 主函数 ==========
func main() {
	if len(os.Args) > 1 && (os.Args[1] == "--help" || os.Args[1] == "-h") {
		fmt.Print(problemDesc)
		return
	}

	if len(os.Args) == 1 {
		// 运行默认测试用例
		fmt.Println("=== 默认测试用例 ===")
		for i, tc := range defaultTests {
			nums := make([]int, len(tc.nums))
			copy(nums, tc.nums)
			result := twoSum(nums, tc.target)
			passed := vectorEqual(result, tc.expected)
			status := "失败"
			if passed {
				status = "通过"
			}
			fmt.Printf("测试 %d: nums = %s, target = %d => %s (期望: %s) [%s]\n",
				i+1, formatVector(tc.nums), tc.target, formatVector(result), formatVector(tc.expected), status)
		}
		return
	}

	// 从命令行参数解析输入: <nums数组> <target> [期望输出]
	if len(os.Args) >= 3 {
		nums := parseVector(os.Args[1])
		target, err := strconv.Atoi(os.Args[2])
		if err != nil {
			fmt.Fprintf(os.Stderr, "错误: 无效的 target 值 '%s'\n", os.Args[2])
			os.Exit(1)
		}
		result := twoSum(nums, target)

		fmt.Printf("输入: nums = %s, target = %d\n", formatVector(nums), target)
		fmt.Printf("输出: %s\n", formatVector(result))

		if len(os.Args) >= 4 {
			expected := parseVector(os.Args[3])
			passed := vectorEqual(result, expected)
			status := "失败"
			if passed {
				status = "通过"
			}
			fmt.Printf("期望: %s [%s]\n", formatVector(expected), status)
			if !passed {
				os.Exit(1)
			}
		}
	} else {
		fmt.Fprintf(os.Stderr, "用法: %s <数组> <target> [期望输出]\n", os.Args[0])
		fmt.Fprintf(os.Stderr, "示例: %s \"[2,7,11,15]\" 9 \"[0,1]\"\n", os.Args[0])
		os.Exit(1)
	}
}
