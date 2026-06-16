package main

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"sort"
	"strings"
	"unicode"
)

// ===================== src 扫描 =====================

type problemEntry struct {
	num  string // 数字前缀
	name string // 完整文件名（如 "1twoSum.go"）
}

// extractNumPrefix 提取文件名开头的数字前缀
func extractNumPrefix(name string) string {
	var b strings.Builder
	for _, r := range name {
		if unicode.IsDigit(r) {
			b.WriteRune(r)
		} else {
			break
		}
	}
	return b.String()
}

// scanSrc 扫描 src/ 目录，返回排序后的题目列表
func scanSrc() []problemEntry {
	var results []problemEntry
	entries, err := os.ReadDir("src")
	if err != nil {
		return results
	}
	for _, e := range entries {
		name := e.Name()
		if strings.HasPrefix(name, ".") || !strings.HasSuffix(name, ".go") {
			continue
		}
		num := extractNumPrefix(name)
		if num != "" {
			results = append(results, problemEntry{num, name})
		}
	}
	sort.Slice(results, func(i, j int) bool {
		if len(results[i].num) != len(results[j].num) {
			return len(results[i].num) < len(results[j].num)
		}
		return results[i].num < results[j].num
	})
	return results
}

// findProblem 在 src/ 中精确匹配题号，返回不含扩展名的文件名
func findProblem(prefix string) string {
	problems := scanSrc()
	// 精确匹配：num == prefix
	for _, p := range problems {
		if p.num == prefix {
			return strings.TrimSuffix(p.name, ".go")
		}
	}
	// 前缀匹配：num 以 prefix 开头，且 num 的下一个字符非数字
	for _, p := range problems {
		if strings.HasPrefix(p.num, prefix) {
			suffix := p.num[len(prefix):]
			if suffix != "" && unicode.IsDigit(rune(suffix[0])) {
				continue
			}
			return strings.TrimSuffix(p.name, ".go")
		}
	}
	return ""
}

// ===================== 命令处理 =====================

func printHelp() {
	fmt.Println("Leetcode 题解运行器 (Go)")
	fmt.Println()
	fmt.Println("用法:")
	fmt.Println("  ./leetcode help                      - 显示此帮助")
	fmt.Println("  ./leetcode list                      - 列出所有题目")
	fmt.Println("  ./leetcode <题号>                     - 运行指定题目的默认测试")
	fmt.Println("  ./leetcode <题号> <参数...>           - 运行指定题目并传入参数")
	fmt.Println()
	fmt.Println("示例:")
	fmt.Println("  ./leetcode 1                         - 运行第1题")
	fmt.Println("  ./leetcode 42                        - 运行第42题")
	fmt.Println()
	fmt.Println("题号支持精确数字前缀匹配")
	fmt.Println()
	fmt.Println("题目列表:")
	for _, p := range scanSrc() {
		fmt.Printf("  %s - %s\n", p.num, p.name)
	}
}

func listProblems() {
	fmt.Println("题目列表:")
	for _, p := range scanSrc() {
		fmt.Printf("  %s - %s\n", p.num, p.name)
	}
}

func runBinary(name string, args []string) int {
	binPath := filepath.Join("bin", name)
	cmd := exec.Command(binPath, args...)
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	err := cmd.Run()
	if err != nil {
		fmt.Fprintf(os.Stderr, "错误: 无法执行 %s，请先编译\n", binPath)
		return 1
	}
	return cmd.ProcessState.ExitCode()
}

func main() {
	if len(os.Args) < 2 {
		printHelp()
		return
	}

	arg1 := os.Args[1]

	if arg1 == "help" || arg1 == "--help" || arg1 == "-h" {
		printHelp()
		return
	}

	if arg1 == "list" || arg1 == "-l" {
		listProblems()
		return
	}

	problemName := findProblem(arg1)
	if problemName == "" {
		fmt.Fprintf(os.Stderr, "错误: 未找到匹配的题目 '%s'\n", arg1)
		fmt.Fprintf(os.Stderr, "使用 './leetcode list' 查看所有题目\n")
		os.Exit(1)
	}

	os.Exit(runBinary(problemName, os.Args[2:]))
}
