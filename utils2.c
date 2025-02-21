#include "cube.h"

int line_is_empty(char *line)
{
	int i;

	i = 0;
	while (line && (line[i] == '\t' || line[i] == ' ' || line[i] == '\n'))
		i++;
	if (line[i])
		return (0);
	return (1);
}

int	ft_count_times(char *str, char c)
{
	int i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == c)
			res++;
		i++;
	}
	return (res);
}

int	longest_line(t_cub *cub)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cub->maps->my_map[0]);
	while (i < cub->lines)
	{
		if (len < ft_strlen(cub->maps->my_map[i]))
			len = ft_strlen(cub->maps->my_map[i]);
		i++;
	}
	return (len);
}
