/**
 * @File Name: type_traits.h
 * @Brief : 用于提取类型信息
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-19
 *
 */

#ifndef HWTINYSTL_TYPE_TRAITS_H_
#define HWTINYSTL_TYPE_TRAITS_H_
// 使用了type_traits的标准头文件
#include <type_traits>
namespace hwstl
{
    // helper struct
    template <typename AnyType, AnyType v>
    struct m_integral_constant
    {
        static constexpr AnyType value = v;
    };

    template <bool b>
    using m_bool_constant = m_integral_constant;

}
#endif