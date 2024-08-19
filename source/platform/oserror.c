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

#include "platform_module.h"

#include <dark/core/core.h>
#include <dark/platform/platform.h>

#include <errno.h>

#undef DARK_UNIT
#define DARK_UNIT "oserror"

bool dark_oserror_occured_is(void)
{
    return errno != 0;
}

Dark_Oserror dark_oserror_occured(void)
{
    const int64_t value = errno;
    errno = 0;

#if defined(___DARK_WINDOWS)
    switch(value)
    {
        case 1:
            return DARK_OSERROR_EPERM;
        case 2:
            return DARK_OSERROR_ENOENT;
        case 3:
            return DARK_OSERROR_ESRCH;
        case 4:
            return DARK_OSERROR_EINTR;
        case 5:
            return DARK_OSERROR_EIO;
        case 6:
            return DARK_OSERROR_ENXIO;
        case 7:
            return DARK_OSERROR_E2BIG;
        case 8:
            return DARK_OSERROR_ENOEXEC;
        case 9:
            return DARK_OSERROR_EBADF;
        case 10:
            return DARK_OSERROR_ECHILD;
        case 11:
            return DARK_OSERROR_EAGAIN;
        case 12:
            return DARK_OSERROR_ENOMEM;
        case 13:
            return DARK_OSERROR_EACCES;
        case 14:
            return DARK_OSERROR_EFAULT;
        case 17:
            return DARK_OSERROR_EEXIST;
        case 18:
            return DARK_OSERROR_EXDEV;
        case 19:
            return DARK_OSERROR_ENODEV;
        case 20:
            return DARK_OSERROR_ENOTDIR;
        case 21:
            return DARK_OSERROR_EISDIR;
        case 22:
            return DARK_OSERROR_EINVAL;
        case 23:
            return DARK_OSERROR_ENFILE;
        case 24:
            return DARK_OSERROR_EMFILE;
        case 25:
            return DARK_OSERROR_ENOTTY;
        case 27:
            return DARK_OSERROR_EFBIG;
        case 28:
            return DARK_OSERROR_ENOSPC;
        case 29:
            return DARK_OSERROR_ESPIPE;
        case 30:
            return DARK_OSERROR_EROFS;
        case 32:
            return DARK_OSERROR_EPIPE;
        case 33:
            return DARK_OSERROR_EDOM;
        case 34:
            return DARK_OSERROR_ERANGE;
        case 36:
            return DARK_OSERROR_EDEADLK;
        case 38:
            return DARK_OSERROR_ENAMETOOLONG;
        case 39:
            return DARK_OSERROR_ENOLCK;
        case 40:
            return DARK_OSERROR_ENOSYS;
        case 41:
            return DARK_OSERROR_ENOTEMPTY;
        case 42:
            return DARK_OSERROR_EILSEQ;
        case 80:
            return DARK_OSERROR_STRUNCATE;
        case 100:
            return DARK_OSERROR_EADDRINUSE;
        case 101:
            return DARK_OSERROR_EADDRNOTAVAIL;
        case 102:
            return DARK_OSERROR_EAFNOSUPPORT;
        case 103:
            return DARK_OSERROR_EALREADY;
        case 104:
            return DARK_OSERROR_EBADMSG;
        case 105:
            return DARK_OSERROR_ECANCELED;
        case 106:
            return DARK_OSERROR_ECONNABORTED;
        case 107:
            return DARK_OSERROR_ECONNREFUSED;
        case 108:
            return DARK_OSERROR_ECONNRESET;
        case 109:
            return DARK_OSERROR_EDESTADDRREQ;
        case 110:
            return DARK_OSERROR_EHOSTUNREACH;
        case 111:
            return DARK_OSERROR_EIDRM;
        case 112:
            return DARK_OSERROR_EINPROGRESS;
        case 113:
            return DARK_OSERROR_EISCONN;
        case 114:
            return DARK_OSERROR_ELOOP;
        case 115:
            return DARK_OSERROR_EMSGSIZE;
        case 116:
            return DARK_OSERROR_ENETDOWN;
        case 117:
            return DARK_OSERROR_ENETRESET;
        case 118:
            return DARK_OSERROR_ENETUNREACH;
        case 119:
            return DARK_OSERROR_ENOBUFS;
        case 120:
            return DARK_OSERROR_ENODATA;
        case 121:
            return DARK_OSERROR_ENOLINK;
        case 122:
            return DARK_OSERROR_ENOMSG;
        case 123:
            return DARK_OSERROR_ENOPROTOOPT;
        case 124:
            return DARK_OSERROR_ENOSR;
        case 125:
            return DARK_OSERROR_ENOSTR;
        case 126:
            return  DARK_OSERROR_ENOTCONN;
        case 127:
            return DARK_OSERROR_ENOTRECOVERABLE;
        case 128:
            return DARK_OSERROR_ENOTSOCK;
        case 129:
            return DARK_OSERROR_ENOTSUP;
        case 130:
            return DARK_OSERROR_EOPNOTSUPP;
        case 131:
            return DARK_OSERROR_EOTHER;
        case 132:
            return DARK_OSERROR_EOVERFLOW;
        case 133:
            return DARK_OSERROR_EOWNERDEAD;
        case 134:
            return DARK_OSERROR_EPROTO;
        case 135:
            return DARK_OSERROR_EPROTONOSUPPORT;
        case 136:
            return DARK_OSERROR_EPROTOTYPE;
        case 137:
            return DARK_OSERROR_ETIME;
        case 138:
            return DARK_OSERROR_ETIMEDOUT;
        case 139:
            return DARK_OSERROR_ETXTBSY;
        case 140:
            return DARK_OSERROR_EWOULDBLOCK;
        default:
            return DARK_OSERROR_UNKNOWN;
    }
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    switch (value)
    {
    case EPERM:
        return DARK_OSERROR_EPERM;
    case ENOENT:
        return DARK_OSERROR_ENOENT;
    case ESRCH:
        return DARK_OSERROR_ESRCH;
    case EINTR:
        return DARK_OSERROR_EINTR;
    case EIO:
        return DARK_OSERROR_EIO;
    case ENXIO:
        return DARK_OSERROR_ENXIO;
    case E2BIG:
        return DARK_OSERROR_E2BIG;
    case ENOEXEC:
        return DARK_OSERROR_ENOEXEC;
    case EBADF:
        return DARK_OSERROR_EBADF;
    case ECHILD:
        return DARK_OSERROR_ECHILD;
    case EAGAIN:
        return DARK_OSERROR_EAGAIN;
    case ENOMEM:
        return DARK_OSERROR_ENOMEM;
    case EACCES:
        return DARK_OSERROR_EACCES;
    case EFAULT:
        return DARK_OSERROR_EFAULT;
    case ENOTBLK:
        return DARK_OSERROR_ENOTBLK;
    case EBUSY:
        return DARK_OSERROR_EBUSY;
    case EEXIST:
        return DARK_OSERROR_EEXIST;
    case EXDEV:
        return DARK_OSERROR_EXDEV;
    case ENODEV:
        return DARK_OSERROR_ENODEV;
    case ENOTDIR:
        return DARK_OSERROR_ENOTDIR;
    case EISDIR:
        return DARK_OSERROR_EISDIR;
    case EINVAL:
        return DARK_OSERROR_EINVAL;
    case ENFILE:
        return DARK_OSERROR_ENFILE;
    case EMFILE:
        return DARK_OSERROR_EMFILE;
    case ENOTTY:
        return DARK_OSERROR_ENOTTY;
    case ETXTBSY:
        return DARK_OSERROR_ETXTBSY;
    case EFBIG:
        return DARK_OSERROR_EFBIG;
    case ENOSPC:
        return DARK_OSERROR_ENOSPC;
    case ESPIPE:
        return DARK_OSERROR_ESPIPE;
    case EROFS:
        return DARK_OSERROR_EROFS;
    case EMLINK:
        return DARK_OSERROR_EMLINK;
    case EPIPE:
        return DARK_OSERROR_EPIPE;
    case EDOM:
        return DARK_OSERROR_EDOM;
    case ERANGE:
        return DARK_OSERROR_ERANGE;
    case EDEADLK:
        return DARK_OSERROR_EDEADLK;
    case ENAMETOOLONG:
        return DARK_OSERROR_ENAMETOOLONG;
    case ENOLCK:
        return DARK_OSERROR_ENOLCK;
    case ENOSYS:
        return DARK_OSERROR_ENOSYS;
    case ENOTEMPTY:
        return DARK_OSERROR_ENOTEMPTY;
    case ELOOP:
        return DARK_OSERROR_ELOOP;
    case ENOMSG:
        return DARK_OSERROR_ENOMSG;
    case EIDRM:
        return DARK_OSERROR_EIDRM;
    case ECHRNG:
        return DARK_OSERROR_ECHRNG;
    case EL2NSYNC:
        return DARK_OSERROR_EL2NSYNC;
    case EL3HLT:
        return DARK_OSERROR_EL3HLT;
    case EL3RST:
        return DARK_OSERROR_EL3RST;
    case ELNRNG:
        return DARK_OSERROR_ELNRNG;
    case EUNATCH:
        return DARK_OSERROR_EUNATCH;
    case ENOCSI:
        return DARK_OSERROR_ENOCSI;
    case EL2HLT:
        return DARK_OSERROR_EL2HLT;
    case EBADE:
        return DARK_OSERROR_EBADE;
    case EBADR:
        return DARK_OSERROR_EBADR;
    case EXFULL:
        return DARK_OSERROR_EXFULL;
    case ENOANO:
        return DARK_OSERROR_ENOANO;
    case EBADRQC:
        return DARK_OSERROR_EBADRQC;
    case EBADSLT:
        return DARK_OSERROR_EBADSLT;
    case EBFONT:
        return DARK_OSERROR_EBFONT;
    case ENOSTR:
        return DARK_OSERROR_ENOSTR;
    case ENODATA:
        return DARK_OSERROR_ENODATA;
    case ETIME:
        return DARK_OSERROR_ETIME;
    case ENOSR:
        return DARK_OSERROR_ENOSR;
    case ENONET:
        return DARK_OSERROR_ENONET;
    case ENOPKG:
        return DARK_OSERROR_ENOPKG;
    case EREMOTE:
        return DARK_OSERROR_EREMOTE;
    case ENOLINK:
        return DARK_OSERROR_ENOLINK;
    case EADV:
        return DARK_OSERROR_EADV;
    case ESRMNT:
        return DARK_OSERROR_ESRMNT;
    case ECOMM:
        return DARK_OSERROR_ECOMM;
    case EPROTO:
        return DARK_OSERROR_EPROTO;
    case EMULTIHOP:
        return DARK_OSERROR_EMULTIHOP;
    case EDOTDOT:
        return DARK_OSERROR_EDOTDOT;
    case EBADMSG:
        return DARK_OSERROR_EBADMSG;
    case EOVERFLOW:
        return DARK_OSERROR_EOVERFLOW;
    case ENOTUNIQ:
        return DARK_OSERROR_ENOTUNIQ;
    case EBADFD:
        return DARK_OSERROR_EBADFD;
    case EREMCHG:
        return DARK_OSERROR_EREMCHG;
    case ELIBACC:
        return DARK_OSERROR_ELIBACC;
    case ELIBBAD:
        return DARK_OSERROR_ELIBBAD;
    case ELIBSCN:
        return DARK_OSERROR_ELIBSCN;
    case ELIBMAX:
        return DARK_OSERROR_ELIBMAX;
    case ELIBEXEC:
        return DARK_OSERROR_ELIBEXEC;
    case EILSEQ:
        return DARK_OSERROR_EILSEQ;
    case ERESTART:
        return DARK_OSERROR_ERESTART;
    case ESTRPIPE:
        return DARK_OSERROR_ESTRPIPE;
    case EUSERS:
        return DARK_OSERROR_EUSERS;
    case ENOTSOCK:
        return DARK_OSERROR_ENOTSOCK;
    case EDESTADDRREQ:
        return DARK_OSERROR_EDESTADDRREQ;
    case EMSGSIZE:
        return DARK_OSERROR_EMSGSIZE;
    case EPROTOTYPE:
        return DARK_OSERROR_EPROTOTYPE;
    case ENOPROTOOPT:
        return DARK_OSERROR_ENOPROTOOPT;
    case EPROTONOSUPPORT:
        return DARK_OSERROR_EPROTONOSUPPORT;
    case ESOCKTNOSUPPORT:
        return DARK_OSERROR_ESOCKTNOSUPPORT;
    case EOPNOTSUPP:
        return DARK_OSERROR_EOPNOTSUPP;
    case EPFNOSUPPORT:
        return DARK_OSERROR_EPFNOSUPPORT;
    case EAFNOSUPPORT:
        return DARK_OSERROR_EAFNOSUPPORT;
    case EADDRINUSE:
        return DARK_OSERROR_EADDRINUSE;
    case EADDRNOTAVAIL:
        return DARK_OSERROR_EADDRNOTAVAIL;
    case ENETDOWN:
        return DARK_OSERROR_ENETDOWN;
    case ENETUNREACH:
        return DARK_OSERROR_ENETUNREACH;
    case ENETRESET:
        return DARK_OSERROR_ENETRESET;
    case ECONNABORTED:
        return DARK_OSERROR_ECONNABORTED;
    case ECONNRESET:
        return DARK_OSERROR_ECONNRESET;
    case ENOBUFS:
        return DARK_OSERROR_ENOBUFS;
    case EISCONN:
        return DARK_OSERROR_EISCONN;
    case ENOTCONN:
        return DARK_OSERROR_ENOTCONN;
    case ESHUTDOWN:
        return DARK_OSERROR_ESHUTDOWN;
    case ETOOMANYREFS:
        return DARK_OSERROR_ETOOMANYREFS;
    case ETIMEDOUT:
        return DARK_OSERROR_ETIMEDOUT;
    case ECONNREFUSED:
        return DARK_OSERROR_ECONNREFUSED;
    case EHOSTDOWN:
        return DARK_OSERROR_EHOSTDOWN;
    case EHOSTUNREACH:
        return DARK_OSERROR_EHOSTUNREACH;
    case EALREADY:
        return DARK_OSERROR_EALREADY;
    case EINPROGRESS:
        return DARK_OSERROR_EINPROGRESS;
    case ESTALE:
        return DARK_OSERROR_ESTALE;
    case EUCLEAN:
        return DARK_OSERROR_EUCLEAN;
    case ENOTNAM:
        return DARK_OSERROR_ENOTNAM;
    case ENAVAIL:
        return DARK_OSERROR_ENAVAIL;
    case EISNAM:
        return DARK_OSERROR_EISNAM;
    case EREMOTEIO:
        return DARK_OSERROR_EREMOTEIO;
    case EDQUOT:
        return DARK_OSERROR_EDQUOT;
    case ENOMEDIUM:
        return DARK_OSERROR_ENOMEDIUM;
    case EMEDIUMTYPE:
        return DARK_OSERROR_EMEDIUMTYPE;
    case ECANCELED:
        return DARK_OSERROR_ECANCELED;
    case ENOKEY:
        return DARK_OSERROR_ENOKEY;
    case EKEYEXPIRED:
        return DARK_OSERROR_EKEYEXPIRED;
    case EKEYREVOKED:
        return DARK_OSERROR_EKEYREVOKED;
    case EKEYREJECTED:
        return DARK_OSERROR_EKEYREJECTED;
    case EOWNERDEAD:
        return DARK_OSERROR_EOWNERDEAD;
    case ENOTRECOVERABLE:
        return DARK_OSERROR_ENOTRECOVERABLE;
    default:
        return DARK_OSERROR_UNKNOWN;
    }
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)
}

const char* dark_oserror_name(const Dark_Oserror oserror_)
{
    DARK_ASSERT( ___DARK_OSERROR_MIN < oserror_ && oserror_ < ___DARK_OSERROR_MAX, DARK_ERROR_ENUM);

    switch (oserror_)
    {
    case DARK_OSERROR_NONE:
       return "no error occured";
    case DARK_OSERROR_EPERM:
        return "operation not permitted";
    case DARK_OSERROR_ENOENT:
        return "no such file or directory";
    case DARK_OSERROR_ESRCH:
        return "no such process";
    case DARK_OSERROR_EINTR:
        return "interrupted system call";
    case DARK_OSERROR_EIO:
        return "i/o error";
    case DARK_OSERROR_ENXIO:
        return "no such device or address";
    case DARK_OSERROR_E2BIG:
        return "argument list too long";
    case DARK_OSERROR_ENOEXEC:
        return "exec format error";
    case DARK_OSERROR_EBADF:
        return "bad file number";
    case DARK_OSERROR_ECHILD:
        return "no child processes";
    case DARK_OSERROR_EAGAIN:
        return "try again";
    case DARK_OSERROR_ENOMEM:
        return "out of memory";
    case DARK_OSERROR_EACCES:
        return "permission denied";
    case DARK_OSERROR_EFAULT:
        return "bad address";
    case DARK_OSERROR_ENOTBLK:
        return "block device required";
    case DARK_OSERROR_EBUSY:
        return "device or resource busy";
    case DARK_OSERROR_EEXIST:
        return "file exists";
    case DARK_OSERROR_EXDEV:
        return "cross-device link";
    case DARK_OSERROR_ENODEV:
        return "no such device";
    case DARK_OSERROR_ENOTDIR:
        return "not a directory";
    case DARK_OSERROR_EISDIR:
        return "is a directory";
    case DARK_OSERROR_EINVAL:
        return "invalid argument";
    case DARK_OSERROR_ENFILE:
        return "file table overflow";
    case DARK_OSERROR_EMFILE:
        return "too many open files";
    case DARK_OSERROR_ENOTTY:
        return "not a typewriter";
    case DARK_OSERROR_ETXTBSY:
        return "text file busy";
    case DARK_OSERROR_EFBIG:
        return "file too large";
    case DARK_OSERROR_ENOSPC:
        return "no space left on device";
    case DARK_OSERROR_ESPIPE:
        return "illegal seek";
    case DARK_OSERROR_EROFS:
        return "read-only file system";
    case DARK_OSERROR_EMLINK:
        return "too many links";
    case DARK_OSERROR_EPIPE:
        return "broken pipe";
    case DARK_OSERROR_EDOM:
        return "math argument out of domain of func";
    case DARK_OSERROR_ERANGE:
        return "math result not representable";
    case DARK_OSERROR_EDEADLK:
        return "resource deadlock would occur";
    case DARK_OSERROR_ENAMETOOLONG:
        return "file name too long";
    case DARK_OSERROR_ENOLCK:
        return "no record locks available";
    case DARK_OSERROR_ENOSYS:
        return "function not implemented";
    case DARK_OSERROR_ENOTEMPTY:
        return "directory not empty";
    case DARK_OSERROR_ELOOP:
        return "too many symbolic links encountered";
    case DARK_OSERROR_ENOMSG:
        return "no message of desired type";
    case DARK_OSERROR_EIDRM:
        return "identifier removed";
    case DARK_OSERROR_ECHRNG:
        return "channel number out of range";
    case DARK_OSERROR_EL2NSYNC:
        return "level 2 not synchronized";
    case DARK_OSERROR_EL3HLT:
        return "level 3 halted";
    case DARK_OSERROR_EL3RST:
        return "level 3 reset";
    case DARK_OSERROR_ELNRNG:
        return "link number out of range";
    case DARK_OSERROR_EUNATCH:
        return "protocol driver not attached";
    case DARK_OSERROR_ENOCSI:
        return "no CSI structure available";
    case DARK_OSERROR_EL2HLT:
        return "level 2 halted";
    case DARK_OSERROR_EBADE:
        return "invalid exchange";
    case DARK_OSERROR_EBADR:
        return "invalid request descriptor";
    case DARK_OSERROR_EXFULL:
        return "exchange full";
    case DARK_OSERROR_ENOANO:
        return "no anode";
    case DARK_OSERROR_EBADRQC:
        return "invalid request code";
    case DARK_OSERROR_EBADSLT:
        return "invalid slot";
    case DARK_OSERROR_EBFONT:
        return "bad font file format";
    case DARK_OSERROR_ENOSTR:
        return "device not a stream";
    case DARK_OSERROR_ENODATA:
        return "no data available";
    case DARK_OSERROR_ETIME:
        return "timer expired";
    case DARK_OSERROR_ENOSR:
        return "out of streams resources";
    case DARK_OSERROR_ENONET:
        return "machine is not on the network";
    case DARK_OSERROR_ENOPKG:
        return "package not installed";
    case DARK_OSERROR_EREMOTE:
        return "object is remote";
    case DARK_OSERROR_ENOLINK:
        return "link has been severed";
    case DARK_OSERROR_EADV:
        return "advertise error";
    case DARK_OSERROR_ESRMNT:
        return "srmount error";
    case DARK_OSERROR_ECOMM:
        return "communication error on send";
    case DARK_OSERROR_EPROTO:
        return "protocol error";
    case DARK_OSERROR_EMULTIHOP:
        return "multihop attempted";
    case DARK_OSERROR_EDOTDOT:
        return "RFS specific error";
    case DARK_OSERROR_EBADMSG:
        return "not a data message";
    case DARK_OSERROR_EOVERFLOW:
        return "value too large for defined data type";
    case DARK_OSERROR_ENOTUNIQ:
        return "name not unique on network";
    case DARK_OSERROR_EBADFD:
        return "file descriptor in bad state";
    case DARK_OSERROR_EREMCHG:
        return "remote address changed";
    case DARK_OSERROR_ELIBACC:
        return "can not access a needed shared library";
    case DARK_OSERROR_ELIBBAD:
        return "accessing a corrupted shared library";
    case DARK_OSERROR_ELIBSCN:
        return ".lib section in a.out corrupted";
    case DARK_OSERROR_ELIBMAX:
        return "attempting to link in too many shared libraries";
    case DARK_OSERROR_ELIBEXEC:
        return "cannot exec a shared library directly";
    case DARK_OSERROR_EILSEQ:
        return "illegal byte sequence";
    case DARK_OSERROR_ERESTART:
        return "interrupted system call should be restarted";
    case DARK_OSERROR_ESTRPIPE:
        return "streams pipe error";
    case DARK_OSERROR_EUSERS:
        return "too many users";
    case DARK_OSERROR_ENOTSOCK:
        return "socket operation on non-socket";
    case DARK_OSERROR_EDESTADDRREQ:
        return "destination address required";
    case DARK_OSERROR_EMSGSIZE:
        return "message too long";
    case DARK_OSERROR_EPROTOTYPE:
        return "protocol wrong type for socket";
    case DARK_OSERROR_ENOPROTOOPT:
        return "protocol not available";
    case DARK_OSERROR_EPROTONOSUPPORT:
        return "protocol not supported";
    case DARK_OSERROR_ESOCKTNOSUPPORT:
        return "socket type not supported";
    case DARK_OSERROR_EOPNOTSUPP:
        return "operation not supported on transport endpoint";
    case DARK_OSERROR_EPFNOSUPPORT:
        return "protocol family not supported";
    case DARK_OSERROR_EAFNOSUPPORT:
        return "address family not supported by protocol";
    case DARK_OSERROR_EADDRINUSE:
        return "address already in use";
    case DARK_OSERROR_EADDRNOTAVAIL:
        return "cannot assign requested address";
    case DARK_OSERROR_ENETDOWN:
        return "network is down";
    case DARK_OSERROR_ENETUNREACH:
        return "network is unreachable";
    case DARK_OSERROR_ENETRESET:
        return "network dropped connection because of reset";
    case DARK_OSERROR_ECONNABORTED:
        return "software caused connection abort";
    case DARK_OSERROR_ECONNRESET:
        return "connection reset by peer";
    case DARK_OSERROR_ENOBUFS:
        return "no buffer space available";
    case DARK_OSERROR_EISCONN:
        return "transport endpoint is already connected";
    case DARK_OSERROR_ENOTCONN:
        return "transport endpoint is not connected";
    case DARK_OSERROR_ESHUTDOWN:
        return "cannot send after transport endpoint shutdown";
    case DARK_OSERROR_ETOOMANYREFS:
        return "too many references: cannot splice";
    case DARK_OSERROR_ETIMEDOUT:
        return "connection timed out";
    case DARK_OSERROR_ECONNREFUSED:
        return "connection refused";
    case DARK_OSERROR_EHOSTDOWN:
        return "host is down";
    case DARK_OSERROR_EHOSTUNREACH:
        return "no route to host";
    case DARK_OSERROR_EALREADY:
        return "operation already in progress";
    case DARK_OSERROR_EINPROGRESS:
        return "operation now in progress";
    case DARK_OSERROR_ESTALE:
        return "stale NFS file handle";
    case DARK_OSERROR_EUCLEAN:
        return "structure needs cleaning";
    case DARK_OSERROR_ENOTNAM:
        return "not a XENIX named type file";
    case DARK_OSERROR_ENAVAIL:
        return "no XENIX semaphores available";
    case DARK_OSERROR_EISNAM:
        return "is a named type file";
    case DARK_OSERROR_EREMOTEIO:
        return "remote I/O error";
    case DARK_OSERROR_EDQUOT:
        return "quota exceeded";
    case DARK_OSERROR_ENOMEDIUM:
        return "no medium found";
    case DARK_OSERROR_EMEDIUMTYPE:
        return "wrong medium type";
    case DARK_OSERROR_ECANCELED:
        return "operation canceled";
    case DARK_OSERROR_ENOKEY:
        return "required key not available";
    case DARK_OSERROR_EKEYEXPIRED:
        return "key has expired";
    case DARK_OSERROR_EKEYREVOKED:
        return "key has been revoked";
    case DARK_OSERROR_EKEYREJECTED:
        return "key was rejected by service";
    case DARK_OSERROR_EOWNERDEAD:
        return "owner died";
    case DARK_OSERROR_ENOTRECOVERABLE:
        return "state not recoverable";
    case DARK_OSERROR_STRUNCATE:
        return "string copy or concatenation resulted in a truncated string (win32 only)";
    case DARK_OSERROR_ENOTSUP:
        return "not supported (win32 only)";
    case DARK_OSERROR_EOTHER:
        return "other (win32 only)";
    case DARK_OSERROR_EWOULDBLOCK:
        return "operation would block (win32 only)";
    case DARK_OSERROR_UNKNOWN:
        return "unknown error";
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }
}
