#include "automate.h"

static int	dive(t_data *data, int id, char *word)
{
	t_node	*nodes = data->nodes;
	t_con	*cur;
	int	i = -1;
	if (*word == 0)
		return 1;
	while (nodes[++i].con != (t_con *)-1)
	{
		if (nodes[i].id == id)
		{
			cur = nodes[i].con;
			while (cur)
			{
				if (cur->ett == *word)
				{
					if (word[1] == 0)
					{
						for (int j = 0; data->outs[j].con != (t_con *)-1; j++)
							if (data->outs[j].id == cur->to)
								return (1);
						return 0;
					}
					int	res = dive(data, cur->to, &word[1]);// should return 1 if success 0 if fail
					if (res)
						return (1);
				}
				cur = cur->next;
			}
		}
	}
	return (0);
}

int	find_word(t_data *data, char *word)
{
	int		res = 0;
	t_node	*node;
	t_con	*cur;
	int	i = -1;
	if (word == NULL && *word == 0)
		return 0;
	while (data->ins[++i].con != (t_con *)-1)
	{
		node = &(data->ins[i]);
		cur = node->con;
		while (cur)
		{
			if (cur->ett == *word)
				res = dive(data, cur->to, &word[1]);
			cur = cur->next;
		}
	}
	return (res);
}