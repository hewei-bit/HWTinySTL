#ifndef HWTINYSTL_LIST_H_
#define HWTINYSTL_LIST_H_
/**
 * @File Name: list.h
 * @Brief :������һ��ģ���� list,����һ��˫������
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 *
 */

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
    template <class T>
    struct list_node_base;
    template <class T>
    struct list_node;
    template <class T>
    struct node_traits
    {
        typedef list_node_base<T> *base_ptr;
        typedef list_node<T> *node_ptr;
    };

    //����list�Ľڵ�ṹ
    template <class T>
    struct list_node_base
    {
        typedef typename node_traits<T>::base_ptr base_ptr;
        typedef typename node_traits<T>::node_ptr node_ptr;

        base_ptr prev; //ǰһ���ڵ�
        base_ptr next; //��һ���ڵ�

        list_node_base() = default;

        base_ptr self()
        {
            return static_cast<base_ptr>(&*this);
        }

        node_ptr as_node()
        {
            return static_cast<node_ptr>(self());
        }

        void unlink()
        {
            prev = next = self();
        }
    };
    template <class T>
    struct list_node : public list_node_base<T>
    {
        typedef typename node_traits<T>::base_ptr base_ptr;
        typedef typename node_traits<T>::node_ptr node_ptr;

        T value; //������

        list_node() = default;
        list_node(const T &v) : value(v)
        {
        }
        list_node(T &&v) : value(hwstl::move(v))
        {
        }

        base_ptr as_base()
        {
            return static_cast<base_ptr>(&*this);
        }
        node_ptr self()
        {
            return static_cast<node_ptr>(&*this);
        }
    };

    //list �ĵ��������



}
#endif