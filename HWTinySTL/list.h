/**
 * @File Name: list.h
 * @Brief :
 * @Author : name (xx@foxmail.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-19
 *
 */

#ifndef HWTINYSTL_LIST_H_
#define HWTINYSTL_LIST_H_

//���ͷ�ļ�������һ��ģ���� list
//����һ��˫������
// �쳣��֤��
// mystl::list<T> ��������쳣��֤�����ֺ������쳣��֤���������µȺ�����ǿ�쳣��ȫ��֤��
//   * emplace_front
//   * emplace_back
//   * emplace
//   * push_front
//   * push_back
//   * insert
#include <initializer_list>

#include "iterator.h"
#include "memory.h"
#include "functional.h"
#include "util.h"
#include "exceptdef.h"
namespace hwstl
{
    template <calss T>
    struct list_node_base;
    template <class T>
    struct list_node;
    template <class T>
    struct node_traits
    {
        typedef list_node_base<T> *base_ptr;
        typedef list_node<T> *node_ptr;
    }

}
#endif