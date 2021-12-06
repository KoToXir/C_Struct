#include <stdint.h>
#ifndef TYPE_H_
#define TYPE_H_

/*--------------------------------------------------------------------
 * #define
 *--------------------------------------------------------------------*/
//データタイプ
//! boolタイプ
#define     BOOL       int
//! byteタイプ(1バイト)
#ifndef BYTE
#define     BYTE       unsigned char
#endif
//! charタイプ(1バイト)
#define		CHAR	   char	
//! unsigned charタイプ(1バイト)
#ifndef UCHAR
#define     UCHAR      unsigned char
#endif
//! shortタイプ(2バイト)
#define		SHORT	   int16_t
//! wordタイプ(2バイト)
#define		WORD	   uint16_t
//! intタイプ(4バイト)
#define     INT        int32_t
//! unsigned intタイプ(4バイト)
#define     UINT       uint32_t
//! dwordタイプ(4バイト)
#define		DWORD	   uint32_t
//! floatタイプ(4バイト)
#define		FLOAT	   float
//! longタイプ(8バイト)
#define		LONG	   int64_t
//! ulongタイプ(8バイト)
#define		ULONG	   uint64_t
//! doubleタイプ(8バイト)
#define		DOUBLE	   double
//! voidタイプ
#define		VOID	   void
//! true
#define     TRUE       1
//! false
#define     FALSE      0
//! null
#ifndef		NULL
	#define		NULL	   ((void*)0)
#endif


#endif /* TYPE_H_ */
