#ifndef HWTINYSTL_ALLOCATOR_H_
#define HWTINYSTL_ALLOCATOR_H_
/**
 * @File Name: allocator.h
 * @Brief : allocator分配器用于管理内存Containers的分配、释放，对象的构造、析构
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-25
 *
 */
namespace hwstl
{
    //模板类：allocator
    //模板函数代表数据类型
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
        static T *allocate(size_type n);

        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_type n);

        static void construct(T *ptr);
        static void construct(T *ptr, const T &value);
        static void construct(T *ptr, T &&value);

        template <typename... Args>
        static void construct(T *ptr, Args &&...args);

        static void destroy(T *ptr);
        static void destroy(T *first, T *last);
    };

    template <typename T>
    inline T *allocator<T>::allocate()
    {
        return static_cast<T *>(::operator new(sizeof(T)));
    }

    template <typename T>
    inline T *allocator<T>::allocate(size_type n)
    {
        if (n == 0)
            return nullptr;
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }

    template <typename T>
    inline void allocator<T>::deallocate(T *ptr)
    {
        if (ptr == nullptr)
            return;
        ::operator delete(ptr);
    }

    template <typename T>
    inline void allocator<T>::deallocate(T *ptr, size_type /*size*/)
    {
        if (ptr == nullptr)
            return;
        ::operator delete(ptr);
    }

    template <typename T>
    inline void allocator<T>::construct(T *ptr)
    {
        hwstl::construct(ptr);
    }

    template <typename T>
    inline void allocator<T>::construct(T *ptr, const T &value)
    {
        hwstl::construct(ptr, value);
    }

    template <typename T>
    inline void allocator<T>::construct(T *ptr, T &&value)
    {
        hwstl::construct(ptr, hwstl::move(value));
    }

    template <typename T>
    template <typename... Args>
    inline void allocator<T>::construct(T *ptr, Args &&...args)
    {
        hwstl::construct(ptr, hwstl::forward<Args>(args)...);
    }

    template <typename T>
    inline void allocator<T>::destroy(T *ptr)
    {
        hwstl::destroy(ptr);
    }

    template <typename T>
    inline void allocator<T>::destroy(T *first, T *last)
    {
        hwstl::destroy(first, last);
    }
}

#endif