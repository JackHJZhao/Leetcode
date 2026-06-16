#!/usr/bin/env python3
"""
Leetcode 题解运行器 (Python)
用法:
  python3 main.py help                      - 显示帮助
  python3 main.py list                      - 列出所有题目
  python3 main.py <题号>                     - 运行指定题目的默认测试
  python3 main.py <题号> <参数...>           - 运行指定题目并传入参数
"""

import sys
import os
import subprocess


def extract_num_prefix(filename: str) -> str:
    """提取文件名开头的数字前缀，如 '1twoSum.py' -> '1'"""
    prefix = ""
    for ch in filename:
        if ch.isdigit():
            prefix += ch
        else:
            break
    return prefix


def scan_src() -> list:
    """扫描 src/ 目录，返回 [(题号, 文件名), ...] 列表"""
    src_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), "src")
    if not os.path.isdir(src_dir):
        return []
    results = []
    for f in sorted(os.listdir(src_dir)):
        if not f.endswith(".py"):
            continue
        num = extract_num_prefix(f)
        if num:
            results.append((num, f))
    return results


def find_problem(prefix: str) -> str:
    """
    在 src/ 中通过数字前缀精确匹配。
    精确匹配：文件名以题号开头，且下一个字符不是数字。
    返回完整文件名（不含 .py 扩展名），未找到返回空字符串。
    """
    problems = scan_src()
    # 精确匹配：num == prefix
    for num, fname in problems:
        if num == prefix:
            return fname[:-3]  # 去掉 .py
    # 前缀匹配（用户输入是 num 的前缀，且 num 下一个字符非数字）
    for num, fname in problems:
        if num.startswith(prefix):
            suffix = fname[len(prefix):]
            if suffix and suffix[0].isdigit():
                continue  # 例如 prefix='1' 不匹配 fname='11maxArea.py'
            return fname[:-3]
    return ""


def print_help():
    print("Leetcode 题解运行器 (Python)")
    print()
    print("用法:")
    print("  python3 main.py help                      - 显示此帮助")
    print("  python3 main.py list                      - 列出所有题目")
    print("  python3 main.py <题号>                     - 运行指定题目的默认测试")
    print("  python3 main.py <题号> <参数...>           - 运行指定题目并传入参数")
    print()
    print("示例:")
    print("  python3 main.py 1                         - 运行第1题")
    print("  python3 main.py 42                        - 运行第42题")
    print()
    print("题号支持精确数字前缀匹配")
    print()
    print("题目列表:")
    for num, name in scan_src():
        print(f"  {num} - {name}")


def list_problems():
    print("题目列表:")
    for num, name in scan_src():
        print(f"  {num} - {name}")


def run_script(name: str, args: list) -> int:
    script_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), "src")
    script_path = os.path.join(script_dir, name + ".py")
    if not os.path.exists(script_path):
        print(f"错误: 未找到脚本 {script_path}", file=sys.stderr)
        return 1
    result = subprocess.run([sys.executable, script_path] + args)
    return result.returncode


def main():
    if len(sys.argv) < 2:
        print_help()
        return

    arg1 = sys.argv[1]
    if arg1 in ("help", "--help", "-h"):
        print_help()
        return
    if arg1 in ("list", "-l"):
        list_problems()
        return

    problem_name = find_problem(arg1)
    if not problem_name:
        print(f"错误: 未找到匹配的题目 '{arg1}'", file=sys.stderr)
        print("使用 'python3 main.py list' 查看所有题目", file=sys.stderr)
        sys.exit(1)

    sys.exit(run_script(problem_name, sys.argv[2:]))


if __name__ == "__main__":
    main()
