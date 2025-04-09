/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:23 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/08 19:32:55 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_maps(t_cub *cub, char **stock_l, char **map_check)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (compare_dir(cub->maps, stock_l[i]) == 0)
		{
			free_tab(stock_l);
			print_error(cub, "Missing parameters", map_check);
			return ;
		}
		if (check_names(cub->maps) == 1 || check_params_c(cub->maps) == 1)
		{
			free_tab(stock_l);
			return (print_error(cub, NULL, map_check));
		}
		i++;
	}
	free_tab(stock_l);
}

int	check_dir(char **map_check, t_cub *cub)
{
	int	i;
	int	j;
	char	**stock_l;

	i = 0;
	j = 0;
	stock_l = ft_calloc(7, sizeof(char *));
	while (i < cub->lines)
	{
		if (!line_is_empty(map_check[i]))
		{
			stock_l[j] = ft_strdup(map_check[i]);
			printf("%s\n", stock_l[j]);
			j++;
		}
		i++;
		if (j == 6)
			break ;
	}
	if (j != 6)
	{
		free_tab(stock_l);
		return (print_error(cub, "Not enough", map_check), 1);
	}
	init_maps(cub, stock_l, map_check);
	return (i);
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
			if (cub->maps->my_map[i][j] == '0' || cub->maps->my_map[i][j] == 'N' || cub->maps->my_map[i][j] == 'S' || cub->maps->my_map[i][j] == 'W' || cub->maps->my_map[i][j] == 'E')
			{
				if (cub->maps->my_map[i][j + 1] == ' ')
					return (print_error(cub, "Error !\nFlood 1", map_check), 1);
				else if (cub->maps->my_map[i][j - 1] == ' ')
					return (print_error(cub, "Error !\nFlood 2", map_check), 1);
				else if (ft_strlen(cub->maps->my_map[i - 1]) - 2 < j
					|| cub->maps->my_map[i - 1][j] == ' ')
					return (print_error(cub, "Error !\nFlood 3", map_check), 1);
				else if (ft_strlen(cub->maps->my_map[i + 1]) - 2 < j
					|| cub->maps->my_map[i + 1][j] == ' ')
					return (print_error(cub, "Error !\nFlood 4", map_check), 1);
			}
		}
	}
	return (0);
}

int	fill_my_map(t_cub *cub, char **map_check, int i)
{
	int	j;

	j = 0;
	while (i < cub->lines)
	{
		if (!line_is_empty(map_check[i]))
		{
			cub->maps->my_map[j] = ft_strdup(map_check[i]);
			j++;
		}
		i++;
	}
	if (j == 0)
		return (print_error(cub, "Error !\nMissing map !", map_check), 1);
	cub->lines = j;
	cub->maps->long_line = longest_line(cub);
	if (check_first_last_line(cub, map_check) == 1
	|| check_walls(cub, map_check) == 1 || check_player(cub, map_check) == 1
	|| check_other_num(cub, map_check) == 1)
		return (1);
	printf("PLAYER ---> %c\n", cub->maps->player_dir);
	return (0);
}

int	check_my_map(t_cub *cub, char **map_check, int c)
{
	int	len;
	int	i;

	(void)c;
	len = ft_strlen(map_check[0]);
	i = check_dir(map_check, cub);
	if (i > 1)
	{
		if (fill_my_map(cub, map_check, i) == 1)
			return (1);
		if (check_flood(cub, map_check) == 1)
			return (1);
	}
	return (0);
}
