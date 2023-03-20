#include "automate.h"

void    print_nodes(t_node *n)
{
    int i;

    i = -1;
    while (n[++i].con != (t_con *)-1)
    {
        printf("node_id: %d\n", n[i].id);
        printf("connections: ");
        t_con *cur = n[i].con;
        while(cur)
        {
            printf("\t(%c) -> [%d]", cur->ett, cur->to);
            cur = cur->next;
        }
        printf("\n\n");
    }
}