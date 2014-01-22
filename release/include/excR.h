/*
 * excR.h
 *
 *  Created on: 2011-5-14
 *      Author:
 *
 * Description:
 * 	This is common function return value and error code definitions;
 * All values based errno and extend it;
 * 	Use these values both in user space applications and kernel drivers,
 * except driver should return minus value;
 */

#ifndef __EXC_R_H__
#define __EXC_R_H__


#ifdef __cplusplus
extern "C" {
#endif

//#ifdef __linux__
#include <errno.h>
//#endif/*__linux__*/
	
enum excR_ENUM
{
	EXCR_ERROR 			= (-1),
	EXCR_ERR			= EXCR_ERROR,
	EXCR_FAIL			= EXCR_ERROR,

	EXCR_SUCCESS 		= (0),
	EXCR_OK				= EXCR_SUCCESS,

/*###########################################################################*/
/*BEGIN errno mapping*/
	EXCR_EPERM 			= EPERM,/* Operation not permitted */
	EXCR_ENOENT 		= ENOENT,/* No such file or directory */
	EXCR_ESRCH 			= ESRCH,/* No such process */
	EXCR_EINTR 			= EINTR,/* Interrupted system call */
	EXCR_EIO 			= EIO,/* I/O error */
	EXCR_ENXIO 			= ENXIO,/* No such device or address */
	EXCR_E2BIG 			= E2BIG,/* Argument list too long */
	EXCR_ENOEXEC 		= ENOEXEC,/* Exec format error */
	EXCR_EBADF 			= EBADF,/* Bad file number */
	EXCR_ECHILD 			= ECHILD,/* No child processes */
	EXCR_EAGAIN 			= EAGAIN,/* Try again */
	EXCR_ENOMEM 			= ENOMEM,/* Out of memory */
	EXCR_EACCES 			= EACCES,/* Permission denied */
	EXCR_EFAULT 			= EFAULT,/* Bad address */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	EXCR_ENOTBLK 		= ENOTBLK,/* Block device required */
#endif
	EXCR_EBUSY 			= EBUSY,/* Device or resource busy */
	EXCR_EEXIST 		= EEXIST,/* File exists */
	EXCR_EXDEV 			= EXDEV,/* Cross-device link */
	EXCR_ENODEV 		= ENODEV,/* No such device */
	EXCR_ENOTDIR 		= ENOTDIR,/* Not a directory */
	EXCR_EISDIR 			= EISDIR,/* Is a directory */
	EXCR_EINVAL 			= EINVAL,/* Invalid argument */
	EXCR_ENFILE 			= ENFILE,/* File table overflow */
	EXCR_EMFILE 			= EMFILE,/* Too many open files */
	EXCR_ENOTTY 			= ENOTTY,/* Not a typewriter */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	EXCR_ETXTBSY 		= ETXTBSY,/* Text file busy */
#endif
	EXCR_EFBIG 			= EFBIG,/* File too large */
	EXCR_ENOSPC 		= ENOSPC,/* No space left on device */
	EXCR_ESPIPE 		= ESPIPE,/* Illegal seek */
	EXCR_EROFS 			= EROFS,/* Read-only file system */
	EXCR_EMLINK 		= EMLINK,/* Too many links */
	EXCR_EPIPE 			= EPIPE,/* Broken pipe */
	EXCR_EDOM 			= EDOM,/* Math argument out of domain of func */
	EXCR_ERANGE 		= ERANGE,/* Math result not representable */

	EXCR_EDEADLK 		= EDEADLK,/* Resource deadlock would occur */
	EXCR_ENAMETOOLONG 	= ENAMETOOLONG,/* File name too long */
	EXCR_ENOLCK 		= ENOLCK,/* No record locks available */
	EXCR_ENOSYS 		= ENOSYS,/* Function not implemented */
	EXCR_ENOTEMPTY 		= ENOTEMPTY,/* Directory not empty */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	EXCR_ELOOP 			= ELOOP,/* Too many symbolic links encountered */
#endif
	EXCR_EWOULDBLOCK 	= EAGAIN,	/* Operation would block */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	EXCR_ENOMSG 		= ENOMSG,/* No message of desired type */
	EXCR_EIDRM 			= EIDRM,/* Identifier removed */
	EXCR_ECHRNG 		= ECHRNG,/* Channel number out of range */
	EXCR_EL2NSYNC 		= EL2NSYNC,/* Level 2 not synchronized */
	EXCR_EL3HLT 		= EL3HLT,/* Level 3 halted */
	EXCR_EL3RST 		= EL3RST,/* Level 3 reset */
	EXCR_ELNRNG 		= ELNRNG,/* Link number out of range */
	EXCR_EUNATCH 		= EUNATCH,/* Protocol driver not attached */
	EXCR_ENOCSI 		= ENOCSI,/* No CSI structure available */
	EXCR_EL2HLT 		= EL2HLT,/* Level 2 halted */
	EXCR_EBADE 			= EBADE,/* Invalid exchange */
	EXCR_EBADR 			= EBADR,/* Invalid request descriptor */
	EXCR_EXFULL 		= EXFULL,/* Exchange full */
	EXCR_ENOANO 		= ENOANO,/* No anode */
	EXCR_EBADRQC 		= EBADRQC,/* Invalid request code */
	EXCR_EBADSLT 		= EBADSLT,/* Invalid slot */
#endif
	EXCR_EDEADLOCK 		= EDEADLK,
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	EXCR_EBFONT 		= EBFONT,/* Bad font file format */
	EXCR_ENOSTR 		= ENOSTR,/* Device not a stream */
	EXCR_ENODATA 		= ENODATA,/* No data available */
	EXCR_ETIME 			= ETIME,/* Timer expired */
	EXCR_ENOSR 			= ENOSR,/* Out of streams resources */
	EXCR_ENONET 		= ENONET,/* Machine is not on the network */
	EXCR_ENOPKG 		= ENOPKG,/* Package not installed */
	EXCR_EREMOTE 		= EREMOTE,/* Object is remote */
	EXCR_ENOLINK 		= ENOLINK,/* Link has been severed */
	EXCR_EADV 			= EADV,/* Advertise error */
	EXCR_ESRMNT 		= ESRMNT,/* Srmount error */
	EXCR_ECOMM 			= ECOMM,/* Communication error on send */
	EXCR_EPROTO 		= EPROTO,/* Protocol error */
	EXCR_EMULTIHOP 		= EMULTIHOP,/* Multihop attempted */
	EXCR_EDOTDOT 		= EDOTDOT,/* RFS specific error */
	EXCR_EBADMSG 		= EBADMSG,/* Not a data message */
	EXCR_EOVERFLOW 		= EOVERFLOW,/* Value too large for defined data type */
	EXCR_ENOTUNIQ 		= ENOTUNIQ,/* Name not unique on network */
	EXCR_EBADFD 		= EBADFD,/* File descriptor in bad state */
	EXCR_EREMCHG 		= EREMCHG,/* Remote address changed */
	EXCR_ELIBACC 		= ELIBACC,/* Can not access a needed shared library */
	EXCR_ELIBBAD 		= ELIBBAD,/* Accessing a corrupted shared library */
	EXCR_ELIBSCN 		= ELIBSCN,/* .lib section in a.out corrupted */
	EXCR_ELIBMAX 		= ELIBMAX,/* Attempting to link in too many shared libraries */
	EXCR_ELIBEXEC 		= ELIBEXEC,/* Cannot exec a shared library directly */
#endif
	EXCR_EILSEQ 		= EILSEQ,/* Illegal byte sequence */
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	EXCR_ERESTART 		= ERESTART,/* Interrupted system call should be restarted */
	EXCR_ESTRPIPE 		= ESTRPIPE,/* Streams pipe error */
	EXCR_EUSERS 		= EUSERS,/* Too many users */
	EXCR_ENOTSOCK 		= ENOTSOCK,/* Socket operation on non-socket */
	EXCR_EDESTADDRREQ 	= EDESTADDRREQ,/* Destination address required */
	EXCR_EMSGSIZE 		= EMSGSIZE,/* Message too long */
	EXCR_EPROTOTYPE 	= EPROTOTYPE,/* Protocol wrong type for socket */
	EXCR_ENOPROTOOPT 	= ENOPROTOOPT,/* Protocol not available */
	EXCR_EPROTONOSUPPORT = EPROTONOSUPPORT,/* Protocol not supported */
	EXCR_ESOCKTNOSUPPORT = ESOCKTNOSUPPORT,/* Socket type not supported */
	EXCR_EOPNOTSUPP 	= EOPNOTSUPP,/* Operation not supported on transport endpoint */
	EXCR_EPFNOSUPPORT 	= EPFNOSUPPORT,/* Protocol family not supported */
	EXCR_EAFNOSUPPORT 	= EAFNOSUPPORT,/* Address family not supported by protocol */
	EXCR_EADDRINUSE 	= EADDRINUSE,/* Address already in use */
	EXCR_EADDRNOTAVAIL 	= EADDRNOTAVAIL,/* Cannot assign requested address */
	EXCR_ENETDOWN 		= ENETDOWN,/* Network is down */
	EXCR_ENETUNREACH 	= ENETUNREACH,/* Network is unreachable */
	EXCR_ENETRESET 		= ENETRESET,/* Network dropped connection because of reset */
	EXCR_ECONNABORTED 	= ECONNABORTED,/* Software caused connection abort */
	EXCR_ECONNRESET 	= ECONNRESET,/* Connection reset by peer */
	EXCR_ENOBUFS 		= ENOBUFS,/* No buffer space available */
	EXCR_EISCONN 		= EISCONN,/* Transport endpoint is already connected */
	EXCR_ENOTCONN 		= ENOTCONN,/* Transport endpoint is not connected */
	EXCR_ESHUTDOWN 		= ESHUTDOWN,/* Cannot send after transport endpoint shutdown */
	EXCR_ETOOMANYREFS 	= ETOOMANYREFS,/* Too many references: cannot splice */
	EXCR_ETIMEDOUT 		= ETIMEDOUT,/* Connection timed out */
	EXCR_ECONNREFUSED 	= ECONNREFUSED,/* Connection refused */
	EXCR_EHOSTDOWN 		= EHOSTDOWN,/* Host is down */
	EXCR_EHOSTUNREACH 	= EHOSTUNREACH,/* No route to host */
	EXCR_EALREADY 		= EALREADY,/* Operation already in progress */
	EXCR_EINPROGRESS 	= EINPROGRESS,/* Operation now in progress */
	EXCR_ESTALE 		= ESTALE,/* Stale NFS file handle */
	EXCR_EUCLEAN 		= EUCLEAN,/* Structure needs cleaning */
	EXCR_ENOTNAM 		= ENOTNAM,/* Not a XENIX named type file */
	EXCR_ENAVAIL 		= ENAVAIL,/* No XENIX semaphores available */
	EXCR_EISNAM 		= EISNAM,/* Is a named type file */
	EXCR_EREMOTEIO 		= EREMOTEIO,/* Remote I/O error */
	EXCR_EDQUOT 		= EDQUOT,/* Quota exceeded */
	EXCR_ENOMEDIUM 		= ENOMEDIUM,/* No medium found */
	EXCR_EMEDIUMTYPE 	= EMEDIUMTYPE,/* Wrong medium type */
	EXCR_ECANCELED 		= ECANCELED,/* Operation Canceled */
	EXCR_ENOKEY 		= ENOKEY,/* Required key not available */
	EXCR_EKEYEXPIRED 	= EKEYEXPIRED,/* Key has expired */
	EXCR_EKEYREVOKED 	= EKEYREVOKED,/* Key has been revoked */
	EXCR_EKEYREJECTED 	= EKEYREJECTED,/* Key was rejected by service */

	EXCR_EOWNERDEAD 	= EOWNERDEAD,/* Owner died */
	EXCR_ENOTRECOVERABLE = ENOTRECOVERABLE,/* State not recoverable */
#endif
	//EXCR_ERFKILL 		= ERFKILL,/* Operation not possible due to RF-kill */
/*END errno mapping*/
/*###########################################################################*/

	/*BEGIN of EXCR_xxx defines from 200~300*/
	EXCR_BASE=200,
	EXCR_NOT_SUPPORT,/*not support operation or function*/
	EXCR_EEOF,/*End-Of-File*/
	EXCR_EEOS = EXCR_EEOF,/*End-Of-Stream*/
#if defined(CONFIG_XEHSC_DEVPLAT_VC6)
	EXCR_ENODATA,
#endif
	/*TODO: extend more values begin here*/

	EXCR_MAX=299,
	/*END of EXCR_xxx defines from 200~300*/

	/*USER extended other EXCR_xxx values from 300*/


	/*Caution: Special Value for Yes/No*/
	EXCR_YES=1,
	EXCR_NO=0,
};

typedef enum excR_ENUM excR_t;
typedef enum excR_ENUM excR_errno_t;
typedef enum excR_ENUM excR_fail_reason_t;

#ifdef __cplusplus
};
#endif

#endif /* __EXC_R_H__ */
