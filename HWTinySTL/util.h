#ifndef HWTINYSTL_UTIL_H_
#define HWTINYSTL_UTIL_H_
// 这个文件包含一些通用工具，
// 包括 move, forward, swap 等函数，以及 pair 等
#include <cstddef>

#include "type_traits.h"

namespace hwstl
{
    // move
    template <class T>
    typename std::remove_reference<T>::type &&move(T &&arg) noexcept
    {
    }
    // forward

    // swap

    // pair
    // 结构体模板 : pair
    // 两个模板参数分别表示两个数据的类型
    // 用 first 和 second 来分别取出第一个数据和第二个数据
}

#endif