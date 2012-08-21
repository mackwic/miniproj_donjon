
#include "test.h"
#include "arc_list.h"

size_t len(struct arc_list * l)
{
    size_t t = 0;

    for(; l; l = l->next )
	t++;

    return t;
}

struct arc_list* add(struct arc_list * l, struct arc * node)
{
    struct arc_list * head;
    MALLOC(sizeof(*head), head);

    head->node = node;
    head->next = l;

    return head;
}

