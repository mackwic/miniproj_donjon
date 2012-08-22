#ifndef _TEST_
#define _TEST_

#ifdef _DEBUG

#define DEBUG(args...) printf(args)
#define DEBUGN(args...) printf(args"\n")

#else

#define DEBUG(args...)
#define DEBUGN(args...)

#endif


#ifdef _TEST

#include <check.h>
#define MARK mark_point()

#define MALLOC(size, ptr)			\
    if(!(ptr = malloc(size))) {			\
	printf("malloc error, hard failure");	\
	exit(EXIT_FAILURE);			\
    }

#else

#define MARK
#define MALLOC(size, ptr) \
    if(!(ptr = malloc(size))) {			\
	printf("malloc error, hard failure");	\
	exit(EXIT_FAILURE);			\
    }

#endif /* TEST */
#endif /* _TEST_ */
