#ifndef _TEST_
#define _TEST_

#ifdef _TEST

#include <check.h>
#define MARK mark_point()
#define DEBUG(args...) printf(args)

#define MALLOC(size, ptr)			\
    if(!(ptr = malloc(size))) {			\
	printf("malloc error, hard failure");	\
	exit(EXIT_FAILURE);			\
    }

#else

#define MARK
#define DEBUG(args...)
#define MALLOC(size, ptr) \
    if(!(ptr = malloc(size))) {			\
	printf("malloc error, hard failure");	\
	exit(EXIT_FAILURE);			\
    }

#endif /* TEST */
#endif /* _TEST_ */
