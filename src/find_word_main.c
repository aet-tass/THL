#include "automate.h"

int main(int c, char **v)
{
	t_data	*data = ft_parser(v[1]);
	if (find_word(data, v[2]))
		printf("YES\n");
	else
		printf("NO\n");
	return (0);
 }