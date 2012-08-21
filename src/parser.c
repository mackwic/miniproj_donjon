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
	MARK;
	char buff[MAX_COLLUMN];
	int pos = 0;
	int count = 0;
	int skip_line = 0;

	bzero(buff, MAX_COLLUMN);

	MARK;
	while (input != NULL && *input != '\0')
	{
		MARK;
		DEBUG("%c\t%d\n", *input, count);
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
			MALLOC(pos * sizeof(*buff), res[count]);

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
	return 0;
}

/* separe une string par ses espaces, initialise res */
int divide_str(const char * input, char ** res)
{
	MARK;
	char buff[MAX_COLLUMN];
	int pos = 0;
	char ** ptr;

	MALLOC(50 * sizeof(*res), res);
	ptr = res;

	bzero(buff, MAX_COLLUMN);
	MARK;

	while (*input != '\0')
	{
		MARK;
		if (*input == ' ')
		{
			MARK;
			buff[pos++] = '\0';
			MALLOC(pos * sizeof(*buff), ptr);

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
    char ** ptr = arr;

    while (ptr)
    {
	free(*ptr);
	ptr++;
    }

    free(arr);
}

/* appelle preprocess, puis divide_str,
 * puis construit une struct donjon* a partir des tokens
 */
int process(const char * input, struct donjon * res)
{
	MARK;
	char ** lines;
	char ** words;

	MALLOC(MAX_LINES * (sizeof *lines), lines);
	MALLOC(MAX_COLLUMN * (sizeof *words), words);

	int nb_rooms;
	int rooms[1000];
	struct arc_list * arcs = NULL;

	MARK;
	preprocess(input, lines);

	while (lines != NULL)
	{
		MARK;
		divide_str(*lines, words);

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
	}

	MARK;
	free_dyn_array(lines);
	free_dyn_array(words);

	res = create_donjon(nb_rooms, rooms, arcs);
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

    *buff = calloc(size + 2, sizeof(**buff));
    fread (*buff, sizeof(**buff), size, file);
    *buff[size+1] = '\0';
    MARK;

    return 0;
}


/* appelle str_of_file, puis process */
struct donjon * parse(const char * filename)
{
    char ** input = NULL;
    struct donjon * res = NULL;

    MARK;
    if (str_of_file(filename, input))
	exit(EXIT_FAILURE);

    MARK;
    if (process (*input, res))
	exit(EXIT_FAILURE);

    return res;
}
