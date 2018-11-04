/**
 * \file utility.hpp
 * \brief 便利マクロ群。
 * \author Takuya Itoh
 */

#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

#include <stddef.h>

/// 安全なメモリ解放
/// \param[in] p ポインタ
#define SDELETE(p)		{ if (p) { delete p;   p = NULL; } }

/// 安全なメモリ解放（配列）
/// \param[in] p ポインタ（配列）
#define SDELETE_ARRAY(p) { if (p) { delete[] p; p = NULL; } }

#endif	// UTILITY_HPP_INCLUDED
