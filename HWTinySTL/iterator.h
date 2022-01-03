#ifndef HWTINYSTL_ITERATOR_H_
#define HWTINYSTL_ITERATOR_H_
/**
 * @File Name: iterator.h
 * @Brief : 用于迭代器设计，包含了一些模板结构体与全局函数，
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 *
 */

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
    // 罗列出iterator必须给算法提供的5种数据类型
    template <typename Category, typename T, typename Distance = ptrdiff_t,
              typename Pointer = T *, typename Reference = T &>
    struct iterator
    {
        typedef Category iterator_category; //迭代器类别
        typedef T value_type;               //数据类型
        typedef Pointer Pointer;            //数据指针
        typedef Reference reference;        //数据引用
        typedef Distance difference_type;   //两个迭代器之间距离
    };

    // iterator_traits
    // 用以分离class iterator（vector、map、list...） 和 nonclass iterator（指针）
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
        template <typename U>
        static char test(typename U::iterator_category * = 0);

    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };

    template <typename Iterator, bool>
    struct iterator_traits_impl
    {
    };
    template <typename Iterator>
    struct iterator_traits_impl<Iterator, true>
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::difference_type difference_type;
    };

    template <typename Iterator, bool>
    struct iterator_traits_helper
    {
    };

    template <typename Iterator>
    struct iterator_traits_helper<Iterator, true>
        : public iterator_traits_impl<Iterator,
                                      std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
                                          std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>

    {
    };

    //萃取迭代器特性
    template <typename Iterator>
    struct iterator_traits
        : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value>
    {
    };

    //针对 nonclass iterator 即原生指针的偏特化版本
    template <class T>
    struct iterator_traits<T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef ptrdiff_t difference_type;
    };

    template <typename T>
    struct iterator_traits<const T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef ptrdiff_t difference_type;
    };

    template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of
        : public m_bool_constant<
              std::is_convertible<
                  typename iterator<T>::iterator_category, U>::value>
    {
        /* data */
    };

    //萃取某种迭代器
    template <typename T, typename U>
    struct has_iterator_cat_of<T, U, false> : public : m_false_type
    {
    };

}

#endif