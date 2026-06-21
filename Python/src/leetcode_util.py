#!/usr/bin/env python3

"""Leetcode 通用工具函数"""

from collections import Counter


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
    return Counter(a) == Counter(b)
