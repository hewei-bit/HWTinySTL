#ifndef HWTINYSTL_UTIL_H_
#define HWTINYSTL_UTIL_H_
// ����ļ�����һЩͨ�ù��ߣ�
// ���� move, forward, swap �Ⱥ������Լ� pair ��
#include <cstddef>

#include "type_traits.h"

namespace hwstl
{
    // move
    template <class T>
    typename std::remove_reference<T>::type &&move(T &&arg) noexcept
    {
    }
    // forward

    // swap

    // pair
    // �ṹ��ģ�� : pair
    // ����ģ������ֱ��ʾ�������ݵ�����
    // �� first �� second ���ֱ�ȡ����һ�����ݺ͵ڶ�������
}

#endif