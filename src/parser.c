#include "automate.h"

char *readline(int fd)
{
	char *line;
	line = malloc(1024);
	int i = 0;
	line[i] = 0;
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	if (i == 0 && line[i] == 0)
		return (free(line), NULL);
	line[i + 1] = 0;
	return (line);
}

int	get_lines_count(char *filename)
{
	int fd = open(filename, O_RDONLY);
	int count = 0;
	char *line;
	while (1)
	{
		line = readline(fd);
		if (line == NULL)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int	get_nodes_count(char *filename)
{
	int	lines_count = get_lines_count(filename);
	int	*arr = calloc(lines_count, sizeof(int));
	int	idx = 0;
	char *line;
	int fd = open(filename, O_RDONLY);

	while (1)
	{
		line = readline(fd);
		if (line == NULL)
			break ;
		int i = 0;
		while (line[i] && line[i] != ' ')
			i++;
		int a = atoi(line), b = atoi(&line[i]);
		for (i = 0; i < idx && arr[i] != a; i++);
		if (i == idx)
			arr[idx++] = a;
		for (i = 0; i < idx && arr[i] != b; i++);
		if (i == idx)
			arr[idx++] = b;
		free(line);
	}
	free(arr);
	return (idx);
}

int	push_node(t_node *nodes, int idx, int id, int to, char ett)
{
	int	ret = 0;
	int i = -1;
	while (++i < idx && nodes[i].id != id);
	if (i == idx)
	{
		nodes[i].id = id;
		nodes[i].con = 	NULL;
		ret = 1;
	}
	if (ett)
	{
		t_con	*con = malloc(sizeof(t_con));
		con->to = to;
		con->ett = ett;
		con->next = NULL;
		t_con	*cur = nodes[i].con;
		if (cur == NULL)
			nodes[i].con = con;
		else
		{
			while (cur->next)
				cur = cur->next;
			cur->next = con;
		}
	}
	return (ret);
}

void	create_nodes(int fd, t_node **nodes_ptr, char *filename)
{
	int	nodes_count = get_nodes_count(filename);
	t_node	*nodes = calloc(nodes_count + 1, sizeof(t_node));
	int node_in, node_out;
	char	ett;
	int		idx = 0;
	char	*line;
	int	line_count = get_lines_count(filename), i = -1;

	while (++i < line_count - 2)
	{
		line = readline(fd);
		node_in = atoi(line);
		int j = 0;
		while (line[j] && line[j] != ' ')
		 	j++;
		node_out = atoi(&line[j]);
		while (line[j] && line[j] == ' ')
		 	j++;
		while (line[j] && line[j] != ' ')
		 	j++;
		while (line[j] && line[j] == ' ')
		 	j++;
		ett = line[j];
		idx += push_node(nodes, idx, node_in, node_out, ett);
		idx += push_node(nodes, idx, node_out, 0, 0);
		free(line);
	}
	nodes[idx].con = (t_con *)-1;
	*nodes_ptr = nodes;
}

void	extract_io(int fd, t_node **io_ptr, t_node *nodes)
{
	char *line = readline(fd);
	int 	count = 1;
	int i = 0;
	while(line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
			count++;
		while (line[i] && line[i] != ' ')
			i++;
	}
	t_node *io = malloc(count * sizeof(t_node));
	int j = 0;
	i = 0;
	while(line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == 0)
			break ;
		int	id = atoi(&line[i]);
		int	k = 0;
		while (nodes[k].con != (t_con *)-1 && nodes[k].id != id)
			k++;
		io[j++] = nodes[k];
		while (line[i] && line[i] != ' ')
			i++;
	}
	io[j].con = (t_con *) - 1;
	free(line);
	*io_ptr = io;
}

t_data *ft_parser(char *filename)
{
	t_data	*data = malloc(sizeof(t_data));
	int fd = open(filename, O_RDONLY);
	create_nodes(fd, &data->nodes, filename);
	extract_io(fd, &data->ins, data->nodes);
	extract_io(fd, &data->outs, data->nodes);
	return (data);
}


/* int main(int c, char **v)
{
	t_data	*data = ft_parser(v[1]);
	t_node *nodes = data->nodes;

	
	find_word(data, "ou");

	for(int i = 0; 
	 i++)
		printf("%d ", data->ins[i].id);
	printf("\n");
	for(int i = 0; data->outs[i].con != (t_con *)-1; i++)
		printf("%d ", data->outs[i].id);
	printf("\n");

	int idx = 8;
	int i = 0;
	while (nodes[i].con != (t_con *)-1 && nodes[i].id != idx)
		i++;
	t_con *cur = nodes[i].con;
	while (cur)
	{
		printf("%d ---- (%c) -----> %d\n", nodes[i].id, cur->ett, cur->to);
		cur = cur->next;
	}
	return (0);
 }*/