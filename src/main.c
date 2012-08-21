#include <stdio.h>
#include <stdlib.h>

#include "donjon.h"
#include "parser.h"


/*****************************************************************************/
#ifdef TEST

#include <check.h>
#include "../test/t_parser.c"

Suite * parser_suite (void)
{
    Suite * s = suite_create("Parser");

    TCase *tc = tcase_create ("Parse");
    tcase_add_test (tc, test_preprocess);
    suite_add_tcase (s, tc);

    return s;
}

struct donjon * main_test(const char * file)
{
    Suite * s;
    SRunner * sr;
    int failed;

    s = parser_suite();
    sr = srunner_create(s);

    srunner_run_all (sr, CK_NORMAL);
    failed = srunner_ntests_failed (sr);

    if (failed != 0)
	return NULL;
    else
	return parse(file);
}
#endif
/*****************************************************************************/

int main (int argc, char const* argv[])
{
    struct donjon *doj = NULL;

    if (argc < 2)
    {
	printf("Usage: ./stein <file.dj>\n");
	return 1;
    }

#ifndef TEST
    doj = parse(argv[1]);
#else
    doj = main_test(argv[1]);
#endif

    if (doj == NULL)
	return 1;

    return 0;
}

