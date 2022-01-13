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

}
#endif