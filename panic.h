#ifndef PANIC_H
#define PANIC_H

#include <stdio.h>
#include <stdlib.h>

#define panic(STR)          \
	do {                    \
		fputs(STR, stderr); \
		exit(1);            \
	} while (0)

#define panicf(FMT, ...)                   \
	do {                                   \
		fprintf(stderr, FMT, __VA_ARGS__); \
		exit(1);                           \
	} while (0)

#endif /* PANIC_H */
