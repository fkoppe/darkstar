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

#if !defined(___DARK___OSERROR_H)
#define ___DARK___OSERROR_H

#include <dark/core/essential.h>

typedef enum Dark_Oserror
{
    DARK_OSERROR_NONE,
    DARK_OSERROR_EPERM,
    DARK_OSERROR_ENOENT,
    DARK_OSERROR_ESRCH,
    DARK_OSERROR_EINTR,
    DARK_OSERROR_EIO,
    DARK_OSERROR_ENXIO,
    DARK_OSERROR_E2BIG,
    DARK_OSERROR_ENOEXEC,
    DARK_OSERROR_EBADF,
    DARK_OSERROR_ECHILD,
    DARK_OSERROR_EAGAIN,
    DARK_OSERROR_ENOMEM,
    DARK_OSERROR_EACCES,
    DARK_OSERROR_EFAULT,
    DARK_OSERROR_ENOTBLK,
    DARK_OSERROR_EBUSY,
    DARK_OSERROR_EEXIST,
    DARK_OSERROR_EXDEV,
    DARK_OSERROR_ENODEV,
    DARK_OSERROR_ENOTDIR,
    DARK_OSERROR_EISDIR,
    DARK_OSERROR_EINVAL,
    DARK_OSERROR_ENFILE,
    DARK_OSERROR_EMFILE,
    DARK_OSERROR_ENOTTY,
    DARK_OSERROR_ETXTBSY,
    DARK_OSERROR_EFBIG,
    DARK_OSERROR_ENOSPC,
    DARK_OSERROR_ESPIPE,
    DARK_OSERROR_EROFS,
    DARK_OSERROR_EMLINK,
    DARK_OSERROR_EPIPE,
    DARK_OSERROR_EDOM,
    DARK_OSERROR_ERANGE,
    DARK_OSERROR_EDEADLK,
    DARK_OSERROR_ENAMETOOLONG,
    DARK_OSERROR_ENOLCK,
    DARK_OSERROR_ENOSYS,
    DARK_OSERROR_ENOTEMPTY,
    DARK_OSERROR_ELOOP,
    DARK_OSERROR_ENOMSG,
    DARK_OSERROR_EIDRM,
    DARK_OSERROR_ECHRNG,
    DARK_OSERROR_EL2NSYNC,
    DARK_OSERROR_EL3HLT,
    DARK_OSERROR_EL3RST,
    DARK_OSERROR_ELNRNG,
    DARK_OSERROR_EUNATCH,
    DARK_OSERROR_ENOCSI,
    DARK_OSERROR_EL2HLT,
    DARK_OSERROR_EBADE,
    DARK_OSERROR_EBADR,
    DARK_OSERROR_EXFULL,
    DARK_OSERROR_ENOANO,
    DARK_OSERROR_EBADRQC,
    DARK_OSERROR_EBADSLT,
    DARK_OSERROR_EBFONT,
    DARK_OSERROR_ENOSTR,
    DARK_OSERROR_ENODATA,
    DARK_OSERROR_ETIME,
    DARK_OSERROR_ENOSR,
    DARK_OSERROR_ENONET,
    DARK_OSERROR_ENOPKG,
    DARK_OSERROR_EREMOTE,
    DARK_OSERROR_ENOLINK,
    DARK_OSERROR_EADV,
    DARK_OSERROR_ESRMNT,
    DARK_OSERROR_ECOMM,
    DARK_OSERROR_EPROTO,
    DARK_OSERROR_EMULTIHOP,
    DARK_OSERROR_EDOTDOT,
    DARK_OSERROR_EBADMSG,
    DARK_OSERROR_EOVERFLOW,
    DARK_OSERROR_ENOTUNIQ,
    DARK_OSERROR_EBADFD,
    DARK_OSERROR_EREMCHG,
    DARK_OSERROR_ELIBACC,
    DARK_OSERROR_ELIBBAD,
    DARK_OSERROR_ELIBSCN,
    DARK_OSERROR_ELIBMAX,
    DARK_OSERROR_ELIBEXEC,
    DARK_OSERROR_EILSEQ,
    DARK_OSERROR_ERESTART,
    DARK_OSERROR_ESTRPIPE,
    DARK_OSERROR_EUSERS,
    DARK_OSERROR_ENOTSOCK,
    DARK_OSERROR_EDESTADDRREQ,
    DARK_OSERROR_EMSGSIZE,
    DARK_OSERROR_EPROTOTYPE,
    DARK_OSERROR_ENOPROTOOPT,
    DARK_OSERROR_EPROTONOSUPPORT,
    DARK_OSERROR_ESOCKTNOSUPPORT,
    DARK_OSERROR_EOPNOTSUPP,
    DARK_OSERROR_EPFNOSUPPORT,
    DARK_OSERROR_EAFNOSUPPORT,
    DARK_OSERROR_EADDRINUSE,
    DARK_OSERROR_EADDRNOTAVAIL,
    DARK_OSERROR_ENETDOWN,
    DARK_OSERROR_ENETUNREACH,
    DARK_OSERROR_ENETRESET,
    DARK_OSERROR_ECONNABORTED,
    DARK_OSERROR_ECONNRESET,
    DARK_OSERROR_ENOBUFS,
    DARK_OSERROR_EISCONN,
    DARK_OSERROR_ENOTCONN,
    DARK_OSERROR_ESHUTDOWN,
    DARK_OSERROR_ETOOMANYREFS,
    DARK_OSERROR_ETIMEDOUT,
    DARK_OSERROR_ECONNREFUSED,
    DARK_OSERROR_EHOSTDOWN,
    DARK_OSERROR_EHOSTUNREACH,
    DARK_OSERROR_EALREADY,
    DARK_OSERROR_EINPROGRESS,
    DARK_OSERROR_ESTALE,
    DARK_OSERROR_EUCLEAN,
    DARK_OSERROR_ENOTNAM,
    DARK_OSERROR_ENAVAIL,
    DARK_OSERROR_EISNAM,
    DARK_OSERROR_EREMOTEIO,
    DARK_OSERROR_EDQUOT,
    DARK_OSERROR_ENOMEDIUM,
    DARK_OSERROR_EMEDIUMTYPE,
    DARK_OSERROR_ECANCELED,
    DARK_OSERROR_ENOKEY,
    DARK_OSERROR_EKEYEXPIRED,
    DARK_OSERROR_EKEYREVOKED,
    DARK_OSERROR_EKEYREJECTED,
    DARK_OSERROR_EOWNERDEAD,
    DARK_OSERROR_ENOTRECOVERABLE,
    DARK_OSERROR_UNKNOWN,
    ___DARK_OSERROR_MAX,
} Dark_Oserror;

Dark_Oserror dark_oserror_occured(void);

const char* dark_oserror_name(Dark_Oserror oserror_);

#endif // !defined(___DARK___OSERROR_H)
