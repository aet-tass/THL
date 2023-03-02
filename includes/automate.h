#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct s_con
{
	int	to;
	char	ett;
	struct s_con *next;
}	t_con;

typedef struct s_node
{
	int	id;
	t_con	*con;
}	t_node;

typedef	struct s_data
{
	t_node	*nodes;
	t_node	*ins;
	t_node	*outs;
}	t_data;

t_data 	*ft_parser(char *filename);
void	gen_dot_file(t_data *data, char *name);
int		find_word(t_data *data, char *word);
void	find_in_file(t_data *data, char *filename);



#endif
