#ifndef HWTINYSTL_MEMORY_H_
#define HWTINYSTL_MEMORY_H_
/**
 * @File Name: memory.h
 * @Brief : 更高级的动态内存管理
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-01-03
 * @State : finished 2022-01-13
 */

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "algobase.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"
namespace hwstl
{
    //获取对象地址
    template <typename Tp>
    inline constexpr Tp *addressof(Tp &value) noexcept
    {
        return &value;
    }

    //获取 释放 临时缓冲区
    template <typename T>
    inline pair<T *, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T *)
    {
        if ()
    }
}
#endif