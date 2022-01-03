# HWTinySTL
=====

## 简介
    模仿MyTinySTL的项目，基于 C++11 的 tinySTL，实现了大部分 STL 中的容器与函数。作为新手练习用途。
## 支持
* 操作系统
  * linux
  * windows
  * osx
* 编译器
  * g++ 5.4 或以上
  * clang++ 3.5 或以上
  * msvc 14.0 或以上

## 需要
  * 使用 cmake 2.8 来构建项目（**可选**）

## 运行
  * gcc/clang on linux/osx
  1. 克隆仓库
```bash
$ git clone git@github.com:Alinshans/MyTinySTL.git
$ cd MyTinySTL
```
  2. 构建并运行
```bash
$ mkdir build && cd build
$ cmake ..
$ make
$ cd ../bin && ./stltest
```



