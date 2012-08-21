#ifndef _t_parser_
#define _t_parser_

#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "../src/test.h"
#include "../src/parser.h"

#define MM mark_point()

/*
int count_arr(void * arr, size_t size);

int is_all_eq (char ** arr1, char ** arr2, int how_many);
*/

int count_arr(void * arr, size_t size)
{
    MARK;
    int i = 0;
    void * ptr = arr;

    MARK;
    while (ptr != NULL)
    {
	MARK;
	ptr += size;
	i++;
    }
    MARK;

    return i;
}

int is_all_eq (char ** arr1, char ** arr2, int how_many)
{
    MARK;
    char **ptr1 = arr1, **ptr2 = arr2;
    int i = 0;

    MARK;
    while (ptr1 && ptr2 && (strcmp(*ptr1,*ptr2) == 0))
    {
	MARK;
	ptr1++;
	ptr2++;
	i++;
    }

    MARK;
    return (ptr1 == NULL && ptr2 == NULL && how_many == i);
}


START_TEST (test_preprocess)
{
    const char * input = "PLOP\n# CECI EST UN COMMENT\n\nPLOP2\nTESTi";
    char * expected[3] = { "PLOP", "PLOP2", "TESTi" };
    char ** output = NULL;

    MM;
    output = preprocess(input);
    MM;

    printf("size of output: %d\n", sizeof(output));
    fail_unless (sizeof(output) == 3, NULL);
    MM;
    fail_unless (is_all_eq (output, expected, 3), NULL);
    MM;

    free (output);
}
END_TEST

#endif
