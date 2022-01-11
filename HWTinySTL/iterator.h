#ifndef HWTINYSTL_ITERATOR_H_
#define HWTINYSTL_ITERATOR_H_
/**
 * @File Name: iterator.h
 * @Brief : 用于迭代器设计，包含了一些模板结构体与全局函数，
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 * @Statement : finished (2022-1-5)
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
    template <typename T>
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

    template <typename T, typename U, bool = has_iterator_cat<iterator_traits<T>>::value>
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

    template <typename ITer>
    struct is_input_iterator : public has_iterator_cat_of<ITer, input_iterator_tag>
    {
    };

    template <typename ITer>
    struct is_output_iterator : public has_iterator_cat_of<ITer, output_iterator_tag>
    {
    };

    template <typename ITer>
    struct is_forward_iterator : public has_iterator_cat_of<ITer, bidirectional_iterator_tag>
    {
    };

    template <typename ITer>
    struct is_random_access_iterator : public has_iterator_cat_of<ITer, random_access_iterator_tag>
    {
    };

    template <typename Iterator>
    struct is_iterator : public m_bool_constant<is_input_iterator<iterator>::value ||
                                                is_output_iterator<iterator>::value>
    {
    };

    //萃取某个迭代器的 category
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &)
    {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }

    //萃取某个迭代器的distance_type
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::difference_type *
    distance_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
    }

    // 萃取某个迭代器的 value_type
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::value_type *
    value_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
    }

    //以下函数计算迭代器间的距离
    // distance 的 input_iterator_tag 的版本
    template <typename InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    // distance 的 random_access_iterator_tag 的版本
    template <typename RandomIter>
    inline typename iterator_traits<RandomIter>::difference_type
    distance_dispatch(RandomIter first, RandomIter last,
                      random_access_iterator_tag)
    {
        return last - first;
    }

    template <typename InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        return distance_dispatch(first, last, iterator_category(first));
    }

    // 以下函数用于让迭代器前进 n 个距离

    // advance 的 input_iterator_tag 的版本
    template <typename InputIterator, typename Distance>
    inline void advance_dispatch(InputIterator &i, Distance n, input_iterator_tag)
    {
        while (n--)
            ++i;
    }
    // advance 的 bidirectional_iterator_tag 的版本
    template <typename BidirectionalIterator, typename Distance>
    inline void advance_dispatch(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag)
    {
        if (n >= 0)
            while (n--)
                ++i;
        else
            while (n++)
                --i;
    }

    // advance 的 random_access_iterator_tag 的版本
    template <typename RandomIter, typename Distance>
    inline void advance_dispatch(RandomIter &i, Distance n, random_access_iterator_tag)
    {
        i += n;
    }

    template <typename InputIterator, typename Distance>
    inline void advance(InputIterator &i, Distance n)
    {
        advance_dispatch(i, n, iterator_category(i));
    }

    /*****************************************************************************************/

    // 模板类 : reverse_iterator
    // 代表反向迭代器，使前进为后退，后退为前进
    template <typename Iterator>
    class reverse_iterator
    {
    private:
        Iterator current; //记录对应的正向迭代器
    public:
        //返向迭代器的五种相应类型
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;

        typedef Iterator iterator_type;
        typedef reverse_iterator<Iterator> self;

    public:
        //构造函数
        reverse_iterator() {}
        explicit reverse_iterator(iterator_type i) : current(i) {}
        reverse_iterator(const self &rhs) : current(rhs.current) {}

    public:
        //取出相应的正向迭代器
        inline iterator_type base() const
        {
            return current;
        }

        //重载操作符,重载操作符里面有一个隐藏的this
        inline reference operator*() const
        {
            //实际对应正向迭代器的前一个位置
            auto tmp = current;
            return *--tmp;
        }

        inline pointer operator->() const
        {
            return &(operator*());
        }

        // 前进(++)变为后退(--)
        //前++
        inline self &operator++()
        {
            --current;
            retrun *this;
        }
        //后++
        inline self operator++(int)
        {
            self tmp = *this;
            --current;
            return tmp;
        }

        // 后退(--)变为前进(++)
        inline self &operator--()
        {
            ++current;
            return *this;
        }
        inline self operator--(int)
        {
            self tmp = *this;
            ++current;
            return tmp;
        }

        //+=, +, -=, -
        inline self &operator+=(difference_type n)
        {
            current -= n;
            return *this;
        }

        inline self operator+(difference_type n) const
        {
            return self(current - n);
        }

        inline self &operator-=(difference_type n)
        {
            current += n return *this;
        }

        inline self operator-(difference_type n) const
        {
            return self(current + n);
        }

        inline self operator[](difference_type n) const
        {
            return *(*this + n);
        }
    };

    //重载 operate-
    template <typename Iterator>
    inline typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> &lhs,
              const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() - lhs.base();
    }

    //重载比较操作符 == ,< ,!=,>,<=,>=

    template <typename Iterator>
    inline bool operator==(const reverse_iterator<Iterator> &lhs,
                           const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() == lhs.base();
    }

    template <typename Iterator>
    inline bool operator<(const reverse_iterator<Iterator> &lhs,
                          const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() < lhs.base();
    }

    template <typename Iterator>
    inline bool operator<=(const reverse_iterator<Iterator> &lhs,
                           const reverse_iterator<Iterator> &rhs)
    {
        return !(rhs < lhs);
    }

    template <typename Iterator>
    inline bool operator>(const reverse_iterator<Iterator> &lhs,
                          const reverse_iterator<Iterator> &rhs)
    {
        return rhs < lhs;
    }

    template <typename Iterator>
    inline bool operator>=(const reverse_iterator<Iterator> &lhs,
                           const reverse_iterator<Iterator> &rhs)
    {
        return !(lhs < rhs);
    }

    template <typename Iterator>
    inline bool operator!=(const reverse_iterator<Iterator> &lhs,
                           const reverse_iterator<Iterator> &rhs)
    {
        return !(rhs == lhs);
    }

}

#endif