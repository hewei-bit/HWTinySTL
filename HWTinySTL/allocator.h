/**
 * @File Name: allocator.h
 * @Brief : allocator���ڹ����ڴ�ķ��䡢�ͷţ�����Ĺ��졢����
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-25
 *
 */

#ifndef HWTINYSTL_ALLOCATOR_H_
#define HWTINYSTL_ALLOCATOR_H_

namespace hwstl
{
    //ģ���ࣺallocator
    //ģ�庯��������������
    template <typename T>
    class allocator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        static T *allocate();
        static T allocate(size_t);

        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_type n);
    }
}

#endif