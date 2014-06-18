/*
 *  Portable interface to the CPU cycle counter
 *
 *  Copyright (C) 2006-2014, Brainspark B.V.
 *
 *  This file is part of PolarSSL (http://www.polarssl.org)
 *  Lead Maintainer: Paul Bakker <polarssl_maintainer at polarssl.org>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "timing.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(POLARSSL_HAVE_ASM) &&  \
    (defined(_MSC_VER) && defined(_M_IX86)) || defined(__WATCOMC__)

#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    unsigned long tsc;
    __asm   rdtsc
    __asm   mov  [tsc], eax
    return( tsc );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK && POLARSSL_HAVE_ASM &&
          ( _MSC_VER && _M_IX86 ) || __WATCOMC__ */

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(POLARSSL_HAVE_ASM) &&  \
    defined(__GNUC__) && defined(__i386__)

#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    unsigned long lo, hi;
    asm volatile( "rdtsc" : "=a" (lo), "=d" (hi) );
    return( lo );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK && POLARSSL_HAVE_ASM &&
          __GNUC__ && __i386__ */

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(POLARSSL_HAVE_ASM) &&  \
    defined(__GNUC__) && (defined(__amd64__) || defined(__x86_64__))

#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    unsigned long lo, hi;
    asm volatile( "rdtsc" : "=a" (lo), "=d" (hi) );
    return( lo | (hi << 32) );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK && POLARSSL_HAVE_ASM &&
          __GNUC__ && ( __amd64__ || __x86_64__ ) */

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(POLARSSL_HAVE_ASM) &&  \
    defined(__GNUC__) && (defined(__powerpc__) || defined(__ppc__))

#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    unsigned long tbl, tbu0, tbu1;

    do
    {
        asm volatile( "mftbu %0" : "=r" (tbu0) );
        asm volatile( "mftb  %0" : "=r" (tbl ) );
        asm volatile( "mftbu %0" : "=r" (tbu1) );
    }
    while( tbu0 != tbu1 );

    return( tbl );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK && POLARSSL_HAVE_ASM &&
          __GNUC__ && ( __powerpc__ || __ppc__ ) */

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(POLARSSL_HAVE_ASM) &&  \
    defined(__GNUC__) && defined(__sparc64__)

#if defined(__OpenBSD__)
#warning OpenBSD does not allow access to tick register using software version instead
#else
#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    unsigned long tick;
    asm volatile( "rdpr %%tick, %0;" : "=&r" (tick) );
    return( tick );
}
#endif /* __OpenBSD__ */
#endif /* !POLARSSL_HAVE_HARDCLOCK && POLARSSL_HAVE_ASM &&
          __GNUC__ && __sparc64__ */

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(POLARSSL_HAVE_ASM) &&  \
    defined(__GNUC__) && defined(__sparc__) && !defined(__sparc64__)

#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    unsigned long tick;
    asm volatile( ".byte 0x83, 0x41, 0x00, 0x00" );
    asm volatile( "mov   %%g1, %0" : "=r" (tick) );
    return( tick );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK && POLARSSL_HAVE_ASM &&
          __GNUC__ && __sparc__ && !__sparc64__ */

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(POLARSSL_HAVE_ASM) &&      \
    defined(__GNUC__) && defined(__alpha__)

#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    unsigned long cc;
    asm volatile( "rpcc %0" : "=r" (cc) );
    return( cc & 0xFFFFFFFF );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK && POLARSSL_HAVE_ASM &&
          __GNUC__ && __alpha__ */

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(POLARSSL_HAVE_ASM) &&      \
    defined(__GNUC__) && defined(__ia64__)

#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    unsigned long itc;
    asm volatile( "mov %0 = ar.itc" : "=r" (itc) );
    return( itc );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK && POLARSSL_HAVE_ASM &&
          __GNUC__ && __ia64__ */

#if !defined(POLARSSL_HAVE_HARDCLOCK) && defined(_MSC_VER) && \
    !defined(EFIX64) && !defined(EFI32)

#define POLARSSL_HAVE_HARDCLOCK

unsigned long hardclock( void )
{
    LARGE_INTEGER offset;

    QueryPerformanceCounter( &offset );

    return (unsigned long)( offset.QuadPart );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK && _MSC_VER && !EFIX64 && !EFI32 */

#if !defined(POLARSSL_HAVE_HARDCLOCK)

#define POLARSSL_HAVE_HARDCLOCK

static int hardclock_init = 0;
static struct timeval tv_init;

unsigned long hardclock( void )
{
    struct timeval tv_cur;

    if( hardclock_init == 0 )
    {
        gettimeofday( &tv_init, NULL );
        hardclock_init = 1;
    }

    gettimeofday( &tv_cur, NULL );
    return( ( tv_cur.tv_sec  - tv_init.tv_sec  ) * 1000000
          + ( tv_cur.tv_usec - tv_init.tv_usec ) );
}
#endif /* !POLARSSL_HAVE_HARDCLOCK */
