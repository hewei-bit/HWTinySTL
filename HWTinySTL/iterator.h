/**
 * @File Name: iterator.h
 * @Brief : ���ڵ�������ƣ�������һЩģ��ṹ����ȫ�ֺ�����
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 *
 */

#include <cstddef>

#include "type_traits.h"
namespace hwstl
{
    //���ֵ�����:
    struct input_iterator_tag
    {
    };
    struct output_iterator_tag
    {
    };
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    struct bi

}