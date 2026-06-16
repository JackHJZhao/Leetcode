#!/usr/bin/env python3
"""
Leetcode 题解运行器（顶层入口）
支持多语言（Cpp / Go / Python），默认使用 Python。
运行时自动扫描对应语言的 src/ 目录，通过数字前缀匹配源文件。

用法:
  ./leetcode.py                                     - 显示帮助
  ./leetcode.py help                                - 显示帮助
  ./leetcode.py list [语言]                         - 列出题目
  ./leetcode.py <题号> [参数...]                    - 用默认语言运行
  ./leetcode.py -l <语言> <题号> [参数...]           - 用指定语言运行
  ./leetcode.py --lang <语言> <题号> [参数...]      - 同上

示例:
  ./leetcode.py 1                         - 用 Python 运行第1题
  ./leetcode.py -l cpp 42                 - 用 C++ 运行第42题
  ./leetcode.py list                      - 列出所有语言题目
  ./leetcode.py list cpp                  - 列出 C++ 题目
"""

import sys
import os
import subprocess

# ===================== 配置 =====================

DEFAULT_LANG = "python"

# 语言配置：dir=子目录, ext=源文件后缀, desc=描述
LANG_CONFIG = {
    "python": {"dir": "Python", "ext": ".py",  "desc": "Python"},
    "go":     {"dir": "Go",     "ext": ".go",  "desc": "Go（需编译）"},
    "cpp":    {"dir": "Cpp",    "ext": ".cpp", "desc": "C++（需编译）"},
}

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))

# ===================== 语言解析 =====================

def resolve_lang(raw: str) -> str:
    """解析语言名称，支持前缀和别名"""
    raw = raw.lower()
    if raw in LANG_CONFIG:
        return raw
    matches = [k for k in LANG_CONFIG if k.startswith(raw)]
    if len(matches) == 1:
        return matches[0]
    aliases = {"py": "python", "c++": "cpp"}
    if raw in aliases:
        return aliases[raw]
    return ""


def print_help():
    print(__doc__.strip())
    print()
    print("支持的语言:")
    for lang, cfg in LANG_CONFIG.items():
        print(f"  {lang:8s} - {cfg['desc']}")
    print(f"\n默认语言: {DEFAULT_LANG}")


def parse_args(args: list):
    """解析 -l/--lang 参数，返回 (lang, rest_args)"""
    lang = DEFAULT_LANG
    i = 0
    while i < len(args):
        if args[i] in ("-l", "--lang"):
            if i + 1 < len(args):
                parsed = resolve_lang(args[i + 1])
                if not parsed:
                    print(f"错误: 不支持的语言 '{args[i + 1]}'", file=sys.stderr)
                    print(f"支持: {', '.join(LANG_CONFIG.keys())}", file=sys.stderr)
                    sys.exit(1)
                lang = parsed
                i += 2
            else:
                print("错误: -l/--lang 需要一个参数", file=sys.stderr)
                sys.exit(1)
        else:
            return lang, args[i:]
    return lang, []


# ===================== src 扫描 =====================

def _extract_num_prefix(filename: str) -> str:
    """提取文件名开头的数字前缀，如 '1twoSum.cpp' -> '1', '3306countOfSubstrings.cpp' -> '3306'"""
    prefix = ""
    for ch in filename:
        if ch.isdigit():
            prefix += ch
        else:
            break
    return prefix


def scan_src(lang: str) -> list:
    """扫描 src/ 目录，返回 [(题号, 完整文件名), ...] 列表"""
    cfg = LANG_CONFIG[lang]
    src_dir = os.path.join(SCRIPT_DIR, cfg["dir"], "src")
    if not os.path.isdir(src_dir):
        return []
    results = []
    for f in sorted(os.listdir(src_dir)):
        if not f.endswith(cfg["ext"]):
            continue
        num = _extract_num_prefix(f)
        if num:
            results.append((num, f))
    return results


def find_source(lang: str, problem_num: str) -> str:
    """
    在 src/ 下精确匹配题号。
    精确匹配：文件名以题号开头，且下一个字符不是数字。
    例如 problem_num='1' 匹配 '1twoSum.cpp'，不匹配 '11maxArea.cpp'
    返回完整路径或空字符串。
    """
    cfg = LANG_CONFIG[lang]
    src_dir = os.path.join(SCRIPT_DIR, cfg["dir"], "src")
    if not os.path.isdir(src_dir):
        return ""
    for f in sorted(os.listdir(src_dir)):
        if not f.startswith(problem_num) or not f.endswith(cfg["ext"]):
            continue
        suffix = f[len(problem_num):]
        # 精确匹配：题号后面紧跟的不是数字
        if suffix and not suffix[0].isdigit():
            return os.path.join(src_dir, f)
    return ""


def list_problems(lang=None):
    """列出题目（可指定语言）"""
    langs = [lang] if lang else LANG_CONFIG.keys()
    for l in langs:
        cfg = LANG_CONFIG[l]
        problems = scan_src(l)
        if problems:
            print(f"\n--- {l.upper()} ({cfg['desc']}) ---")
            for num, name in problems:
                print(f"  {num:6s} - {name}")


# ===================== 编译 & 运行 =====================

def compile_if_needed(lang: str, problem_num: str) -> bool:
    """编译 C++/Go 源文件（时间戳比较，按需编译）"""
    cfg = LANG_CONFIG[lang]
    lang_dir = os.path.join(SCRIPT_DIR, cfg["dir"])

    if lang == "cpp":
        return _compile_cpp(lang_dir, problem_num)
    if lang == "go":
        return _compile_go(lang_dir, problem_num)
    return True


def _compile_cpp(lang_dir: str, problem_num: str) -> bool:
    src_path = find_source("cpp", problem_num)
    if not src_path:
        return True

    bin_name = os.path.splitext(os.path.basename(src_path))[0]
    bin_dir = os.path.join(lang_dir, "bin")
    bin_path = os.path.join(bin_dir, bin_name)
    common_h = os.path.join(lang_dir, "src", "common.h")

    need = (not os.path.exists(bin_path) or
            os.path.getmtime(src_path) > os.path.getmtime(bin_path))
    if not need and os.path.exists(common_h):
        need = os.path.getmtime(common_h) > os.path.getmtime(bin_path)
    if not need:
        return True

    print(f"[编译] cpp: {os.path.basename(src_path)} ...", end=" ", flush=True)
    os.makedirs(bin_dir, exist_ok=True)
    cxx = "clang++" if sys.platform == "darwin" else "g++"
    r = subprocess.run(
        [cxx, "-std=c++17", "-O2", "-Wall", "-Isrc", src_path, "-o", bin_path],
        cwd=lang_dir, capture_output=True, text=True)
    if r.returncode != 0:
        print("失败")
        print(r.stderr, file=sys.stderr)
        return False
    print("完成")
    return True


def _compile_go(lang_dir: str, problem_num: str) -> bool:
    src_path = find_source("go", problem_num)
    if not src_path:
        return True

    bin_name = os.path.splitext(os.path.basename(src_path))[0]
    bin_dir = os.path.join(lang_dir, "bin")
    bin_path = os.path.join(bin_dir, bin_name)

    if os.path.exists(bin_path) and os.path.getmtime(src_path) <= os.path.getmtime(bin_path):
        return True

    print(f"[编译] go: {os.path.basename(src_path)} ...", end=" ", flush=True)
    os.makedirs(bin_dir, exist_ok=True)
    r = subprocess.run(
        ["go", "build", "-o", bin_path, src_path],
        cwd=lang_dir, capture_output=True, text=True)
    if r.returncode != 0:
        print("失败")
        print(r.stderr, file=sys.stderr)
        return False
    print("完成")
    return True


def run_problem(lang: str, problem_num: str, extra_args: list) -> int:
    """直接运行题目源文件/二进制（不经过语言调度器）"""
    cfg = LANG_CONFIG[lang]
    lang_dir = os.path.join(SCRIPT_DIR, cfg["dir"])

    src_path = find_source(lang, problem_num)
    if not src_path:
        print(f"错误: 在 {lang}/src/ 中未找到题号为 '{problem_num}' 的源文件",
              file=sys.stderr)
        return 1

    # 编译型语言：先编译再运行
    if lang in ("cpp", "go"):
        if not compile_if_needed(lang, problem_num):
            return 1
        bin_name = os.path.splitext(os.path.basename(src_path))[0]
        bin_path = os.path.join(lang_dir, "bin", bin_name)
        r = subprocess.run([bin_path] + extra_args, cwd=lang_dir)
        return r.returncode

    # Python：直接运行
    r = subprocess.run([sys.executable, src_path] + extra_args, cwd=lang_dir)
    return r.returncode


# ===================== 主入口 =====================

def main():
    args = sys.argv[1:]

    if not args:
        print_help()
        return

    # help
    if args[0] in ("help", "--help", "-h"):
        if len(args) >= 2:
            lang = resolve_lang(args[1])
            if lang:
                list_problems(lang)
                return
        print_help()
        return

    # list
    if args[0] == "list":
        if len(args) >= 2 and resolve_lang(args[1]):
            list_problems(args[1])
        else:
            list_problems()
        return

    # 正常流程
    lang, rest = parse_args(args)
    if not rest:
        print_help()
        return

    problem_num = rest[0]
    sys.exit(run_problem(lang, problem_num, rest[1:]))


if __name__ == "__main__":
    main()
