#!/usr/bin/env python3

# ========== 题目描述 ==========
PROBLEM_DESC = """
1. 两数之和 (Two Sum)
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
你可以按任意顺序返回答案。

示例:
  输入: nums = [2,7,11,15], target = 9
  输出: [0,1]
"""

# ========== 题解代码 ==========
class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        m = {}
        for i, v in enumerate(nums):
            t = target - v
            if t in m:
                return [i, m[t]]
            m[v] = i
        return [0, 0]


# ========== 工具函数 ==========
def parse_vector(s: str) -> list[int]:
    """解析 Leetcode 风格的数组: '[1,2,3]' 或 '1,2,3' 或 '1 2 3'"""
    s = s.strip().lstrip("[").rstrip("]")
    if not s:
        return []
    parts = s.replace(",", " ").split()
    return [int(p) for p in parts]


def format_vector(v: list[int]) -> str:
    """格式化输出数组"""
    return "[" + ",".join(str(x) for x in v) + "]"


def vector_equal(a: list[int], b: list[int]) -> bool:
    """比较两个数组是否相等（允许任意顺序）"""
    from collections import Counter
    return Counter(a) == Counter(b)


# ========== 默认测试用例 ==========
DEFAULT_TESTS = [
    {"nums": [2, 7, 11, 15], "target": 9, "expected": [1, 0]},
    {"nums": [3, 2, 4], "target": 6, "expected": [2, 1]},
    {"nums": [3, 3], "target": 6, "expected": [1, 0]},
]


# ========== 主函数 ==========
def main():
    import sys

    if len(sys.argv) > 1 and sys.argv[1] in ("--help", "-h"):
        print(PROBLEM_DESC)
        return

    s = Solution()

    if len(sys.argv) == 1:
        # 运行默认测试用例
        print("=== 默认测试用例 ===")
        for i, tc in enumerate(DEFAULT_TESTS):
            result = s.twoSum(tc["nums"], tc["target"])
            passed = vector_equal(result, tc["expected"])
            status = "通过" if passed else "失败"
            print(f"测试 {i + 1}: nums = {format_vector(tc['nums'])}, "
                  f"target = {tc['target']} => {format_vector(result)} "
                  f"(期望: {format_vector(tc['expected'])}) [{status}]")
        return

    # 从命令行参数解析输入: <nums数组> <target> [期望输出]
    if len(sys.argv) >= 3:
        nums = parse_vector(sys.argv[1])
        target = int(sys.argv[2])
        result = s.twoSum(nums, target)

        print(f"输入: nums = {format_vector(nums)}, target = {target}")
        print(f"输出: {format_vector(result)}")

        if len(sys.argv) >= 4:
            expected = parse_vector(sys.argv[3])
            passed = vector_equal(result, expected)
            status = "通过" if passed else "失败"
            print(f"期望: {format_vector(expected)} [{status}]")
            sys.exit(0 if passed else 1)
    else:
        print(f"用法: {sys.argv[0]} <数组> <target> [期望输出]", file=sys.stderr)
        print(f"示例: {sys.argv[0]} \"[2,7,11,15]\" 9 \"[0,1]\"", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
