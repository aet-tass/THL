#include "automate.h"

static char *random_string()
{
        const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char *p = (char *) malloc(3);
        bzero(p , 3);
        p[0] = charset[rand() % 50];
        p[1] = charset[rand() % 50];
        return (p);
}

static void	gen_io_ins(t_node *nodes, int fd, int in)
{
	for (int i = 0; nodes[i].con != (t_con *)-1; i++)
	{
		char *id = random_string();
		dprintf(fd, "\t%s [label= \"\", shape=none]\n", id);
		if (in)
			dprintf(fd, "\t%s -> %d\n", id, nodes[i].id);
		else
			dprintf(fd, "\t%d -> %s\n", nodes[i].id, id);
	}
}

void	gen_dot_file(t_data *data, char *name)
{
	int fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		printf("Fd Error\n");
		exit (1);
	}
	dprintf(fd, "digraph g \n{\n");
	for (int i = 0; data->nodes[i].con != (t_con *)-1; i++)
	{
		t_con	*cur = data->nodes[i].con;
		while (cur)
		{
			dprintf(fd, "\t%d -> %d [label=%c]\n", data->nodes[i].id, cur->to, cur->ett);
			cur = cur->next;
		}
	}
	gen_io_ins(data->ins, fd, 1);
	gen_io_ins(data->outs, fd, 0);
	dprintf(fd, "}\n");
}
