/**
 * @file mla.h
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Unified header file.
 * @version 1.0
 * @date 2023.11.01
 *
 * @copyright Copyright (c) 2023
 */

#ifndef MLA_H
#define MLA_H

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)

#include "Matrix.h"
#include "Vector.h"

#else
#error "Require at least C++17."

#endif // C++17

#endif // MLA_H
