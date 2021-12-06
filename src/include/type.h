#include <stdint.h>
#ifndef TYPE_H_
#define TYPE_H_

#define     BOOL       int
//! byte(1byte)
#ifndef BYTE
#define     BYTE       unsigned char
#endif
//! char(1byte)
#define		CHAR	   char	
//! unsigned char(1byte)
#ifndef UCHAR
#define     UCHAR      unsigned char
#endif
//! short(2byte)
#define		SHORT	   int16_t
//! word(2byte)
#define		WORD	   uint16_t
//! int(4byte)
#define     INT        int32_t
//! unsigned int(4byte)
#define     UINT       uint32_t
//! dword(4byte)
#define		DWORD	   uint32_t
//! float(4byte)
#define		FLOAT	   float
//! long(8byte)
#define		LONG	   int64_t
//! ulong(8byte)
#define		ULONG	   uint64_t
//! double(8byte)
#define		DOUBLE	   double
//! void
#define		VOID	   void
//! true
#define     TRUE       1
//! false
#define     FALSE      0
//! null
#ifndef		NULL
	#define		NULL	   ((void*)0)
#endif

#endif
