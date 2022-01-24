#ifndef HWTINYSTL_EXCEPTDEF_H_
#define HWTINYSTL_EXCEPTDEF_H_
/**
 * @File Name: exceptdef.h
 * @Brief :
 * @Author : hewei (hewei_1996@qq.com)
 * @Version : 1.0
 * @Creat Date : 2022-01-03
 * @State : finished 2022-01-13
 */
#include <stdexcept>

#include <cassert>
namespace hwstl
{
#define MYSTL_DEBUG(expr) \
    assert(expr)

#define THROW_LENGTH_ERROR_IF(expr, what) \
    if ((expr))                           \
    throw std::length_error(what)

#define THROW_OUT_OF_RANGE_IF(expr, what) \
    if ((expr))                           \
    throw std::out_of_range(what)

#define THROW_RUNTIME_ERROR_IF(expr, what) \
    if ((expr))                            \
    throw std::runtime_error(what)
}

#endif