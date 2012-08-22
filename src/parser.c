#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#include "test.h"

#include "donjon.h"
#include "arc_list.h"

#define MAX_LINES 500
#define MAX_COLLUMN 80


/* separe une string par:
 * * ses fins de ligne
 * * oublie les lignes vides
 * * oublie les commentaires
 */
int preprocess(const char * input, char ** res)
{
	DEBUG("[preprocess] BEGINNING OF TASK\n");
	MARK;
	char buff[MAX_COLLUMN];
	int pos = 0;
	int count = 0;
	int skip_line = 0;

	bzero(buff, MAX_COLLUMN);

	MARK;
	while (input != NULL && *input != NULL && *input != '\0')
	{
		MARK;
		DEBUG("[preprocess] %c[%d]\t%d\n", *input, *input, count);
		if (*input == '\n')
		{
			MARK;
			if (skip_line || pos == 0)
			{
				skip_line = 0;
				input++;
				continue;
			}

			buff[pos++] = '\0';
			MALLOC(pos * (sizeof *buff), res[count]);

			strcpy(res[count], buff);
			bzero(buff, MAX_COLLUMN);

			pos = 0;
			count++;
		}
		else
		{
			MARK;
			if (*input == '#')
				skip_line = 1;

			if (!skip_line && *input != ':')
				buff[pos++] = *input;
		}

		input++;
	}

	res[count] = NULL;
	DEBUG("[preprocess] END OF TASK\n");
	return 0;
}

/* separe une string par ses espaces, initialise res */
int divide_str(const char * input, char *** res)
{
	DEBUG("[divide_str] BEGINNING OF TASK\n");
	MARK;
	char buff[MAX_COLLUMN];
	int pos = 0;
	char ** ptr;

	MALLOC(MAX_LINES * (sizeof **res), *res);
	ptr = *res;

	bzero(buff, MAX_COLLUMN);
	MARK;

	while (*input != '\0')
	{
		DEBUG("[divide_str] %c \t %d\n", *input, pos);
		MARK;
		if (*input == ' ')
		{
			MARK;
			buff[pos++] = '\0';
			MALLOC(pos * (sizeof *buff), *ptr);

			strcpy(*ptr, buff);
			bzero(buff, MAX_COLLUMN);

			pos = 0;
			ptr++;
		}
		else
		{
			MARK;
			buff[pos++] = *input;
		}

		input++;
	}

	*ptr = NULL;
	DEBUGN("[divide_str] END OF TASK");
	return 0;
}

int get_room_nb(char ** words, int * nb)
{
    int i = 0;
    i = atoi(*words);

    if (nb == 0)
	return -1;

    *nb = i;
    return 0;
}

int set_monster_in_room(int rooms[], char ** words)
{
    int nb = 0;
    int cost = 0;

    nb = atoi(*words);
    words++;
    cost = atoi(*words);

    if (nb == 0 || cost == 0)
	return -1;

    rooms[nb] = -1 * cost;

    return 0;
}

int set_brewery_in_room(int rooms[], char ** words)
{
    int nb = 0;
    int cost = 0;

    nb = atoi(*words);
    words++;
    cost = atoi(*words);

    if (nb == 0 || cost == 0)
	return -1;

    rooms[nb] = -1 * cost;

    return 0;
}

int set_trap_in_room(int rooms[], char ** words)
{
    int nb = 0;
    nb = atoi(*words);

    if (nb == 0)
	return -1;

    rooms[nb] = INT_MIN;

    return 0;
}

void free_dyn_array(char ** arr)
{
    DEBUG_SET_S_INT(nb_free, 0);
    char ** ptr = arr;
    DEBUG_SET_INT(i, 0);
    DEBUG_DO(nb_free++);
    DEBUG("FREE %d of [dyn_array] BEGIN\n", nb_free);

    while (ptr != NULL && *ptr != NULL)
    {
	DEBUG("FREE %d elt %d[%p]\n", nb_free, i, ptr);
	free(*ptr);
	ptr++;
	DEBUG_DO(i++);
    }

    DEBUG("FREE %d ENDED, FREE OF MAIN PTR\n", nb_free);
    free(arr);
    DEBUG("FREE %d TASK END\n", nb_free);
}

/* appelle preprocess, puis divide_str,
 * puis construit une struct donjon* a partir des tokens
 */
int process(const char * input, struct donjon * res)
{
	DEBUGN("[process] BEGINNING OF TASK");
	MARK;
	char ** lines, ** ptr_lines;
	char ** words, ** ptr_words;

	MALLOC(MAX_LINES * (sizeof *lines), lines);
	ptr_lines = lines;

	int nb_rooms;
	int rooms[1000];
	struct arc_list * arcs = NULL;

	MARK;
	preprocess(input, lines);

	while (lines != NULL && *lines != NULL)
	{
		DEBUG("[process] current = {%s}\n", *lines);
		MARK;

		MALLOC(MAX_COLLUMN * (sizeof *words), words);
		ptr_words = words;

		divide_str(*lines, &words);

		MARK;
		if (strcmp(*words, "ROOMS") == 0)
		{
			MARK;
			if(get_room_nb(words+1, &nb_rooms))
			{
			    printf("ERROR: impossible to get the nomber of the roums\n");
			    return -1;
			}
		}
	MALLOC(MAX_COLLUMN * (sizeof *words), words);
	ptr_words = words;
		else if (strcmp(*words, "MONSTER") == 0)
		{
			MARK;
			if(set_monster_in_room(rooms, words + 1))
			{
			    printf("ERROR: impossible to set the monster in the roum\n");
			    return -1;
			}
		}
		else if (strcmp(*words, "BREWERY") == 0)
		{
			MARK;
			if(set_brewery_in_room(rooms, words + 1))
			{
			    printf("ERROR: impossible to set the brewery in the room\n");
			    return -1;
			}
		}
		else if (strcmp(*words, "DEAD") == 0)
		{
			MARK;
			if(set_trap_in_room(rooms, words + 2))
			{
			    printf("ERROR: impossible to set the trap in the room");
			    return -1;
			}
		}
		else if (strcmp(*words, "ARC") == 0)
		{
			MARK;

			struct arc * arcc = create_arc(
				atoi(*(++words)),
				atoi(*(++words)),
				atoi(*(++words))
				);

			arcs = add(arcs, arcc);
		}
		MARK;
		lines++;
		free_dyn_array(ptr_words);
	}

	MARK;
	free_dyn_array(ptr_lines);

	res = create_donjon(nb_rooms, rooms, arcs);
	DEBUGN("[process] END OF TASK");
	return 0;
}

/* lit un fichier et le place dans une chaine de char, initialise buff */
int str_of_file(const char * filename, char ** buff)
{
    MARK;
    FILE * file;
    int size = 0;

    file = fopen (filename, "r");
    if (file == NULL)
	return errno;
    MARK;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    MARK;

    *buff = calloc(size + 5, (sizeof **buff));

    if (*buff == NULL)
    {
	printf("FATAL: allocation error in parser.c at line 291\n");
	exit(EXIT_FAILURE);
    }

    fread (*buff, (sizeof **buff), size, file);
    /* *buff[size+1] = '\0'; ca plante... mais est-ce necessaire ? */
    /* OUI */

    DEBUG("PLOP 2\n");

    MARK;

    fclose(file);
    return 0;
}


/* appelle str_of_file, puis process */
struct donjon * parse(const char * filename)
{
    char ** input = NULL;
    struct donjon * res = NULL;

    MALLOC(MAX_LINES * (sizeof *input), input);

    MARK;
    if (str_of_file(filename, input))
    {
	printf("ERROR: impossible to read the map file (bad name ?)");
	exit(EXIT_FAILURE);
    }

    MARK;
    if (process (*input, res))
    {
	printf("ERROR: something strange happens during the parsing of the map file...");
	exit(EXIT_FAILURE);
    }

    return res;
}

