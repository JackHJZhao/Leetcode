# Makefile - 兼容 macOS 和 Linux
# 编译所有 Leetcode 题解文件

# 自动检测操作系统
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX := g++
	CXXFLAGS := -std=c++17 -O2 -Wall
	LDFLAGS :=
endif
ifeq ($(UNAME_S),Darwin)
	CXX := clang++
	CXXFLAGS := -std=c++17 -O2 -Wall
	LDFLAGS :=
endif

# 目录
SRC_DIR := src
BIN_DIR := bin

# 自动查找所有 .cpp 源文件（排除 common.h）
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# 生成对应的目标文件名（去掉路径和扩展名）
TARGETS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SRCS))

# 确保 bin 目录存在
$(shell mkdir -p $(BIN_DIR))

# 默认目标：编译所有文件 + leetcode 启动器
.PHONY: all
all: $(TARGETS) leetcode

# 编译 leetcode 启动器
leetcode: main.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) main.cpp -o leetcode $(LDFLAGS)
	@echo "编译完成: leetcode"

# 编译单个源文件为可执行文件
$(BIN_DIR)/%: $(SRC_DIR)/%.cpp $(SRC_DIR)/common.h
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) $< -o $@ $(LDFLAGS)
	@echo "编译完成: $@"

# 编译特定文件（通过题号）
.PHONY: run
run:
	@echo "请使用 ./leetcode <题号> 来运行特定题目"

# 清理编译产物
.PHONY: clean
clean:
	rm -rf $(BIN_DIR)
	@echo "清理完成"

# 帮助信息
.PHONY: help
help:
	@echo "用法:"
	@echo "  make          - 编译所有题目"
	@echo "  make clean    - 清理编译产物"
	@echo "  make help     - 显示此帮助"
	@echo ""
	@echo "运行题目:"
	@echo "  ./leetcode <题号>              - 运行默认测试"
	@echo "  ./leetcode <题号> <输入参数>    - 指定测试输入"
	@echo "  ./leetcode help                - 显示帮助"

# 声明伪目标
.PHONY: all clean help run
