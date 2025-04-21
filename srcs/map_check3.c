/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:20:53 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/16 18:46:24 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_names(t_map *maps)
{
	int	i;

	i = 0;
	if (maps->c && ft_count_times(maps->c[1], ',') != 2)
		return (printf("Error : check C params\n"), 1);
	if (maps->f && ft_count_times(maps->f[1], ',') != 2)
		return (printf("Error : check F params\n"), 1);
	if (maps->no && (!ft_strchr(maps->no[1], '/') || !maps->no[1]))
		return (printf("Error : check NO path\n"), 1);
	if (maps->so && (!ft_strchr(maps->so[1], '/') || !maps->so[1]))
		return (printf("Error : check SO path\n"), 1);
	if (maps->ea && (!ft_strchr(maps->ea[1], '/') || !maps->ea[1]))
		return (printf("Error : check EA path\n"), 1);
	if (maps->we && (!ft_strchr(maps->we[1], '/') || !maps->we[1]))
		return (printf("Error : check WE path\n"), 1);
	return (0);
}

int	check_flood_swit(t_cub *cub, char **map_check, int *i, int *j)
{
	if (cub->maps->my_map[*i][*j + 1] == ' ' || cub->maps->my_map[*i][*j
		+ 1] == '\0')
		return (print_error(cub, "Error !\nFlood 1", map_check), 1);
	else if (cub->maps->my_map[*i][*j - 1] == ' ' || cub->maps->my_map[*i][*j
		- 1] == '\0')
		return (print_error(cub, "Error !\nFlood 2", map_check), 1);
	else if (ft_strlen(cub->maps->my_map[*i - 1]) - 2 < *j
		|| cub->maps->my_map[*i - 1][*j] == ' ' || cub->maps->my_map[*i
		- 1][*j] == '\0')
		return (print_error(cub, "Error !\nFlood 3", map_check), 1);
	else if (ft_strlen(cub->maps->my_map[*i + 1]) - 2 < *j
		|| cub->maps->my_map[*i + 1][*j] == ' ' || cub->maps->my_map[*i
		+ 1][*j] == '\0')
		return (print_error(cub, "Error !\nFlood 4", map_check), 1);
	return (0);
}

int	check_flood(t_cub *cub, char **map_check)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->lines - 1)
	{
		j = -1;
		while (++j < ft_strlen(cub->maps->my_map[i]))
		{
			if (cub->maps->my_map[i][j] == '0' || cub->maps->my_map[i][j] == 'N'
				|| cub->maps->my_map[i][j] == 'S'
				|| cub->maps->my_map[i][j] == 'W'
				|| cub->maps->my_map[i][j] == 'E')
			{
				if (check_flood_swit(cub, map_check, &i, &j) == 1)
					return (1);
			}
		}
	}
	return (0);
}

int	is_onlyfriend(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int	check_walls(t_cub *cub, char **map_check)
{
	int	i;
	int	len;

	i = 1;
	if (cub->maps->my_map)
	{
		len = ft_strlen(cub->maps->my_map[i]) - 1;
		while (i < (cub->lines - 1))
		{
			if (len != 0)
			{
				if ((cub->maps->my_map[i][0] != '1' || cub->maps->my_map[i][len
					- 1] != '1') && !is_space(cub->maps->my_map[i][len - 1])
					&& !is_space(cub->maps->my_map[i][0]))
				{
					return (print_error(cub, "Error ! \nCheck the walls !",
							map_check), 1);
				}
			}
			i++;
			len = ft_strlen(cub->maps->my_map[i]) - 1;
		}
	}
	return (0);
}
