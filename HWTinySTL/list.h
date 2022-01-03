#ifndef HWTINYSTL_LIST_H_
#define HWTINYSTL_LIST_H_
/**
 * @File Name: list.h
 * @Brief :包含了一个模板类 list,这是一个双向链表
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2021-12-24
 *
 */

// 异常保证：
// mystl::list<T> 满足基本异常保证，部分函数无异常保证，并对以下等函数做强异常安全保证：
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

    //定义list的节点结构
    template <class T>
    struct list_node_base
    {
        typedef typename node_traits<T>::base_ptr base_ptr;
        typedef typename node_traits<T>::node_ptr node_ptr;

        base_ptr prev; //前一个节点
        base_ptr next; //后一个节点

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

        T value; //数据域

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

    //list 的迭代器设计



}
#endif