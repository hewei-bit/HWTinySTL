/**
 * @File Name: type_traits.h
 * @Brief : ������ȡ������Ϣ
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-19
 *
 */

#ifndef HWTINYSTL_TYPE_TRAITS_H_
#define HWTINYSTL_TYPE_TRAITS_H_
// ʹ����type_traits�ı�׼ͷ�ļ�
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