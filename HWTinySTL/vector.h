#ifndef HWTINYSTL_VECTOR_H_
#define HWTINYSTL_VECTOR_H_
/**
 * @File Name: vector.h
 * @Brief :  vector : ����
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 *
 */
// �쳣��֤��
// mystl::vecotr<T> ��������쳣��֤�����ֺ������쳣��֤���������º�����ǿ�쳣��ȫ��֤��
//   * emplace
//   * emplace_back
//   * push_back
// �� std::is_nothrow_move_assignable<T>::value == true ʱ�����º���Ҳ����ǿ�쳣��֤��
//   * reserve
//   * resize
//   * insert

#include <initializer_list>

#include "iterator.h"
#include "memory.h"
#include "util.h"
#include "exceptdef.h"
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

    // ģ����: vector
    // ģ����� T ��������
    template <typename T>
    class vector
    {
        static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned in hwstl");

    public:
        // vector ��Ƕ��
        typedef hwstl::allocator<T> allocator_type;
        typedef hwstl::allocator<T> data_allocator;

        typedef typename allocator_type::value_type value_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

        //��Ϊ�������ռ䣬����ֱ����ָ�뵱������
        typedef value_type *iterator;
        typedef const value_type *const_iterator;
        typedef hwstl::reverse_iterator<iterator> reverse_iterator;
        typedef hwstl::reverse_iterator<const iterator> const_reverse_iterator;

        allocator_type get_allocator() { return data_allocator(); }

    private:
        iterator begin_; //��ʾĿǰʹ�ÿռ��ͷ��
        iterator end_;   //��ʾĿǰʹ�ÿռ��β��
        iterator cap_;   //��ʾĿǰ�洢�ռ��β��

    public:
        //���졢���ơ��ƶ�����������
        vector();
        ~vector();
    };

}
#endif