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

#include <dark/darktest.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef DARK_UNIT

static size_t DARK_TEST_NUMBER = 0;
static const char* DARK_TEST_NAME = NULL;

void dark_test_initialise(void)
{
    if(NULL != DARK_TEST_NAME)
    {
        fputs("test_initialise failed: test already initialised", stderr);
        abort();
    }

    DARK_TEST_NUMBER = 0;
    DARK_TEST_NAME = "unknown";

    DARK_DEBUG_MEMORY_TRYINITIALISE;
}

void dark_test_shutdown(void)
{
    if(NULL == DARK_TEST_NAME)
    {
        fputs("test_shutdown failed: test not initialised", stderr);
        abort();
    }

    DARK_TEST_NUMBER = 0;
    DARK_TEST_NAME = NULL;

    DARK_DEBUG_MEMORY_TRYSHUTDOWN;
}

void dark_test_name_set(const char* const name_)
{
    assert(NULL != name_);

    DARK_TEST_NUMBER++;
    DARK_TEST_NAME = name_;

    fprintf(stderr, "test#%zu: %s\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
}

void dark_test(const char* const func_, const intmax_t line_, const bool cond_, const char* const conds_)
{
    assert(NULL != func_);
    assert(0 != line_);
    //cond_
    assert(NULL != conds_);

    if(cond_)
    {
        return;
    }

    fputs("\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\n", stderr);

    if(NULL != DARK_TEST_NAME)
    {
        fprintf(stderr, "test:\t#%zu\nname:\t%s\n\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
    }


    fprintf(stderr, "cond:\t%s was false\n\nfunc:\t%s\nline:\t%" PRId64 "\n\n", conds_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_p(const char* const func_, const intmax_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const void* const a_, const void* const b_, const char* const as_, const char* const bs_)
{
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != op_);
    //eq_!
    //lt_!
    assert(eq_ || lt_);
    //nt_
    //a_
    //b_
    assert(NULL != as_);
    assert(NULL != bs_);

    bool result = false;

    const int value = memcmp(&a_, &b_, sizeof(void*));

    if(eq_ && !value)
    {
        result = true;
    }

    if(lt_ && (value < 0))
    {
        result = true;
    }

    if(nt_)
    {
        result = !result;
    }

    if(result)
    {
        return;
    }

    fputs("\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\n", stderr);

    if(NULL != DARK_TEST_NAME)
    {
        fprintf(stderr, "test:\t#%zu\nname:\t%s\n\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
    }

    fprintf(stderr, "cond:\t%s %s %s was false\n%s:\t%p\n%s:\t%p\n\nfunc:\t%s\nline:\t%" PRIdMAX "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_u(const char* const func_, const intmax_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const uintmax_t a_, const uintmax_t b_, const char* const as_, const char* const bs_)
{
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != op_);
    //eq_!
    //lt_!
    assert(eq_ || lt_);
    //nt_
    //a_
    //b_
    assert(NULL != as_);
    assert(NULL != bs_);

    bool result = false;

    if(eq_ && (a_ == b_))
    {
        result = true;
    }

    if(lt_ && (a_ < b_))
    {
        result = true;
    }

    if(nt_)
    {
        result = !result;
    }

    if(result)
    {
        return;
    }

    fputs("\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\n", stderr);

    if(NULL != DARK_TEST_NAME)
    {
        fprintf(stderr, "test:\t#%zu\nname:\t%s\n\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
    }

    fprintf(stderr, "cond:\t%s %s %s was false\n%s:\t%" PRIuMAX "\n%s:\t%" PRIuMAX "\n\nfunc:\t%s\nline:\t%" PRIdMAX "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_i(const char* const func_, const intmax_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const intmax_t a_, const intmax_t b_, const char* const as_, const char* const bs_)
{
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != op_);
    //eq_!
    //lt_!
    assert(eq_ || lt_);
    //nt_
    //a_
    //b_
    assert(NULL != as_);
    assert(NULL != bs_);

    bool result = false;

    if(eq_ && (a_ == b_))
    {
        result = true;
    }

    if(lt_ && (a_ < b_))
    {
        result = true;
    }

    if(nt_)
    {
        result = !result;
    }

    if(result)
    {
        return;
    }

    fputs("\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\n", stderr);

    if(NULL != DARK_TEST_NAME)
    {
        fprintf(stderr, "test:\t#%zu\nname:\t%s\n\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
    }

    fprintf(stderr, "cond:\t%s %s %s was false\n%s:\t%" PRIdMAX "\n%s:\t%" PRIdMAX "\n\nfunc:\t%s\nline:\t%" PRIdMAX "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_f(const char* const func_, const intmax_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const float a_, const float b_, const char* const as_, const char* const bs_)
{
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != op_);
    //eq_!
    //lt_!
    assert(eq_ || lt_);
    //nt_
    //a_
    //b_
    assert(NULL != as_);
    assert(NULL != bs_);

    bool result = false;

    if(eq_ && (a_ == b_))
    {
        result = true;
    }

    if(lt_ && (a_ < b_))
    {
        result = true;
    }

    if(nt_)
    {
        result = !result;
    }

    if(result)
    {
        return;
    }

    fputs("\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\n", stderr);

    if(NULL != DARK_TEST_NAME)
    {
        fprintf(stderr, "test:\t#%zu\nname:\t%s\n\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
    }

    fprintf(stderr, "cond:\t%s %s %s was false\n%s:\t%f\n%s:\t%f\n\nfunc:\t%s\nline:\t%" PRIdMAX "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_d(const char* const func_, const intmax_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const double a_, const double b_, const char* const as_, const char* const bs_)
{
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != op_);
    //eq_!
    //lt_!
    assert(eq_ || lt_);
    //nt_
    //a_
    //b_
    assert(NULL != as_);
    assert(NULL != bs_);

    bool result = false;

    if(eq_ && (a_ == b_))
    {
        result = true;
    }

    if(lt_ && (a_ < b_))
    {
        result = true;
    }

    if(nt_)
    {
        result = !result;
    }

    if(result)
    {
        return;
    }

    fputs("\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\n", stderr);

    if(NULL != DARK_TEST_NAME)
    {
        fprintf(stderr, "test:\t#%zu\nname:\t%s\n\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
    }

    fprintf(stderr, "cond:\t%s %s %s was false\n%s:\t%lf\n%s:\t%lf\n\nfunc:\t%s\nline:\t%" PRIdMAX "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_s(const char* const func_, const intmax_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const char* const a_, const char* const b_, const size_t size_, const char* const as_, const char* const bs_)
{
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != op_);
    //eq_!
    //lt_!
    assert(eq_ || lt_);
    //nt_
    //a_
    //b_
    //size_
    assert(NULL != as_);
    assert(NULL != bs_);

    if(0 == size_)
    {
        return;
    }

    bool result = false;

    if(eq_ && !memcmp(a_, b_, size_))
    {
        result = true;
    }

    if(lt_ && (memcmp(a_, b_, size_) < 0))
    {
        result = true;
    }

    if(nt_)
    {
        result = !result;
    }

    if(result)
    {
        return;
    }

    fputs("\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\n", stderr);

    if(NULL != DARK_TEST_NAME)
    {
        fprintf(stderr, "test:\t#%zu\nname:\t%s\n\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
    }

    fprintf(stderr, "cond:\t%s %s %s was false\n%s:\t%s\n%s:\t%s\n\nfunc:\t%s\nline:\t%" PRIdMAX "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_m(const char* const func_, const intmax_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, void* const a_, void* const b_, const size_t size_, const char* const as_, const char* const bs_)
{
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != op_);
    //eq_!
    //lt_!
    assert(eq_ || lt_);
    //nt_
    //a_
    //b_
    //size_
    assert(NULL != as_);
    assert(NULL != bs_);

    if(0 == size_)
    {
        return;
    }

    bool result = false;

    const int value = memcmp(a_, b_, size_);

    if(eq_ && !value)
    {
        result = true;
    }

    if(lt_ && (value < 0))
    {
        result = true;
    }

    if(nt_)
    {
        result = !result;
    }

    if(result)
    {
        return;
    }

    fputs("\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\n", stderr);

    if(NULL != DARK_TEST_NAME)
    {
        fprintf(stderr, "test:\t#%zu\nname:\t%s\n\n", DARK_TEST_NUMBER, DARK_TEST_NAME);
    }

    fprintf(stderr, "cond:\t%s %s %s was false\n\nfunc:\t%s\nline:\t%" PRIdMAX "\n\n", as_, op_, bs_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}
