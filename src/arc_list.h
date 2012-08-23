#ifndef _arc_list_
#define _arc_list_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "donjon.h"

struct arc_list
{
    struct arc * node;
    struct arc_list * next;
};

#define empty_list() NULL
#define is_empty(l) (!(l))

size_t len(struct arc_list * l);

struct arc_list* add(struct arc_list * l, struct arc * node);

void free_arc_list(struct arc_list * list);

#endif
