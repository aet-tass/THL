#include "automate.h"

t_automate  *t_automate_etoile(t_automate *automate)
{
    t_automate  *copy;
    t_node      *node;
    t_con       *cur;
    int         i;
    int         j;
    int         k;

    copy = copy_autmate(automate, 0);
    i = -1;
    while (copy->outs[++i].con != (t_con *)-1)
    {
        k = 0;
        while (copy->nodes[k].id != copy->outs[i].id)
            k++;
        node = &copy->nodes[k];
        j = -1;
        while (copy->ins[++j].con != (t_con *)-1)
        {
            if (copy->ins[j].id == node->id)
                continue;
            cur = node->con;
            if (cur == NULL)
                node->con = copy->ins[j].con;
            else{
                while (cur->next)
                    cur = cur->next;
                cur->next = copy->ins[j].con;
            }
        }
    }
    return (copy);
}

int main(int c, char **v)
{
	t_automate	*au = ft_parser(v[1]);
    t_automate  *data = t_automate_etoile(au);
	if (find_word(data, v[2]))
		printf("YES\n");
	else
		printf("NO\n");
	return (0);
 }
