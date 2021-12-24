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
    struct input_iterator_tag
    {
    };
    struct output_iterator_tag
    {
    };
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    struct bi

}