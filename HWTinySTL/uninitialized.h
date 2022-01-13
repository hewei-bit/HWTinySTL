#ifndef HWTINYSTL_UNINITIALIZED_H_
#define HWTINYSTL_UNINITIALIZED_H_

/**
 * @File Name: uninitialized.h
 * @Brief : ���ͷ�ļ����ڶ�δ��ʼ���ռ乹��Ԫ��
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-01-03
 * @State : finished 2022-01-13
 */
#include "algobase.h"
#include "construct.h"
#include "iterator.h"
#include "type_traits.h"
#include "util.h"
namespace hwstl
{
    /*****************************************************************************************/
    // uninitialized_copy
    // �� [first, last) �ϵ����ݸ��Ƶ��� result Ϊ��ʼ���Ŀռ䣬���ظ��ƽ�����λ��
    /*****************************************************************************************/
    template <typename InputIter, typename ForwardIter>
    inline ForwardIter
    unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type)
    {
        return hwstl::copy(first, last, result);
    }

    template <typename InputIter, typename ForwardIter>
    inline ForwardIter
    unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type)
    {
        auto cur = result;
        try
        {
            for (; first != last; ++first, ++cur)
            {
                hwstl::construct(&*cur, *first);
            }
        }
        catch (...)
        {
            for (; result != cur; --cur)
                hwstl::destroy(&*cur);
        }
        return cur;
    }

    template <typename InputIter, typename ForwardIter>
    inline ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
    {
        return hwstl::unchecked_uninit_copy(first, last, result,
                                            std::is_trivially_copy_assignable<
                                                typename iterator_traits<ForwardIter>::
                                                    value_type>{});
    }

    /*****************************************************************************************/
    // uninitialized_copy_n
    // �� [first, first + n) �ϵ����ݸ��Ƶ��� result Ϊ��ʼ���Ŀռ䣬���ظ��ƽ�����λ��
    /*****************************************************************************************/
    template <typename InputIter, typename Size, typename ForwardIter>
    inline ForwardIter
    unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::true_type)
    {
        return hwstl::copy_n(first, n, result).second;
    }

    template <typename InputIter, typename Size, typename ForwardIter>
    ForwardIter inline unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::false_type)
    {
        auto cur = result;
        try
        {
            for (; n > 0; --n, ++cur, ++first)
            {
                hwstl::construct(&*cur, *first);
            }
        }
        catch (...)
        {
            for (; result != cur; --cur)
                hwstl::destroy(&*cur);
        }
        return cur;
    }

    template <typename InputIter, typename Size, typename ForwardIter>
    inline ForwardIter uninitialized_copy_n(InputIter first, Size n, ForwardIter result)
    {
        return hwstl::unchecked_uninit_copy_n(first, n, result,
                                              std::is_trivially_copy_assignable<
                                                  typename iterator_traits<InputIter>::
                                                      value_type>{});
    }
    /*****************************************************************************************/
    // uninitialized_fill
    // �� [first, last) ���������Ԫ��ֵ
    /*****************************************************************************************/
    template <typename ForwardIter, typename T>
    inline void
    unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T &value, std::true_type)
    {
        hwstl::fill(first, last, value);
    }

    template <typename ForwardIter, typename T>
    inline void
    unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T &value, std::false_type)
    {
        auto cur = first;
        try
        {
            for (; cur != last; ++cur)
            {
                hwstl::construct(&*cur, value);
            }
        }
        catch (...)
        {
            for (; first != cur; ++first)
                hwstl::destroy(&*first);
        }
    }

    template <typename ForwardIter, typename T>
    inline void uninitialized_fill(ForwardIter first, ForwardIter last, const T &value)
    {
        hwstl::unchecked_uninit_fill(first, last, value,
                                     std::is_trivially_copy_assignable<
                                         typename iterator_traits<ForwardIter>::
                                             value_type>{});
    }
    /*****************************************************************************************/
    // uninitialized_fill_n
    // �� first λ�ÿ�ʼ����� n ��Ԫ��ֵ��������������λ��
    /*****************************************************************************************/
    template <typename ForwardIter, typename Size, typename T>
    inline ForwardIter
    unchecked_uninit_fill_n(ForwardIter first, Size n, const T &value, std::true_type)
    {
        return hwstl::fill_n(first, n, value);
    }

    template <typename ForwardIter, typename Size, typename T>
    inline ForwardIter
    unchecked_uninit_fill_n(ForwardIter first, Size n, const T &value, std::false_type)
    {
        auto cur = first;
        try
        {
            for (; n > 0; --n, ++cur)
            {
                hwstl::construct(&*cur, value);
            }
        }
        catch (...)
        {
            for (; first != cur; ++first)
                hwstl::destroy(&*first);
        }
        return cur;
    }

    template <typename ForwardIter, typename Size, typename T>
    inline ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &value)
    {
        return hwstl::unchecked_uninit_fill_n(first, n, value,
                                              std::is_trivially_copy_assignable<
                                                  typename iterator_traits<ForwardIter>::
                                                      value_type>{});
    }

    /*****************************************************************************************/
    // uninitialized_move
    // ��[first, last)�ϵ������ƶ����� result Ϊ��ʼ���Ŀռ䣬�����ƶ�������λ��
    /*****************************************************************************************/
    template <typename InputIter, typename ForwardIter>
    inline ForwardIter
    unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type)
    {
        return hwstl::move(first, last, result);
    }

    template <typename InputIter, typename ForwardIter>
    inline ForwardIter
    unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::false_type)
    {
        ForwardIter cur = result;
        try
        {
            for (; first != last; ++first, ++cur)
            {
                hwstl::construct(&*cur, hwstl::move(*first));
            }
        }
        catch (...)
        {
            hwstl::destroy(result, cur);
        }
        return cur;
    }

    template <typename InputIter, typename ForwardIter>
    inline ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result)
    {
        return hwstl::unchecked_uninit_move(first, last, result,
                                            std::is_trivially_move_assignable<
                                                typename iterator_traits<InputIter>::
                                                    value_type>{});
    }
    /*****************************************************************************************/
    // uninitialized_move_n
    // ��[first, first + n)�ϵ������ƶ����� result Ϊ��ʼ���Ŀռ䣬�����ƶ�������λ��
    /*****************************************************************************************/
    template <typename InputIter, typename Size, typename ForwardIter>
    inline ForwardIter
    unchecked_uninit_move_n(InputIter first, Size n, ForwardIter result, std::true_type)
    {
        return hwstl::move(first, first + n, result);
    }

    template <typename InputIter, typename Size, typename ForwardIter>
    inline ForwardIter
    unchecked_uninit_move_n(InputIter first, Size n, ForwardIter result, std::false_type)
    {
        auto cur = result;
        try
        {
            for (; n > 0; --n, ++first, ++cur)
            {
                hwstl::construct(&*cur, hwstl::move(*first));
            }
        }
        catch (...)
        {
            for (; result != cur; ++result)
                hwstl::destroy(&*result);
            throw;
        }
        return cur;
    }

    template <typename InputIter, typename Size, typename ForwardIter>
    inline ForwardIter uninitialized_move_n(InputIter first, Size n, ForwardIter result)
    {
        return hwstl::unchecked_uninit_move_n(first, n, result,
                                              std::is_trivially_move_assignable<
                                                  typename iterator_traits<InputIter>::
                                                      value_type>{});
    }
}
#endif