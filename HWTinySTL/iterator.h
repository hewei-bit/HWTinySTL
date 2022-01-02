/**
 * @File Name: iterator.h
 * @Brief : ���ڵ�������ƣ�������һЩģ��ṹ����ȫ�ֺ�����
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 *
 */
#ifndef HWTINYSTL_ITERATOR_H_
#define HWTINYSTL_ITERATOR_H_
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
    template <typename Category, typename T, typename Distance = ptrdiff_t,
              typename Pointer = T *, typename Reference = T &>
    struct iterator
    {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Pointer Pointer;
        typedef Reference reference;
        typedef Distance difference_type;
    };

    // iterator_traits
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

    //���ԭ��ָ���ƫ�ػ��汾
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

    //��ȡĳ�ֵ�����
    template <typename T, typename U>
    struct has_iterator_cat_of<T, U, false> : public : m_false_type
    {
    };

}

#endif