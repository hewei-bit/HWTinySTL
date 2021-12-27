/**
 * @File Name: iterator.h
 * @Brief : 用于迭代器设计，包含了一些模板结构体与全局函数，
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 *
 */
#ifndef HWTINYSTL_ITERATOR_H_
#define HWTINYSTL_ITERATOR_H_
#include <cstddef>

#include "type_traits.h"
namespace hwstl
{
    //五种迭代器:
    //输入迭代器
    struct input_iterator_tag
    {
    };
    //输出迭代器
    struct output_iterator_tag
    {
    };
    //正向迭代器
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    //双向迭代器
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };
    //随机访问迭代器
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };

    // iterator 模板
    template <typename Category, typename T, typename Distance = ptrdiff_t,
              typename Pointer = T *, typename Reference = T &>
    struct iterator
    {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Pointer Pointer;
        typedef Reference reference;
        typedef Distance difference_type;
    };

    // iterator_traits
    template <typename T>
    struct has_iterator_cat
    {
    private:
        struct two
        {
            char a;
            char b;
        };
        template <typename U>
        static two test(...);
    };

}

#endif