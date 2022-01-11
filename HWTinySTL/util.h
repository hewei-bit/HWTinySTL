#ifndef HWTINYSTL_UTIL_H_
#define HWTINYSTL_UTIL_H_
/**
 * @File Name: util.h
 * @Brief : 这个文件包含一些通用工具，
 *          包括 move, forward, swap 等函数，以及 pair 等
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-01-03
 *
 */

#include <cstddef>
#include "type_traits.h"
namespace hwstl
{
    // move
    template <typename T>
    typename std::remove_reference<T>::type &&move(T &&arg) noexcept
    {
        return static_cast<typename std::remove_reference<T>::type &&>(arg);
    }
    // forward
    template <typename T>
    T &&forward(typename std::remove_reference<T>::type &arg) noexcept
    {
        return static_cast<T &&>(arg);
    }

    template <typename T>
    T &&forward(typename std::remove_reference<T>::type &&arg) noexcept
    {
        static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
        return static_cast<T &&>(arg);
    }

    // swap
    template <typename Tp>
    void swap(Tp &lhs, Tp &rhs)
    {
        auto tmp(hwstl::move(lhs));
        lhs = hwstl::move(rhs);
        rhs = hwstl::move(tmp);
    }

    template <typename ForwardIter1, typename ForwardIter2>
    ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
    {
        for (; first1 != last1; ++first1, (void)++first2)
            hwstl::swap(*first1, *first2);
        return first2;
    }

    template <typename Tp, size_t N>
    void swap(Tp (&a)[N], Tp (&b)[N])
    {
        hwstl::swap_range(a, a + N, b);
    }
    // pair
    // 结构体模板 : pair
    // 两个模板参数分别表示两个数据的类型
    // 用 first 和 second 来分别取出第一个数据和第二个数据
    template <typename Ty1, typename Ty2>
    struct pair
    {
        typedef Ty1 first_type;
        typedef Ty2 second_type;

        first_type first;   // 保存第一个数据
        second_type second; // 保存第二个数据

        // default constructiable
        template <typename Other1 = Ty1, typename Other2 = Ty2,
                  typename = typename std::enable_if<
                      std::is_default_constructible<Other1>::value &&
                          std::is_default_constructible<Other2>::value,
                      void>::type>
        constexpr pair()
            : first(), second()
        {
        }

        // implicit constructiable for this type
        template <typename U1 = Ty1, typename U2 = Ty2,
                  typename std::enable_if<
                      std::is_copy_constructible<U1>::value &&
                          std::is_copy_constructible<U2>::value &&
                          std::is_convertible<const U1 &, Ty1>::value &&
                          std::is_convertible<const U2 &, Ty2>::value,
                      int>::type = 0>
        constexpr pair(const Ty1 &a, const Ty2 &b)
            : first(a), second(b)
        {
        }

        // explicit constructible for this type
        template <typename U1 = Ty1, typename U2 = Ty2,
                  typename std::enable_if<
                      std::is_copy_constructible<U1>::value &&
                          std::is_copy_constructible<U2>::value &&
                          (!std::is_convertible<const U1 &, Ty1>::value ||
                           !std::is_convertible<const U2 &, Ty2>::value),
                      int>::type = 0>
        explicit constexpr pair(const Ty1 &a, const Ty2 &b)
            : first(a), second(b)
        {
        }

        pair(const pair &rhs) = default;
        pair(pair &&rhs) = default;

        // implicit constructiable for other type
        template <typename Other1, typename Other2,
                  typename std::enable_if<
                      std::is_constructible<Ty1, Other1>::value &&
                          std::is_constructible<Ty2, Other2>::value &&
                          std::is_convertible<Other1 &&, Ty1>::value &&
                          std::is_convertible<Other2 &&, Ty2>::value,
                      int>::type = 0>
        constexpr pair(Other1 &&a, Other2 &&b)
            : first(hwstl::forward<Other1>(a)),
              second(hwstl::forward<Other2>(b))
        {
        }

        // explicit constructiable for other type
        template <typename Other1, typename Other2,
                  typename std::enable_if<
                      std::is_constructible<Ty1, Other1>::value &&
                          std::is_constructible<Ty2, Other2>::value &&
                          (!std::is_convertible<Other1, Ty1>::value ||
                           !std::is_convertible<Other2, Ty2>::value),
                      int>::type = 0>
        explicit constexpr pair(Other1 &&a, Other2 &&b)
            : first(hwstl::forward<Other1>(a)),
              second(hwstl::forward<Other2>(b))
        {
        }

        // implicit constructiable for other pair
        template <typename Other1, typename Other2,
                  typename std::enable_if<
                      std::is_constructible<Ty1, const Other1 &>::value &&
                          std::is_constructible<Ty2, const Other2 &>::value &&
                          std::is_convertible<const Other1 &, Ty1>::value &&
                          std::is_convertible<const Other2 &, Ty2>::value,
                      int>::type = 0>
        constexpr pair(const pair<Other1, Other2> &other)
            : first(other.first),
              second(other.second)
        {
        }

        // explicit constructiable for other pair
        template <typename Other1, typename Other2,
                  typename std::enable_if<
                      std::is_constructible<Ty1, const Other1 &>::value &&
                          std::is_constructible<Ty2, const Other2 &>::value &&
                          (!std::is_convertible<const Other1 &, Ty1>::value ||
                           !std::is_convertible<const Other2 &, Ty2>::value),
                      int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2> &other)
            : first(other.first),
              second(other.second)
        {
        }

        // implicit constructiable for other pair
        template <typename Other1, typename Other2,
                  typename std::enable_if<
                      std::is_constructible<Ty1, Other1>::value &&
                          std::is_constructible<Ty2, Other2>::value &&
                          std::is_convertible<Other1, Ty1>::value &&
                          std::is_convertible<Other2, Ty2>::value,
                      int>::type = 0>
        constexpr pair(pair<Other1, Other2> &&other)
            : first(hwstl::forward<Other1>(other.first)),
              second(hwstl::forward<Other2>(other.second))
        {
        }

        // explicit constructiable for other pair
        template <typename Other1, typename Other2,
                  typename std::enable_if<
                      std::is_constructible<Ty1, Other1>::value &&
                          std::is_constructible<Ty2, Other2>::value &&
                          (!std::is_convertible<Other1, Ty1>::value ||
                           !std::is_convertible<Other2, Ty2>::value),
                      int>::type = 0>
        explicit constexpr pair(pair<Other1, Other2> &&other)
            : first(hwstl::forward<Other1>(other.first)),
              second(hwstl::forward<Other2>(other.second))
        {
        }

        // copy assign for this pair
        pair &operator=(const pair &rhs)
        {
            if (this != &rhs)
            {
                first = rhs.first;
                second = rhs.second;
            }
            return *this;
        }

        // move assign for this pair
        pair &operator=(pair &&rhs)
        {
            if (this != &rhs)
            {
                first = hwstl::move(rhs.first);
                second = hwstl::move(rhs.second);
            }
            return *this;
        }

        // copy assign for other pair
        template <typename Other1, typename Other2>
        pair &operator=(const pair<Other1, Other2> &other)
        {
            first = other.first;
            second = other.second;
            return *this;
        }

        // move assign for other pair
        template <typename Other1, typename Other2>
        pair &operator=(pair<Other1, Other2> &&other)
        {
            first = hwstl::forward<Other1>(other.first);
            second = hwstl::forward<Other2>(other.second);
            return *this;
        }

        ~pair() = default;

        void swap(pair &other)
        {
            if (this != &other)
            {
                hwstl::swap(first, other.first);
                hwstl::swap(second, other.second);
            }
        }
    };

    // 重载比较操作符
    template <typename Ty1, typename Ty2>
    bool operator==(const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <typename Ty1, typename Ty2>
    bool operator<(const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs)
    {
        return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
    }

    template <typename Ty1, typename Ty2>
    bool operator!=(const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Ty1, typename Ty2>
    bool operator>(const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs)
    {
        return rhs < lhs;
    }

    template <typename Ty1, typename Ty2>
    bool operator<=(const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs)
    {
        return !(rhs < lhs);
    }

    template <typename Ty1, typename Ty2>
    bool operator>=(const pair<Ty1, Ty2> &lhs, const pair<Ty1, Ty2> &rhs)
    {
        return !(lhs < rhs);
    }

    // 重载 hwstl 的 swap
    template <typename Ty1, typename Ty2>
    void swap(pair<Ty1, Ty2> &lhs, pair<Ty1, Ty2> &rhs)
    {
        lhs.swap(rhs);
    }

    // 全局函数，让两个数据成为一个 pair
    template <typename Ty1, typename Ty2>
    pair<Ty1, Ty2> make_pair(Ty1 &&first, Ty2 &&second)
    {
        return pair<Ty1, Ty2>(hwstl::forward<Ty1>(first), hwstl::forward<Ty2>(second));
    }
}

#endif