#ifndef HWTINYSTL_ITERATOR_H_
#define HWTINYSTL_ITERATOR_H_
/**
 * @File Name: iterator.h
 * @Brief : ���ڵ�������ƣ�������һЩģ��ṹ����ȫ�ֺ�����
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 * @Statement : finished (2022-1-5)
 */

#include <cstddef>
#include "type_traits.h"
namespace hwstl
{
    //���ֵ�����:
    //���������
    struct input_iterator_tag
    {
    };
    //���������
    struct output_iterator_tag
    {
    };
    //���������
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    //˫�������
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };
    //������ʵ�����
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };

    // iterator ģ��
    // ���г�iterator������㷨�ṩ��5����������
    template <typename Category, typename T, typename Distance = ptrdiff_t,
              typename Pointer = T *, typename Reference = T &>
    struct iterator
    {
        typedef Category iterator_category; //���������
        typedef T value_type;               //��������
        typedef Pointer Pointer;            //����ָ��
        typedef Reference reference;        //��������
        typedef Distance difference_type;   //����������֮�����
    };

    // iterator_traits
    // ���Է���class iterator��vector��map��list...�� �� nonclass iterator��ָ�룩
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

    //��ȡ����������
    template <typename Iterator>
    struct iterator_traits
        : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value>
    {
    };

    //��� nonclass iterator ��ԭ��ָ���ƫ�ػ��汾
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

    //��ȡĳ�ֵ�����
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

    //��ȡĳ���������� category
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &)
    {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }

    //��ȡĳ����������distance_type
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::difference_type *
    distance_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
    }

    // ��ȡĳ���������� value_type
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::value_type *
    value_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
    }

    //���º��������������ľ���
    // distance �� input_iterator_tag �İ汾
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

    // distance �� random_access_iterator_tag �İ汾
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

    // ���º��������õ�����ǰ�� n ������

    // advance �� input_iterator_tag �İ汾
    template <typename InputIterator, typename Distance>
    inline void advance_dispatch(InputIterator &i, Distance n, input_iterator_tag)
    {
        while (n--)
            ++i;
    }
    // advance �� bidirectional_iterator_tag �İ汾
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

    // advance �� random_access_iterator_tag �İ汾
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

    // ģ���� : reverse_iterator
    // �������������ʹǰ��Ϊ���ˣ�����Ϊǰ��
    template <typename Iterator>
    class reverse_iterator
    {
    private:
        Iterator current; //��¼��Ӧ�����������
    public:
        //�����������������Ӧ����
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;

        typedef Iterator iterator_type;
        typedef reverse_iterator<Iterator> self;

    public:
        //���캯��
        reverse_iterator() {}
        explicit reverse_iterator(iterator_type i) : current(i) {}
        reverse_iterator(const self &rhs) : current(rhs.current) {}

    public:
        //ȡ����Ӧ�����������
        inline iterator_type base() const
        {
            return current;
        }

        //���ز�����,���ز�����������һ�����ص�this
        inline reference operator*() const
        {
            //ʵ�ʶ�Ӧ�����������ǰһ��λ��
            auto tmp = current;
            return *--tmp;
        }

        inline pointer operator->() const
        {
            return &(operator*());
        }

        // ǰ��(++)��Ϊ����(--)
        //ǰ++
        inline self &operator++()
        {
            --current;
            retrun *this;
        }
        //��++
        inline self operator++(int)
        {
            self tmp = *this;
            --current;
            return tmp;
        }

        // ����(--)��Ϊǰ��(++)
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

    //���� operate-
    template <typename Iterator>
    inline typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> &lhs,
              const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() - lhs.base();
    }

    //���رȽϲ����� == ,< ,!=,>,<=,>=

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