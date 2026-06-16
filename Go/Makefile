# Makefile - Go Leetcode 题解（兼容 macOS 和 Linux）

# 自动检测操作系统
UNAME_S := $(shell uname -s)

# 目录
SRC_DIR := src
BIN_DIR := bin

# 自动查找所有 .go 源文件（排除 main.go）
SRCS := $(wildcard $(SRC_DIR)/*.go)
# 生成对应的目标文件名
TARGETS := $(patsubst $(SRC_DIR)/%.go,$(BIN_DIR)/%,$(SRCS))

# 确保 bin 目录存在
$(shell mkdir -p $(BIN_DIR))

# 默认目标
.PHONY: all
all: leetcode $(TARGETS)

# 编译调度器
leetcode: main.go
	go build -o $@ $<

# 编译单个源文件
$(BIN_DIR)/%: $(SRC_DIR)/%.go
	@mkdir -p $(BIN_DIR)
	go build -o $@ $<
	@echo "编译完成: $@"

# 清理
.PHONY: clean
clean:
	rm -rf $(BIN_DIR) leetcode
	@echo "清理完成"

# 帮助
.PHONY: help
help:
	@echo "用法:"
	@echo "  make          - 编译调度器和所有题目"
	@echo "  make clean    - 清理编译产物"
	@echo "  make help     - 显示此帮助"

.PHONY: all clean help
