package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

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
