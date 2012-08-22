#ifndef _TEST_
#define _TEST_

#ifdef _DEBUG

#define DEBUG(args...) printf(args)
#define DEBUGN(args...) printf(args"\n")

#define DEBUG_DO(something) something
#define DEBUG_DO_START if (1)
#define DEBUG_DO_END }

#define DEBUG_SET_INT(name, value) int name = value
#define DEBUG_SET_S_INT(name, value) static int name = value
#define DEBUG_SET_STRING(name, value) char * name = "value"

#else

#define DEBUG(args...)
#define DEBUGN(args...)

#define DEBUG_DO(something)
#define DEBUG_DO_START if (0)
#define DEBUG_DO_END }

#define DEBUG_SET_INT(name, value)
#define DEBUG_SET_S_INT(name, value)
#define DEBUG_SET_STRING(name, value)

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
