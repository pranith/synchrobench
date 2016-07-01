#ifndef __GCC_DEFNS_H__
#define __GCC_DEFNS_H__

#define CACHE_LINE_SIZE 64

#define CAS(_a, _o, _n)                                                 \
({                                                                      \
    __typeof__(_o) __o = _o; \
    __atomic_compare_exchange_n(_a, &__o, _n, 1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED);      \
    __o; \
})

#define FAS(_a, _n)                                                     \
({                                                                      \
    __atomic_exchange_n(_a, _n, __ATOMIC_SEQ_CST);                      \
})

#define CAS64(_a, _o, _n) 0 /*stub*/

/* Update Integer location, return Old value. */
#define CASIO CAS
#define FASIO FAS
/* Update Pointer location, return Old value. */
#define CASPO CAS
#define FASPO FAS
/* Update 32/64-bit location, return Old value. */
#define CAS32O CAS
#define CAS64O CAS64

/*
 * II. Memory barriers. 
 *  WMB(): All preceding write operations must commit before any later writes.
 *  RMB(): All preceding read operations must commit before any later reads.
 *  MB():  All preceding memory accesses must commit before any later accesses.
 * 
 *  If the compiler does not observe these barriers (but any sane compiler
 *  will!), then VOLATILE should be defined as 'volatile'.
 */

#define MB() __atomic_thread_fence(__ATOMIC_SEQ_CST) 
/*#define MB()  __asm__ __volatile__ ("lock; addl $0,0(%%esp)" : : : "memory")*/
#define WMB() __atomic_thread_fence(__ATOMIC_RELEASE)
#define RMB() __atomic_thread_fence(__ATOMIC_ACQUIRE)
#define VOLATILE /*volatile*/

/* On Intel, CAS is a strong barrier, but not a compile barrier. */
#define RMB_NEAR_CAS() WMB()
#define WMB_NEAR_CAS() WMB()
#define MB_NEAR_CAS()  WMB()


/*
 * III. Cycle counter access.
 */

#include <time.h>
struct timespec timer;

typedef unsigned long long tick_t;

#define RDTICK()                                                            \
({                                                                          \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer);                        \
    unsigned long long ___ticks = timer.tv_sec * 1E6 + timer.tv_nsec / 1000;                              \
    ___ticks; \
})


#ifndef MB_NEAR_CAS
#define RMB_NEAR_CAS() RMB()
#define WMB_NEAR_CAS() WMB()
#define MB_NEAR_CAS()  MB()
#endif

typedef unsigned char      _u8;
typedef unsigned short     _u16;
typedef unsigned int       _u32;
typedef unsigned long long _u64;

#endif
