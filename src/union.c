#include "automate.h"


int get_max_id(t_node *nodes)
{
    int max;
    int i;

    max = nodes->id;
    i = -1;
    while (nodes[++i].con != (t_con *)-1)
    {
        if (max < nodes[i].id)
            max = nodes[i].id;
    }
    return (max);
}

t_node  *join_nodes(t_node *n1, t_node *n2)
{
    t_node  *n;
    int     n1_size;
    int     n2_size;
    int     i;
    int     j;

    n1_size = get_nodes_size(n1);
    n2_size = get_nodes_size(n2);
    n = calloc(n1_size + n2_size + 1, sizeof(t_node));
    i = -1;
    while (++i < n1_size)
        n[i] = n1[i];
    j = -1;
    while (++j <= n2_size)
        n[i++] = n2[j];
    return (n);
}

t_automate  *automates_union(t_automate *a, t_automate *b)
{
    t_automate  *auto_union;
    t_automate  *copy_a;
    t_automate  *copy_b;

    auto_union = malloc(sizeof(t_automate));
    copy_a = copy_autmate(a, 0);
    copy_b = copy_autmate(b, get_max_id(a->nodes) + 1);
    auto_union->nodes = join_nodes(copy_a->nodes, copy_b->nodes);
    auto_union->ins = join_nodes(copy_a->ins, copy_b->ins);
    auto_union->outs = join_nodes(copy_a->outs, copy_b->outs);
    return (auto_union);
}

int main(int c, char **v)
{
	t_automate	*a = ft_parser(v[1]);
	t_automate	*b = ft_parser(v[2]);
	t_automate  *u = automates_union(a, b);
    // print_nodes(a->ins);
    // printf("--------------------\n");
    // print_nodes(b->ins);
    // print_nodes(b->outs);
    // print_nodes(b->nodes);
    printf("--------------------\n");
    print_nodes(u->nodes);
    printf("--------------------\n");
    if (find_word(u, v[3]))
        printf("YES\n");
    else
        printf("NO\n");
	return (0);
}