#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int cmd(char * input)
{
    char * token;
    int len = 0;

    if (strcmp(input, "QUIT\n") == 0 || strcmp(input, "quit\n") == 0
	    || strcmp(input, "EXIT\n") == 0 || strcmp(input, "exit\n") == 0
	    || strcmp(input, "CLOSE\n") == 0|| strcmp(input, "close\n") == 0
	    || strcmp(input, "END\n") == 0 || strcmp(input, "end\n") == 0
	    )
	return 1;

    token = strtok(input, " ");
    len = strlen(token);

    if (token[len-1] == '\n')
	token[len-1] = '\0';

    if (strcmp(token, "COST") == 0 || strcmp(token, "cost") == 0)
    {
	printf("cost detected\n");
    }
    else if (strcmp(token, "PATH") == 0 || strcmp(token, "path") == 0)
    {
	printf("path detected\n");
    }

    return 0;
}

int main (int argc, char const* argv[])
{
    struct donjon *doj = NULL;
    char buff[80];

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
    {
	printf("FATAL: impossible to create the map of the donjon, abort\n");
	return 1;
    }

    while (fgets(buff, 80, stdin))
    {
	if(cmd(buff))
	    break;
    }

    return 0;
}

