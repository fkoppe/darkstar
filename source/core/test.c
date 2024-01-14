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

/*X X X X X X X X X X X X X X
X                           X
X   THIS IS A CORE FILE     X
X                           X
X X X X X X X X X X X X X X*/

#include "core_helper.h"
#include "core_module.h"

#include <dark/core/core.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

#undef DARK_UNIT

void dark_test_u(const char* const func_, const int64_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const uint64_t a_, const uint64_t b_, const char* const as_, const char* const bs_)
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

    fprintf(stderr, "\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\ncond:\t%s %s %s was false\n%s:\t%" PRIu64 "\n%s:\t%" PRIu64 "\n\nfunc:\t%s\nline:\t%" PRId64 "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_i(const char* const func_, const int64_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const int64_t a_, const int64_t b_, const char* const as_, const char* const bs_)
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

    fprintf(stderr, "\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\ncond:\t%s %s %s was false\n%s:\t%" PRId64 "\n%s:\t%" PRId64 "\n\nfunc:\t%s\nline:\t%" PRId64 "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_f(const char* const func_, const int64_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const float a_, const float b_, const char* const as_, const char* const bs_)
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

    fprintf(stderr, "\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\ncond:\t%s %s %s was false\n%s:\t%f\n%s:\t%f\n\nfunc:\t%s\nline:\t%" PRId64 "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_d(const char* const func_, const int64_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const double a_, const double b_, const char* const as_, const char* const bs_)
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

    fprintf(stderr, "\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\ncond:\t%s %s %s was false\n%s:\t%lf\n%s:\t%lf\n\nfunc:\t%s\nline:\t%" PRId64 "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_s(const char* const func_, const int64_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, const char* const a_, const char* const b_, const size_t size_, const char* const as_, const char* const bs_)
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

    fprintf(stderr, "\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\ncond:\t%s %s %s was false\n%s:\t%s\n%s:\t%s\n\nfunc:\t%s\nline:\t%" PRId64 "\n\n", as_, op_, bs_, as_, a_, bs_, b_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}

void dark_test_m(const char* const func_, const int64_t line_, const char* const op_, const bool eq_, const bool lt_, const bool nt_, void* const a_, void* const b_, const size_t size_, const char* const as_, const char* const bs_)
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

    fprintf(stderr, "\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\ncond:\t%s %s %s was false\n\nfunc:\t%s\nline:\t%" PRId64 "\n\n", as_, op_, bs_, func_, line_);

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}
