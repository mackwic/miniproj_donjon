
#include "debug.h"
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

void free_arc_list(struct arc_list * list)
{
    struct arc_list * ptr1 = list, * ptr2;
    DEBUG_SET_INT(i, 0);
    DEBUGN("FREE arc_list");

    while (ptr1 != NULL)
    {
	DEBUG("FREE elt %d of arc_list", i);
	ptr2 = ptr1;
	free(ptr2);

	ptr1 = ptr1->next;
	DEBUG_DO(i++);
    }

    DEBUGN("FREE main pointer arc_list");
    free(list);

    DEBUGN("FREE END TASK");
}
