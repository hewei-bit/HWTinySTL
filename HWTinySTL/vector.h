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
        vector() noexcept
        {
            try_init();
        }

        explicit vector(size_type n)
        {
            fill_init(n, value_type());
        }

        vector(size_type n, const value_type &value)
        {
            fill_init(n, value);
        }

        template <class Iter, typename std::enable_if<hwstl::is_input_iterator<Iter>::value, int>::type = 0>
        vector(Iter first, Iter last)
        {
            HWSTL_DEBUG(!(last < first));
            range_init(first, last);
        }

        vector(const vector &rhs)
        {
            range_init(rhs.begin_, rhs.end_);
        }

        vector(vector &&rhs) noexcept
            : begin_(rhs.begin_), end_(rhs.end_), cap_(rhs.cap_)
        {
            rhs.begin_ = nullptr;
            rhs.end_ = nullptr;
            rhs.cap_ = nullptr;
        }

        vector(std::initializer_list<value_type> ilist)
        {
            range_init(ilist.begin(), ilist.end());
        }

                ~vector();

    private:
        // helper functions
        // initialize / destroy
        void try_init() noexcept;
        void init_space(size_type size, size_type cap);
        void fill_init(size_type n, const value_type &value_type);

        template <class Iter>
        void range_init(Iter first, Iter last);

        void destroy_and_recover(iterator first, iterator last, size_type n);

        // calculate the growth size
        size_type get_new_cap(size_type add_size);

        // assign
        void fill_assign(size_type n, const value_type &value);

        template <class IIter>
        void copy_assign(IIter first, IIter last, input_iterator_tag);

        template <class FIter>
        void copy_assign(FIter first, FIter last, input_iterator_tag);

        // reallocate
        template <class... Args>
        void reallocate_emplace(iterator pos, Args &&...args);
        void reallocate_insert(iterator pos, const value_type &value);

        // insert
        iterator fill_insert(iterator pos, size_type n, const value_type &value);
        template <class IIter>
        void copy_insert(iterator pos, IIter first, IIter last);

        // shrink_to_fit
        void reinsert(size_type size);
    };

    /*****************************************************************************************/
    // helper function
    // try_init ������������ʧ������ԣ����׳��쳣
    template <class T>
    void vector<T>::try_init() noexcept
    {
    }

}
#endif