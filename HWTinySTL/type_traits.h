#ifndef HWTINYSTL_TYPE_TRAITS_H_
#define HWTINYSTL_TYPE_TRAITS_H_
/**
 * @File Name: type_traits.h
 * @Brief : 用于提取类型信息
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-19
 * @statement : finished 2021-01-12
 */

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
    using m_bool_constant = m_integral_constant<bool, b>;

    typedef m_bool_constant<true> m_true_type;
    typedef m_bool_constant<false> m_false_type;
    /*****************************************************************************************/
    // type traits
    // is_pair
    // --- forward declaration begin
    template <typename T1, typename T2>
    struct pair;
    // --- forward declaration end

    template <typename T>
    struct is_pair : hwstl::m_false_type
    {
    };
    template <typename T1, typename T2>
    struct is_pair<hwstl::pair<T1, T2>> : hwstl::m_true_type
    {
    };

}
#endif