#ifndef HWTINYSTL_VECTOR_H_
#define HWTINYSTL_VECTOR_H_
/**
 * @File Name: vector.h
 * @Brief :  vector : 向量
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 *
 */
// 异常保证：
// mystl::vecotr<T> 满足基本异常保证，部分函数无异常保证，并对以下函数做强异常安全保证：
//   * emplace
//   * emplace_back
//   * push_back
// 当 std::is_nothrow_move_assignable<T>::value == true 时，以下函数也满足强异常保证：
//   * reserve
//   * resize
//   * insert

#include <initializer_list>

#include "iterator.h"
#include "memory.h"
#include "util.h"
#include "exceptdef.h"
namespace hwstl
{
#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

    // 模板类: vector
    // 模板参数 T 代表类型
    template <typename T>
    class vector
    {
        static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned in hwstl");

    public:
        // vector 的嵌套
        typedef hwstl::allocator<T> allocator_type;
        typedef hwstl::allocator<T> data_allocator;

        typedef typename allocator_type::value_type value_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

        //因为是连续空间，所以直接拿指针当迭代器
        typedef value_type *iterator;
        typedef const value_type *const_iterator;
        typedef hwstl::reverse_iterator<iterator> reverse_iterator;
        typedef hwstl::reverse_iterator<const iterator> const_reverse_iterator;

        allocator_type get_allocator() { return data_allocator(); }

    private:
        iterator begin_; //表示目前使用空间的头部
        iterator end_;   //表示目前使用空间的尾部
        iterator cap_;   //表示目前存储空间的尾部

    public:
        //构造、复制、移动、析构函数
        vector();
        ~vector();
    };

}
#endif