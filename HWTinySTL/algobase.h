#ifndef HWTINYSTL_ALGOBASE_H_
#define HWTINYSTL_ALGOBASE_H_
/**
 * @File Name: algobase.h
 * @Brief : ���ͷ�ļ������� hwstl �Ļ����㷨
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-01-03
 * @State : finished 2022-01-13
 */

#include <cstring>

#include "iterator.h"
#include "util.h"

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

    /*****************************************************************************************/
    // max
    // ȡ�����еĽϴ�ֵ���������ʱ��֤���ص�һ������
    /*****************************************************************************************/
    template <typename T>
    inline const T &max(const T &lhs, const T &rhs)
    {
        return lhs < rhs ? rhs : lhs;
    }

    // ���ذ汾ʹ�ú������� comp ����Ƚϲ���
    template <typename T, typename Compare>
    inline const T &max(const T &lhs, const T &rhs)
    {
        return Compare(lhs, rhs) ? lhs : rhs
    }

    /*****************************************************************************************/
    // min
    // ȡ�����еĽ�Сֵ���������ʱ��֤���ص�һ������
    /*****************************************************************************************/
    template <typename T>
    inline const T &min(const T &lhs, const T &rhs)
    {
        return rhs < lhs ? rhs : lhs;
    }

    // ���ذ汾ʹ�ú������� comp ����Ƚϲ���
    template <typename T, typename Compare>
    inline const T &min(const T &lhs, const T &rhs)
    {
        return Compare(lhs, rhs) ? rhs : lhs
    }

    /*****************************************************************************************/
    // iter_swap
    // ��������������ָ����Ե�
    /*****************************************************************************************/
    template <typename Fiter1, typename Fiter2>
    inline void iter_swap(Fiter1 lhs, Fiter2 rhs)
    {
        hwstl::swap(*lhs, *rhs);
    }

    /*****************************************************************************************/
    // copy
    // �� [first, last)�����ڵ�Ԫ�ؿ����� [result, result + (last - first))��
    /*****************************************************************************************/
    // 1.input_iterator_tag �汾
    template <typename InputIter, typename OutputIter>
    inline OutputIter unchecked_cpy_cat(InputIter first, InputIter last, OutputIter result,
                                        hwstl::input_iterator_tag)
    {
        for (; first != last; ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    // 2.ramdom_access_iterator_tag �汾
    template <typename RandomIter, typename OutputIter>
    inline OutputIter
    unchecked_copy_cat(RandomIter first, RandomIter last, OutputIter result,
                       hwstl::random_access_iterator_tag)
    {
        for (auto n = last - first; n > 0; --n, ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    template <typename InputIter, typename OutputIter>
    inline OutputIter
    unchecked_copy(InputIter first, InputIter last, OutputIter result)
    {
        return unchecked_copy_cat(first, last, result, iterator_category(first));
    }

    // Ϊ trivially_copy_assignable �����ṩ�ػ��汾
    template <typename Tp, typename Up>
    inline typename std::enable_if<
        std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_copy_assignable<Up>::value,
        Up *>::type
    unchecked_copy(Tp *first, Tp *last, Up *result)
    {
        const auto n = static_cast<size_t>(last - first);
        if (n != 0)
            std::memmove(result, first, n * sizeof(Up));
        return result + n;
    }

    template <typename InputIter, typename OutputIter>
    inline OutputIter copy(InputIter first, InputIter last, OutputIter result)
    {
        return unchecked_copy(first, last, result);
    }
    /*****************************************************************************************/
    // copy_backward
    // �� [first, last)�����ڵ�Ԫ�ؿ����� [result - (last - first), result)��
    /*****************************************************************************************/
    // unchecked_copy_backward_cat �� bidirectional_iterator_tag �汾
    template <typename BidirectionalIter1, typename BidirectionalIter2>
    inline BidirectionalIter2
    unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                                BidirectionalIter2 result, hwstl::bidirectional_iterator_tag)
    {
        while (first != last)
            *--result = *--last;
        return result;
    }

    // unchecked_copy_backward_cat �� random_access_iterator_tag �汾
    template <typename BidirectionalIter1, typename BidirectionalIter2>
    inline BidirectionalIter2
    unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                                BidirectionalIter2 result, hwstl::random_access_iterator_tag)
    {
        for (auto n = last - first; n > 0; --n)
            *--result = *--last;
        return result;
    }

    template <typename BidirectionalIter1, typename BidirectionalIter2>
    inline BidirectionalIter2
    unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                            BidirectionalIter2 result)
    {
        return unchecked_copy_backward_cat(first, last, result,
                                           iterator_category(first));
    }

    // Ϊ trivially_copy_assignable �����ṩ�ػ��汾
    template <typename Tp, typename Up>
    inline typename std::enable_if<
        std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_copy_assignable<Up>::value,
        Up *>::type
    unchecked_copy_backward(Tp *first, Tp *last, Up *result)
    {
        const auto n = static_cast<size_t>(last - first);
        if (n != 0)
        {
            result -= n;
            std::memmove(result, first, n * sizeof(Up));
        }
        return result;
    }

    template <typename BidirectionalIter1, typename BidirectionalIter2>
    inline BidirectionalIter2
    copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
    {
        return unchecked_copy_backward(first, last, result);
    }
    /*****************************************************************************************/
    // copy_if
    // ��[first, last)������һԪ���� unary_pred ��Ԫ�ؿ������� result Ϊ��ʼ��λ����
    /*****************************************************************************************/
    template <typename InputIter, typename OutputIter, typename UnaryPredicate>
    inline OutputIter
    copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred)
    {
        for (; first != last; ++first)
        {
            if (unary_pred(*first))
                *result++ = *first;
        }
        return result;
    }

    /*****************************************************************************************/
    // copy_n
    // �� [first, first + n)�����ϵ�Ԫ�ؿ����� [result, result + n)��
    // ����һ�� pair �ֱ�ָ�򿽱�������β��
    /*****************************************************************************************/
    template <typename InputIter, typename Size, typename OutputIter>
    inline hwstl::pair<InputIter, OutputIter>
    unchecked_copy_n(InputIter first, Size n, OutputIter result, hwstl::input_iterator_tag)
    {
        for (; n > 0; --n, ++first, ++result)
        {
            *result = *first;
        }
        return hwstl::pair<InputIter, OutputIter>(first, result);
    }

    template <typename RandomIter, typename Size, typename OutputIter>
    inline hwstl::pair<RandomIter, OutputIter>
    unchecked_copy_n(RandomIter first, Size n, OutputIter result,
                     hwstl::random_access_iterator_tag)
    {
        auto last = first + n;
        return hwstl::pair<RandomIter, OutputIter>(last, hwstl::copy(first, last, result));
    }

    template <typename InputIter, typename Size, typename OutputIter>
    inline hwstl::pair<InputIter, OutputIter>
    copy_n(InputIter first, Size n, OutputIter result)
    {
        return unchecked_copy_n(first, n, result, iterator_category(first));
    }

    /*****************************************************************************************/
    // move
    // �� [first, last)�����ڵ�Ԫ���ƶ��� [result, result + (last - first))��
    /*****************************************************************************************/
    // input_iterator_tag �汾
    template <typename InputIter, typename OutputIter>
    inline OutputIter
    unchecked_move_cat(InputIter first, InputIter last, OutputIter result,
                       hwstl::input_iterator_tag)
    {
        for (; first != last; ++first, ++result)
        {
            *result = hwstl::move(*first);
        }
        return result;
    }

    // ramdom_access_iterator_tag �汾
    template <typename RandomIter, typename OutputIter>
    inline OutputIter
    unchecked_move_cat(RandomIter first, RandomIter last, OutputIter result,
                       hwstl::random_access_iterator_tag)
    {
        for (auto n = last - first; n > 0; --n, ++first, ++result)
        {
            *result = hwstl::move(*first);
        }
        return result;
    }

    template <typename InputIter, typename OutputIter>
    inline OutputIter
    unchecked_move(InputIter first, InputIter last, OutputIter result)
    {
        return unchecked_move_cat(first, last, result, iterator_category(first));
    }

    // Ϊ trivially_copy_assignable �����ṩ�ػ��汾
    template <typename Tp, typename Up>
    inline typename std::enable_if<
        std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_move_assignable<Up>::value,
        Up *>::type
    unchecked_move(Tp *first, Tp *last, Up *result)
    {
        const size_t n = static_cast<size_t>(last - first);
        if (n != 0)
            std::memmove(result, first, n * sizeof(Up));
        return result + n;
    }

    template <typename InputIter, typename OutputIter>
    inline OutputIter move(InputIter first, InputIter last, OutputIter result)
    {
        return unchecked_move(first, last, result);
    }

    /*****************************************************************************************/
    // move_backward
    // �� [first, last)�����ڵ�Ԫ���ƶ��� [result - (last - first), result)��
    /*****************************************************************************************/
    // bidirectional_iterator_tag �汾
    template <typename BidirectionalIter1, typename BidirectionalIter2>
    inline BidirectionalIter2
    unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                                BidirectionalIter2 result, hwstl::bidirectional_iterator_tag)
    {
        while (first != last)
            *--result = hwstl::move(*--last);
        return result;
    }

    // random_access_iterator_tag �汾
    template <typename RandomIter1, typename RandomIter2>
    inline RandomIter2
    unchecked_move_backward_cat(RandomIter1 first, RandomIter1 last,
                                RandomIter2 result, hwstl::random_access_iterator_tag)
    {
        for (auto n = last - first; n > 0; --n)
            *--result = hwstl::move(*--last);
        return result;
    }

    template <typename BidirectionalIter1, typename BidirectionalIter2>
    inline BidirectionalIter2
    unchecked_move_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                            BidirectionalIter2 result)
    {
        return unchecked_move_backward_cat(first, last, result,
                                           iterator_category(first));
    }

    // Ϊ trivially_copy_assignable �����ṩ�ػ��汾
    template <typename Tp, typename Up>
    inline typename std::enable_if<
        std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_move_assignable<Up>::value,
        Up *>::type
    unchecked_move_backward(Tp *first, Tp *last, Up *result)
    {
        const size_t n = static_cast<size_t>(last - first);
        if (n != 0)
        {
            result -= n;
            std::memmove(result, first, n * sizeof(Up));
        }
        return result;
    }

    template <typename BidirectionalIter1, typename BidirectionalIter2>
    inline BidirectionalIter2
    move_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
    {
        return unchecked_move_backward(first, last, result);
    }

    /*****************************************************************************************/
    // equal
    // �Ƚϵ�һ������ [first, last)�����ϵ�Ԫ��ֵ�Ƿ�͵ڶ��������
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2>
    inline bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (*first1 != *first2)
                return false;
        }
        return true;
    }

    // ���ذ汾ʹ�ú������� comp ����Ƚϲ���
    template <typename InputIter1, typename InputIter2, typename Compared>
    inline bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!comp(*first1, *first2))
                return false;
        }
        return true;
    }
    /*****************************************************************************************/
    // fill_n
    // �� first λ�ÿ�ʼ��� n ��ֵ
    /*****************************************************************************************/
    template <typename OutputIter, typename Size, typename T>
    inline OutputIter unchecked_fill_n(OutputIter first, Size n, const T &value)
    {
        for (; n > 0; --n, ++first)
        {
            *first = value;
        }
        return first;
    }

    // Ϊ one-byte �����ṩ�ػ��汾
    template <typename Tp, typename Size, typename Up>
    inline typename std::enable_if<
        std::is_integral<Tp>::value && sizeof(Tp) == 1 &&
            !std::is_same<Tp, bool>::value &&
            std::is_integral<Up>::value && sizeof(Up) == 1,
        Tp *>::type
    unchecked_fill_n(Tp *first, Size n, Up value)
    {
        if (n > 0)
        {
            std::memset(first, (unsigned char)value, (size_t)(n));
        }
        return first + n;
    }

    template <typename OutputIter, typename Size, typename T>
    inline OutputIter fill_n(OutputIter first, Size n, const T &value)
    {
        return unchecked_fill_n(first, n, value);
    }
    /*****************************************************************************************/
    // fill
    // Ϊ [first, last)�����ڵ�����Ԫ�������ֵ
    /*****************************************************************************************/
    template <typename ForwardIter, typename T>
    inline void fill_cat(ForwardIter first, ForwardIter last, const T &value,
                         hwstl::forward_iterator_tag)
    {
        for (; first != last; ++first)
        {
            *first = value;
        }
    }

    template <typename RandomIter, typename T>
    inline void fill_cat(RandomIter first, RandomIter last, const T &value,
                         hwstl::random_access_iterator_tag)
    {
        fill_n(first, last - first, value);
    }

    template <typename ForwardIter, typename T>
    inline void fill(ForwardIter first, ForwardIter last, const T &value)
    {
        fill_cat(first, last, value, iterator_category(first));
    }

    /*****************************************************************************************/
    // lexicographical_compare
    // ���ֵ������ж��������н��бȽϣ�����ĳ��λ�÷��ֵ�һ�鲻���Ԫ��ʱ�������м��������
    // (1)�����һ���е�Ԫ�ؽ�С������ true �����򷵻� false
    // (2)������� last1 ����δ���� last2 ���� true
    // (3)������� last2 ����δ���� last1 ���� false
    // (4)���ͬʱ���� last1 �� last2 ���� false
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2>
    inline bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                        InputIter2 first2, InputIter2 last2)
    {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return first1 == last1 && first2 != last2;
    }

    // ���ذ汾ʹ�ú������� comp ����Ƚϲ���
    template <typename InputIter1, typename InputIter2, typename Compred>
    inline bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                        InputIter2 first2, InputIter2 last2, Compred comp)
    {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }
        return first1 == last1 && first2 != last2;
    }

    // ��� const unsigned char* ���ػ��汾
    inline bool lexicographical_compare(const unsigned char *first1,
                                        const unsigned char *last1,
                                        const unsigned char *first2,
                                        const unsigned char *last2)
    {
        const auto len1 = last1 - first1;
        const auto len2 = last2 - first2;
        // �ȱȽ���ͬ���ȵĲ���
        const auto result = std::memcmp(first1, first2, hwstl::min(len1, len2));
        // ����ȣ����Ƚϳ��ıȽϴ�
        return result != 0 ? result < 0 : len1 < len2;
    }

    /*****************************************************************************************/
    // mismatch
    // ƽ�бȽ��������У��ҵ���һ��ʧ���Ԫ�أ�����һ�Ե��������ֱ�ָ������������ʧ���Ԫ��
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2>
    hwstl::pair<InputIter1, InputIter2>
    mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2)
    {
        while (first1 != last1 && *first1 == *first2)
        {
            ++first1;
            ++first2;
        }
        return hwstl::pair<InputIter1, InputIter2>(first1, first2);
    }

    // ���ذ汾ʹ�ú������� comp ����Ƚϲ���
    template <typename InputIter1, typename InputIter2, typename Compred>
    hwstl::pair<InputIter1, InputIter2>
    mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compred comp)
    {
        while (first1 != last1 && comp(*first1, *first2))
        {
            ++first1;
            ++first2;
        }
        return hwstl::pair<InputIter1, InputIter2>(first1, first2);
    }
} // namespace hwstl

#endif