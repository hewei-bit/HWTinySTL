# HWTinySTL - C++ STL实现库

一个基于C++11标准实现的tinySTL库，仿照MyTinySTL项目，用于学习C++标准模板库的实现原理。

## 项目简介

HWTinySTL是一个从零实现的C++ STL（标准模板库），参考了MyTinySTL的设计思路。本项目旨在深入理解C++模板编程、内存管理、数据结构等核心概念，适合C++学习者和面试准备。

## 功能特性

### 已实现组件

#### 1. 容器 (Containers)
- ? **vector** - 动态数组
- ? **list** - 双向链表
- ? **deque** - 双端队列
- ? **queue** - 队列
- ? **stack** - 栈
- ? **map** - 有序映射 (基于红黑树)
- ? **set** - 有序集合 (基于红黑树)
- ? **unordered_map** - 哈希映射 (基于哈希表)
- ? **unordered_set** - 哈希集合 (基于哈希表)

#### 2. 算法 (Algorithms)
- ? **常用算法** - sort, find, count, equal等
- ? **数值算法** - accumulate, inner_product等
- ? **堆算法** - make_heap, push_heap, pop_heap等
- ? **集合算法** - set_union, set_intersection等

#### 3. 工具组件
- ? **allocator** - 空间配置器
- ? **iterator** - 迭代器
- ? **type_traits** - 类型萃取
- ? **functional** - 函数对象
- ? **utility** - 实用工具
- ? **memory** - 内存管理
- ? **string** - 字符串类

#### 4. 底层数据结构
- ? **rb_tree** - 红黑树
- ? **hash_table** - 哈希表

## 项目结构

```
HWTinySTL/
│
├── HWTinySTL/                      # STL实现源码
│   ├── 容器实现
│   │   ├── vector.h               # 动态数组
│   │   ├── list.h                 # 双向链表
│   │   ├── deque.h                # 双端队列
│   │   ├── queue.h                # 队列
│   │   ├── stack.h                # 栈
│   │   ├── map.h                  # 有序映射
│   │   ├── set.h                  # 有序集合
│   │   ├── unordered_map.h        # 哈希映射
│   │   └── unordered_set.h        # 哈希集合
│   │
│   ├── 算法实现
│   │   ├── algorithm.h            # 常用算法
│   │   ├── algo.h                 # 算法实现
│   │   ├── algobase.h             # 算法基础
│   │   ├── heap_algo.h            # 堆算法
│   │   ├── numeric.h              # 数值算法
│   │   └── set_algo.h             # 集合算法
│   │
│   ├── 工具组件
│   │   ├── allocator.h            # 空间配置器
│   │   ├── iterator.h             # 迭代器
│   │   ├── type_traits.h          # 类型萃取
│   │   ├── functional.h           # 函数对象
│   │   ├── util.h                 # 实用工具
│   │   ├── memory.h               # 内存管理
│   │   ├── construct.h            # 构造和析构
│   │   ├── uninitialized.h        # 未初始化内存
│   │   └── exceptdef.h            # 异常处理
│   │
│   ├── 字符串
│   │   ├── astring.h              # 字符串类
│   │   └── base_string.h          # 字符串基类
│   │
│   └── 数据结构
│       ├── rb_tree.h              # 红黑树
│       └── hash_table.h           # 哈希表
│
├── Test/                           # 测试代码
│   ├── test.cpp                    # 测试入口
│   ├── test.h                      # 测试工具
│   ├── vector_test.h               # vector测试
│   ├── list_test.h                 # list测试
│   ├── deque_test.h                # deque测试
│   ├── map_test.h                  # map测试
│   ├── set_test.h                  # set测试
│   ├── unordered_map_test.h        # unordered_map测试
│   ├── unordered_set_test.h        # unordered_set测试
│   ├── stack_test.h                # stack测试
│   ├── queue.h                     # queue测试
│   ├── algorithm_test.h            # 算法测试
│   ├── algorithm_platform_test.h   # 平台算法测试
│   ├── string_test.h               # 字符串测试
│   ├── Lib/                        # 测试库
│   └── CMakeLists.txt              # 测试项目构建文件
│
├── 容器类.png                       # 容器类图
├── CMakeLists.txt                   # 项目构建文件
└── README.md                        # 项目说明文档
```

## 支持的编译器

### 操作系统
- ? Linux
- ? Windows
- ? macOS (OS X)

### 编译器版本
- ? **GCC** - g++ 5.4 或更高版本
- ? **Clang** - clang++ 3.5 或更高版本
- ? **MSVC** - Visual Studio 2015 (14.0) 或更高版本

### C++标准
- 需要支持 **C++11** 或更高标准

## 编译与使用

### 方法一：使用CMake构建 (推荐)

```bash
# 1. 克隆仓库
git clone <repository-url>
cd HWTinySTL

# 2. 创建构建目录
mkdir build && cd build

# 3. 生成Makefile
cmake ..

# 4. 编译项目
make

# 5. 运行测试
cd ../bin && ./stltest
```

### 方法二：直接集成到项目

将 `HWTinySTL/` 目录复制到你的项目目录中，然后在代码中包含需要的头文件：

```cpp
#include "HWTinySTL/vector.h"
#include "HWTinySTL/map.h"
#include "HWTinySTL/algorithm.h"

int main() {
    HWTinySTL::vector<int> vec = {1, 2, 3, 4, 5};
    // 使用HWTinySTL的容器和算法
    return 0;
}
```

### 编译选项

确保编译器启用C++11支持：

```bash
# GCC/Clang
g++ -std=c++11 your_file.cpp

# MSVC
cl /EHsc /std:c++11 your_file.cpp
```

## 测试

项目包含完整的测试代码，位于 `Test/` 目录下。测试覆盖了所有主要组件：

### 运行测试

```bash
cd Test
mkdir build && cd build
cmake ..
make
./test
```

### 测试内容

- 容器功能测试 (vector, list, deque, map, set等)
- 算法功能测试 (sort, find, count等)
- 内存管理测试
- 迭代器测试
- 边界条件测试

## 代码风格

- 遵循STL的命名规范和设计模式
- 使用C++11新特性 (移动语义、右值引用、nullptr等)
- 清晰的代码注释
- 模块化的设计

## 学习路线

如果你想通过本项目学习C++，建议按照以下顺序：

1. **基础组件** - 先学习type_traits, iterator, allocator
2. **简单容器** - vector, list, deque
3. **配接器** - stack, queue
4. **关联容器** - map, set, unordered_map, unordered_set
5. **算法** - 从简单到复杂，学习常用算法的实现
6. **高级特性** - 红黑树、哈希表的实现原理

## 与原版STL的区别

- 本项目主要用于学习，不追求极致的性能优化
- 部分边缘特性可能未实现
- 错误信息可能不如原版STL详细
- 适合理解STL的实现原理和数据结构

## 参考资料

- 《STL源码剖析》 - 侯捷
- 《C++标准库》 - Nicolai M. Josuttis
- C++11/14/17标准文档
- GCC libstdc++ 源码
- LLVM libc++ 源码

## 项目特色

1. **教学导向** - 代码清晰，注释详细，适合学习
2. **现代C++** - 使用C++11新特性
3. **完整实现** - 涵盖STL主要组件
4. **跨平台** - 支持主流操作系统和编译器
5. **测试完善** - 提供完整的测试代码

## TODO

- [ ] 完善异常处理
- [ ] 增加更多算法实现
- [ ] 性能优化
- [ ] 增加使用示例
- [ ] 完善文档

## 许可证

本项目仅供学习交流使用。

## 贡献

欢迎提交Issue和Pull Request来改进本项目。

## 作者

hewei-bit

## 更新日志

- 2024 - 项目初始化
- 2024 - 完成主要容器和算法实现
- 2024 - 增加完整测试代码
