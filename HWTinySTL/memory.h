#ifndef HWTINYSTL_MEMORY_H_
#define HWTINYSTL_MEMORY_H_
/**
 * @File Name: memory.h
 * @Brief : ���߼��Ķ�̬�ڴ����
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-01-03
 * @State : finished 2022-01-13
 */

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "algobase.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"
namespace hwstl
{
    //��ȡ�����ַ
    template <typename Tp>
    inline constexpr Tp *addressof(Tp &value) noexcept
    {
        return &value;
    }

    //��ȡ �ͷ� ��ʱ������
    template <typename T>
    inline pair<T *, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T *)
    {
        if ()
    }
}
#endif