/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2024 Felix Koppe <fkoppe@web.de>                             *
*                                                                                   *
*   This program is free software: you can redistribute it and/or modify            *
*   it under the terms of the GNU Affero General Public License as published        *
*   by the Free Software Foundation, either version 3 of the License, or            *
*   (at your option) any later version.                                             *
*                                                                                   *
*   This program is distributed in the hope that it will be useful,                 *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   *
*   GNU Affero General Public License for more details.                             *
*                                                                                   *
*   You should have received a copy of the GNU Affero General Public License        *
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.          *
*                                                                                   *
************************************************************************************/

#if !defined(___DARK___TEST_H)
#define ___DARK___TEST_H

#include <dark/core/essential.h>

#define DARK_TEST(name) \
dark_test_name_set(name);

#define DARK_TEST_TRUE(cond) dark_test(__func__, __LINE__, (cond), #cond)
#define DARK_TEST_FALSE(cond) dark_test(__func__, __LINE__, (!cond), "!"#cond)

#define DARK_TEST_EQ_P(a, b) dark_test_p(__func__, __LINE__, "==", true, false, false, (a), (b), #a, #b)
#define DARK_TEST_NE_P(a, b) dark_test_p(__func__, __LINE__, "!=", true, false, true, (a), (b), #a, #b)
#define DARK_TEST_LT_P(a, b) dark_test_p(__func__, __LINE__, "<", false, true, false, (a), (b), #a, #b)
#define DARK_TEST_LE_P(a, b) dark_test_p(__func__, __LINE__, "<=", true, true, false, (a), (b), #a, #b)
#define DARK_TEST_GT_P(a, b) dark_test_p(__func__, __LINE__, ">", true, true, true, (a), (b), #a, #b)
#define DARK_TEST_GE_P(a, b) dark_test_p(__func__, __LINE__, ">=", false, true, true, (a), (b), #a, #b)

#define DARK_TEST_EQ_U(a, b) dark_test_u(__func__, __LINE__, "==", true, false, false, (a), (b), #a, #b)
#define DARK_TEST_NE_U(a, b) dark_test_u(__func__, __LINE__, "!=", true, false, true, (a), (b), #a, #b)
#define DARK_TEST_LT_U(a, b) dark_test_u(__func__, __LINE__, "<", false, true, false, (a), (b), #a, #b)
#define DARK_TEST_LE_U(a, b) dark_test_u(__func__, __LINE__, "<=", true, true, false, (a), (b), #a, #b)
#define DARK_TEST_GT_U(a, b) dark_test_u(__func__, __LINE__, ">", true, true, true, (a), (b), #a, #b)
#define DARK_TEST_GE_U(a, b) dark_test_u(__func__, __LINE__, ">=", false, true, true, (a), (b), #a, #b)

#define DARK_TEST_EQ_I(a, b) dark_test_i(__func__, __LINE__, "==", true, false, false, (a), (b), #a, #b)
#define DARK_TEST_NE_I(a, b) dark_test_i(__func__, __LINE__, "!=", true, false, true, (a), (b), #a, #b)
#define DARK_TEST_LT_I(a, b) dark_test_i(__func__, __LINE__, "<", false, true, false, (a), (b), #a, #b)
#define DARK_TEST_LE_I(a, b) dark_test_i(__func__, __LINE__, "<=", true, true, false, (a), (b), #a, #b)
#define DARK_TEST_GT_I(a, b) dark_test_i(__func__, __LINE__, ">", true, true, true, (a), (b), #a, #b)
#define DARK_TEST_GE_I(a, b) dark_test_i(__func__, __LINE__, ">=", false, true, true, (a), (b), #a, #b)

#define DARK_TEST_EQ_F(a, b) dark_test_f(__func__, __LINE__, "==", true, false, false, (a), (b), #a, #b)
#define DARK_TEST_NE_F(a, b) dark_test_f(__func__, __LINE__, "!=", true, false, true, (a), (b), #a, #b)
#define DARK_TEST_LT_F(a, b) dark_test_f(__func__, __LINE__, "<", false, true, false, (a), (b), #a, #b)
#define DARK_TEST_LE_F(a, b) dark_test_f(__func__, __LINE__, "<=", true, true, false, (a), (b), #a, #b)
#define DARK_TEST_GT_F(a, b) dark_test_f(__func__, __LINE__, ">", true, true, true, (a), (b), #a, #b)
#define DARK_TEST_GE_F(a, b) dark_test_f(__func__, __LINE__, ">=", false, true, true, (a), (b), #a, #b)

#define DARK_TEST_EQ_D(a, b) dark_test_d(__func__, __LINE__, "==", true, false, false, (a), (b), #a, #b)
#define DARK_TEST_NE_D(a, b) dark_test_d(__func__, __LINE__, "!=", true, false, true, (a), (b), #a, #b)
#define DARK_TEST_LT_D(a, b) dark_test_d(__func__, __LINE__, "<", false, true, false, (a), (b), #a, #b)
#define DARK_TEST_LE_D(a, b) dark_test_d(__func__, __LINE__, "<=", true, true, false, (a), (b), #a, #b)
#define DARK_TEST_GT_D(a, b) dark_test_d(__func__, __LINE__, ">", true, true, true, (a), (b), #a, #b)
#define DARK_TEST_GE_D(a, b) dark_test_d(__func__, __LINE__, ">=", false, true, true, (a), (b), #a, #b)

#define DARK_TEST_EQ_S(a, b, s) dark_test_s(__func__, __LINE__, "==", true, false, false, (a), (b), (s), #a, #b)
#define DARK_TEST_NE_S(a, b, s) dark_test_s(__func__, __LINE__, "!=", true, false, true, (a), (b), (s), #a, #b)
#define DARK_TEST_LT_S(a, b, s) dark_test_s(__func__, __LINE__, "<", false, true, false, (a), (b), (s), #a, #b)
#define DARK_TEST_LE_S(a, b, s) dark_test_s(__func__, __LINE__, "<=", true, true, false, (a), (b), (s), #a, #b)
#define DARK_TEST_GT_S(a, b, s) dark_test_s(__func__, __LINE__, ">", true, true, true, (a), (b), (s), #a, #b)
#define DARK_TEST_GE_S(a, b, s) dark_test_s(__func__, __LINE__, ">=", false, true, true, (a), (b), (s), #a, #b)

#define DARK_TEST_EQ_M(a, b, s) dark_test_m(__func__, __LINE__, "==", true, false, false, (a), (b), (s), #a, #b)
#define DARK_TEST_NE_M(a, b, s) dark_test_m(__func__, __LINE__, "!=", true, false, true, (a), (b), (s), #a, #b)
#define DARK_TEST_LT_M(a, b, s) dark_test_m(__func__, __LINE__, "<", false, true, false, (a), (b), (s), #a, #b)
#define DARK_TEST_LE_M(a, b, s) dark_test_m(__func__, __LINE__, "<=", true, true, false, (a), (b), (s), #a, #b)
#define DARK_TEST_GT_M(a, b, s) dark_test_m(__func__, __LINE__, ">", true, true, true, (a), (b), (s), #a, #b)
#define DARK_TEST_GE_M(a, b, s) dark_test_m(__func__, __LINE__, ">=", false, true, true, (a), (b), (s), #a, #b)

void dark_test_name_set(const char* name);
void dark_test_end(void);

void dark_test(const char* func, int64_t line, bool cond, const char* conds);
void dark_test_p(const char* func, int64_t line, const char* op, bool eq, bool lt, bool nt, const void* a, const void* b, const char* as, const char* bs);
void dark_test_u(const char* func, int64_t line, const char* op, bool eq, bool lt, bool nt, uintmax_t a, uintmax_t b, const char* as, const char* bs);
void dark_test_i(const char* func, int64_t line, const char* op, bool eq, bool lt, bool nt, intmax_t a, intmax_t b, const char* as, const char* bs);
void dark_test_f(const char* func, int64_t line, const char* op, bool eq, bool lt, bool nt, float a, float b, const char* as, const char* bs);
void dark_test_d(const char* func, int64_t line, const char* op, bool eq, bool lt, bool nt, double a, double b, const char* as, const char* bs);
void dark_test_s(const char* func, int64_t line, const char* op, bool eq, bool lt, bool nt, const char* a, const char* b, size_t size, const char* as, const char* bs);
void dark_test_m(const char* func, int64_t line, const char* op, bool eq, bool lt, bool nt, void* a, void* b, size_t size, const char* as, const char* bs);

#endif // !defined(___DARK___TEST_H)
