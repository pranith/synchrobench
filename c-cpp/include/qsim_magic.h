#ifndef _QSIM_MAGIC_H
#define _QSIM_MAGIC_H

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef USE_QSIM

#if defined(__arm__) || defined(__aarch64__)

#define qsim_magic_enable()				\
	asm volatile("msr pmcr_el0, %0" :: "r" (0xaaaaaaaa));
#define qsim_magic_disable() 				\
	asm volatile("msr pmcr_el0, %0" :: "r" (0xfa11dead));

#elif defined(__i386__) || defined(__x86_64__)

#define qsim_magic_enable()				\
	asm volatile("cpuid;"::"a"(0xaaaaaaaa):"ebx","ecx","edx");
#define qsim_magic_disable()				\
	asm volatile("cpuid;"::"a"(0xfa11dead):"ebx","ecx","edx");

#endif

#define APP_START() qsim_magic_enable()
#define APP_END()   qsim_magic_disable()

__attribute__((unused))
static void qsim_sig_handler(int signo)
{
	char c;
	qsim_magic_disable();
	printf("Callbacks disabled. Quit(y/n)?");
	scanf("%c", &c);

	if (c == 'y')
		exit(0);
}

#define qsim_init()					\
do {							\
	signal(SIGINT, qsim_sig_handler);		\
} while(0);


#else
#define APP_START() 
#define APP_END()
#endif

#endif /* _QSIM_MAGIC_H */
