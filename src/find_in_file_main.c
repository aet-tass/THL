#include "automate.h"

int main(int c, char **v)
{
	t_automate	*data = ft_parser(v[1]);
	find_in_file(data, v[2]);
	return (0);
}
