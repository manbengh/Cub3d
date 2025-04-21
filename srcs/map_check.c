/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:35:23 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/18 21:50:39 by ahbey            ###   ########.fr       */
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
		}
		if (check_names(cub->maps) == 1 || check_params_c(cub->maps) == 1)
		{
			free_tab(stock_l);
			print_error(cub, NULL, map_check);
		}
		i++;
	}
	free_tab(stock_l);
}

int	check_dir(char **map_check, t_cub *cub, int i)
{
	int		j;
	char	**stock_l;

	j = 0;
	stock_l = ft_calloc(7, sizeof(char *));
	if (stock_l == NULL)
		return (print_error(cub, "Error : Malloc ", map_check), 1);
	while (i < cub->lines)
	{
		if (!line_is_empty(map_check[i]))
		{
			stock_l[j] = ft_strdup(map_check[i]);
			j++;
		}
		i++;
		if (j == 6)
			break ;
	}
	if (j != 6)
	{
		free_tab(stock_l);
		return (print_error(cub, "Not enough\n", map_check), 1);
	}
	init_maps(cub, stock_l, map_check);
	return (i);
}

int	check_flood_error(char str)
{
	if (str == '0' || str == 'N' || str == 'S' || str == 'W' || str == 'E')
		return (0);
	return (1);
}

int	fill_my_map(t_cub *cub, char **map_check, int i)
{
	int	j;

	j = 0;
	while (i < cub->lines)
	{
		cub->maps->my_map[j] = ft_strdup(map_check[i]);
		if (cub->maps->my_map[j] == NULL)
			return (print_error(cub, "Erro : Malloc", map_check), 1);
		j++;
		i++;
	}
	if (j == 0)
		return (print_error(cub, "Error !\nMissing map !", map_check), 1);
	cub->lines = j;
	cub->maps->long_line = longest_line(cub);
	if (check_first_last_line(cub, map_check) == 1
		|| check_walls(cub, map_check) == 1 || check_player(cub, map_check) == 1
		|| check_other_num(cub, map_check, 0) == 1)
		return (1);
	return (0);
}

int	check_my_map(t_cub *cub, char **map_check, int c)
{
	int	len;
	int	i;

	(void)c;
	len = ft_strlen(map_check[0]);
	i = check_dir(map_check, cub, 0);
	if (i > 1)
	{
		if (fill_my_map(cub, map_check, i) == 1)
			return (1);
		if (check_flood(cub, map_check) == 1)
			return (1);
	}
	return (0);
}
