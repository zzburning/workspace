/*
 * xeR.h
 *
 *  Created on: 2011-5-14
 *      Author: enigma
 *
 * Description:
 * 	This is common function return value and error code definitions;
 * All values based errno and extend it;
 * 	Use these values both in user space applications and kernel drivers,
 * except driver should return minus value;
 */

#ifndef __HISOME_XEHSC_R_H__
#define __HISOME_XEHSC_R_H__


#ifdef __cplusplus
extern "C" {
#endif

//#ifdef __linux__
#include <errno.h>
//#endif/*__linux__*/
	
enum xeR_ENUM
{
	XER_ERROR 			= (-1),
	XER_ERR				= XER_ERROR,
	XER_FAIL			= XER_ERROR,

	XER_SUCCESS 		= (0),
	XER_OK				= XER_SUCCESS,

/*###########################################################################*/
/*BEGIN errno mapping*/
	XER_EPERM 			= EPERM,/* Operation not permitted */
	XER_ENOENT 			= ENOENT,/* No such file or directory */
	XER_ESRCH 			= ESRCH,/* No such process */
	XER_EINTR 			= EINTR,/* Interrupted system call */
	XER_EIO 			= EIO,/* I/O error */
	XER_ENXIO 			= ENXIO,/* No such device or address */
	XER_E2BIG 			= E2BIG,/* Argument list too long */
	XER_ENOEXEC 		= ENOEXEC,/* Exec format error */
	XER_EBADF 			= EBADF,/* Bad file number */
	XER_ECHILD 			= ECHILD,/* No child processes */
	XER_EAGAIN 			= EAGAIN,/* Try again */
	XER_ENOMEM 			= ENOMEM,/* Out of memory */
	XER_EACCES 			= EACCES,/* Permission denied */
	XER_EFAULT 			= EFAULT,/* Bad address */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	XER_ENOTBLK 		= ENOTBLK,/* Block device required */
#endif
	XER_EBUSY 			= EBUSY,/* Device or resource busy */
	XER_EEXIST 			= EEXIST,/* File exists */
	XER_EXDEV 			= EXDEV,/* Cross-device link */
	XER_ENODEV 			= ENODEV,/* No such device */
	XER_ENOTDIR 		= ENOTDIR,/* Not a directory */
	XER_EISDIR 			= EISDIR,/* Is a directory */
	XER_EINVAL 			= EINVAL,/* Invalid argument */
	XER_ENFILE 			= ENFILE,/* File table overflow */
	XER_EMFILE 			= EMFILE,/* Too many open files */
	XER_ENOTTY 			= ENOTTY,/* Not a typewriter */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	XER_ETXTBSY 		= ETXTBSY,/* Text file busy */
#endif
	XER_EFBIG 			= EFBIG,/* File too large */
	XER_ENOSPC 			= ENOSPC,/* No space left on device */
	XER_ESPIPE 			= ESPIPE,/* Illegal seek */
	XER_EROFS 			= EROFS,/* Read-only file system */
	XER_EMLINK 			= EMLINK,/* Too many links */
	XER_EPIPE 			= EPIPE,/* Broken pipe */
	XER_EDOM 			= EDOM,/* Math argument out of domain of func */
	XER_ERANGE 			= ERANGE,/* Math result not representable */

	XER_EDEADLK 		= EDEADLK,/* Resource deadlock would occur */
	XER_ENAMETOOLONG 	= ENAMETOOLONG,/* File name too long */
	XER_ENOLCK 			= ENOLCK,/* No record locks available */
	XER_ENOSYS 			= ENOSYS,/* Function not implemented */
	XER_ENOTEMPTY 		= ENOTEMPTY,/* Directory not empty */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	XER_ELOOP 			= ELOOP,/* Too many symbolic links encountered */
#endif
	XER_EWOULDBLOCK 	= EAGAIN,	/* Operation would block */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	XER_ENOMSG 			= ENOMSG,/* No message of desired type */
	XER_EIDRM 			= EIDRM,/* Identifier removed */
	XER_ECHRNG 			= ECHRNG,/* Channel number out of range */
	XER_EL2NSYNC 		= EL2NSYNC,/* Level 2 not synchronized */
	XER_EL3HLT 			= EL3HLT,/* Level 3 halted */
	XER_EL3RST 			= EL3RST,/* Level 3 reset */
	XER_ELNRNG 			= ELNRNG,/* Link number out of range */
	XER_EUNATCH 		= EUNATCH,/* Protocol driver not attached */
	XER_ENOCSI 			= ENOCSI,/* No CSI structure available */
	XER_EL2HLT 			= EL2HLT,/* Level 2 halted */
	XER_EBADE 			= EBADE,/* Invalid exchange */
	XER_EBADR 			= EBADR,/* Invalid request descriptor */
	XER_EXFULL 			= EXFULL,/* Exchange full */
	XER_ENOANO 			= ENOANO,/* No anode */
	XER_EBADRQC 		= EBADRQC,/* Invalid request code */
	XER_EBADSLT 		= EBADSLT,/* Invalid slot */
#endif
	XER_EDEADLOCK 		= EDEADLK,
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	XER_EBFONT 			= EBFONT,/* Bad font file format */
	XER_ENOSTR 			= ENOSTR,/* Device not a stream */
	XER_ENODATA 		= ENODATA,/* No data available */
	XER_ETIME 			= ETIME,/* Timer expired */
	XER_ENOSR 			= ENOSR,/* Out of streams resources */
	XER_ENONET 			= ENONET,/* Machine is not on the network */
	XER_ENOPKG 			= ENOPKG,/* Package not installed */
	XER_EREMOTE 		= EREMOTE,/* Object is remote */
	XER_ENOLINK 		= ENOLINK,/* Link has been severed */
	XER_EADV 			= EADV,/* Advertise error */
	XER_ESRMNT 			= ESRMNT,/* Srmount error */
	XER_ECOMM 			= ECOMM,/* Communication error on send */
	XER_EPROTO 			= EPROTO,/* Protocol error */
	XER_EMULTIHOP 		= EMULTIHOP,/* Multihop attempted */
	XER_EDOTDOT 		= EDOTDOT,/* RFS specific error */
	XER_EBADMSG 		= EBADMSG,/* Not a data message */
	XER_EOVERFLOW 		= EOVERFLOW,/* Value too large for defined data type */
	XER_ENOTUNIQ 		= ENOTUNIQ,/* Name not unique on network */
	XER_EBADFD 			= EBADFD,/* File descriptor in bad state */
	XER_EREMCHG 		= EREMCHG,/* Remote address changed */
	XER_ELIBACC 		= ELIBACC,/* Can not access a needed shared library */
	XER_ELIBBAD 		= ELIBBAD,/* Accessing a corrupted shared library */
	XER_ELIBSCN 		= ELIBSCN,/* .lib section in a.out corrupted */
	XER_ELIBMAX 		= ELIBMAX,/* Attempting to link in too many shared libraries */
	XER_ELIBEXEC 		= ELIBEXEC,/* Cannot exec a shared library directly */
#endif
	XER_EILSEQ 			= EILSEQ,/* Illegal byte sequence */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	XER_ERESTART 		= ERESTART,/* Interrupted system call should be restarted */
	XER_ESTRPIPE 		= ESTRPIPE,/* Streams pipe error */
	XER_EUSERS 			= EUSERS,/* Too many users */
	XER_ENOTSOCK 		= ENOTSOCK,/* Socket operation on non-socket */
	XER_EDESTADDRREQ 	= EDESTADDRREQ,/* Destination address required */
	XER_EMSGSIZE 		= EMSGSIZE,/* Message too long */
	XER_EPROTOTYPE 		= EPROTOTYPE,/* Protocol wrong type for socket */
	XER_ENOPROTOOPT 	= ENOPROTOOPT,/* Protocol not available */
	XER_EPROTONOSUPPORT = EPROTONOSUPPORT,/* Protocol not supported */
	XER_ESOCKTNOSUPPORT = ESOCKTNOSUPPORT,/* Socket type not supported */
	XER_EOPNOTSUPP 		= EOPNOTSUPP,/* Operation not supported on transport endpoint */
	XER_EPFNOSUPPORT 	= EPFNOSUPPORT,/* Protocol family not supported */
	XER_EAFNOSUPPORT 	= EAFNOSUPPORT,/* Address family not supported by protocol */
	XER_EADDRINUSE 		= EADDRINUSE,/* Address already in use */
	XER_EADDRNOTAVAIL 	= EADDRNOTAVAIL,/* Cannot assign requested address */
	XER_ENETDOWN 		= ENETDOWN,/* Network is down */
	XER_ENETUNREACH 	= ENETUNREACH,/* Network is unreachable */
	XER_ENETRESET 		= ENETRESET,/* Network dropped connection because of reset */
	XER_ECONNABORTED 	= ECONNABORTED,/* Software caused connection abort */
	XER_ECONNRESET 		= ECONNRESET,/* Connection reset by peer */
	XER_ENOBUFS 		= ENOBUFS,/* No buffer space available */
	XER_EISCONN 		= EISCONN,/* Transport endpoint is already connected */
	XER_ENOTCONN 		= ENOTCONN,/* Transport endpoint is not connected */
	XER_ESHUTDOWN 		= ESHUTDOWN,/* Cannot send after transport endpoint shutdown */
	XER_ETOOMANYREFS 	= ETOOMANYREFS,/* Too many references: cannot splice */
	XER_ETIMEDOUT 		= ETIMEDOUT,/* Connection timed out */
	XER_ECONNREFUSED 	= ECONNREFUSED,/* Connection refused */
	XER_EHOSTDOWN 		= EHOSTDOWN,/* Host is down */
	XER_EHOSTUNREACH 	= EHOSTUNREACH,/* No route to host */
	XER_EALREADY 		= EALREADY,/* Operation already in progress */
	XER_EINPROGRESS 	= EINPROGRESS,/* Operation now in progress */
	XER_ESTALE 			= ESTALE,/* Stale NFS file handle */
	XER_EUCLEAN 		= EUCLEAN,/* Structure needs cleaning */
	XER_ENOTNAM 		= ENOTNAM,/* Not a XENIX named type file */
	XER_ENAVAIL 		= ENAVAIL,/* No XENIX semaphores available */
	XER_EISNAM 			= EISNAM,/* Is a named type file */
	XER_EREMOTEIO 		= EREMOTEIO,/* Remote I/O error */
	XER_EDQUOT 			= EDQUOT,/* Quota exceeded */
	XER_ENOMEDIUM 		= ENOMEDIUM,/* No medium found */
	XER_EMEDIUMTYPE 	= EMEDIUMTYPE,/* Wrong medium type */
	XER_ECANCELED 		= ECANCELED,/* Operation Canceled */
	XER_ENOKEY 			= ENOKEY,/* Required key not available */
	XER_EKEYEXPIRED 	= EKEYEXPIRED,/* Key has expired */
	XER_EKEYREVOKED 	= EKEYREVOKED,/* Key has been revoked */
	XER_EKEYREJECTED 	= EKEYREJECTED,/* Key was rejected by service */

	XER_EOWNERDEAD 		= EOWNERDEAD,/* Owner died */
	XER_ENOTRECOVERABLE = ENOTRECOVERABLE,/* State not recoverable */
#endif
	//XER_ERFKILL 		= ERFKILL,/* Operation not possible due to RF-kill */
/*END errno mapping*/
/*###########################################################################*/

	/*BEGIN of XER_xxx defines from 200~300*/
	XER_BASE=200,
	XER_NOT_SUPPORT,/*not support operation or function*/
	XER_EEOF,/*End-Of-File*/
	XER_EEOS = XER_EEOF,/*End-Of-Stream*/
#if defined(CONFIG_XEHSC_DEVPLAT_VC6)
	XER_ENODATA,
#endif
	/*TODO: extend more values begin here*/

	XER_MAX=299,
	/*END of XER_xxx defines from 200~300*/

	/*USER extended other XER_xxx values from 300*/


	/*Caution: Special Value for Yes/No*/
	XER_YES=1,
	XER_NO=0,
};

typedef enum xeR_ENUM xeR_t;
typedef enum xeR_ENUM xeR_errno_t;
typedef enum xeR_ENUM xeR_fail_reason_t;

#ifdef __cplusplus
};
#endif

#endif /* __HISOME_XEHSC_R_H__ */
