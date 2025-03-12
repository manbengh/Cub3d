/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:37:09 by ahbey             #+#    #+#             */
/*   Updated: 2025/03/12 14:37:12 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_player(t_cub *cub, char **map_check)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	count = 0;
	while (i < cub->lines - 1)
	{
		j = 0;
		while (j < ft_strlen(cub->maps->my_map[i]) - 1)
		{
			if (cub->maps->my_map[i][j] == 'E' || cub->maps->my_map[i][j] == 'W'
				|| cub->maps->my_map[i][j] == 'N' || cub->maps->my_map[i][j] == 'S')
			{
				cub->maps->player_dir = cub->maps->my_map[i][j];
				count++;
			}
				j++;
		}
		i++;
	}
	if (count != 1)
		return (print_error(cub, "Error ! Check Player !", map_check), 1);
	return (0);
}

int	check_other_num(t_cub *cub, char **map_check)
{
	int	i;
	int	j;

	i = 0;
	while (++i < cub->lines - 1)
	{
		j = -1;
		while (++j < ft_strlen(cub->maps->my_map[i]) - 1)
		{
			if (ft_isdigit(cub->maps->my_map[i][j]) == 1 || cub->maps->my_map[i][j] == ' ')
			{
				if (cub->maps->my_map[i][j] != '1' && cub->maps->my_map[i][j] != '0' && cub->maps->my_map[i][j] != ' ')
					return (print_error(cub, "Error ! \n1 or 0 only !", map_check), 1);
			}
			else if (ft_isdigit(cub->maps->my_map[i][j]) == 0)
			{
				if (cub->maps->my_map[i][j] != 'S' && cub->maps->my_map[i][j] != 'E'
					&& cub->maps->my_map[i][j] != 'W' && cub->maps->my_map[i][j] != 'N')
					return (print_error(cub, "Error !\nNothing other than S, N, E, W, 0 or 1 !", map_check), 1);
			}
		}
	}
	return (0);
}

int	check_first_last_line(t_cub *cub, char **map_check)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cub->maps->my_map[0]) - 1;
	while (i < len)
	{
		if (cub->maps->my_map[0][i] != '1' && cub->maps->my_map[0][i] != ' ')
			return (print_error(cub, "Error ! \nCheck the first line !", map_check), 1);
		i++;
	}
	i = 0;
	len = ft_strlen(cub->maps->my_map[cub->lines - 1]);
	while (i < len)
	{
		if (line_is_empty(cub->maps->my_map[cub->lines - 1])
			&& cub->maps->my_map[cub->lines - 1][i] != '1'
			&& cub->maps->my_map[cub->lines - 1][i] != ' ')
			return (print_error(cub, "Error ! \nCheck the last line !", map_check), 1);
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
			if (cub->maps->my_map[i][0] != '1'
				&& cub->maps->my_map[i][len - 1] != ' '
				&& cub->maps->my_map[i][len - 1] == '\t')
				return (print_error(cub, "Error ! \nCheck the walls !", map_check), 1);
			i++;
			len = ft_strlen(cub->maps->my_map[i]) - 1;
		}
	}
	return (0);
}

