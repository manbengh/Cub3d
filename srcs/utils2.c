/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:41:15 by ahbey             #+#    #+#             */
/*   Updated: 2025/03/12 14:41:18 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_check_nums(char *str)
{
	int	i;
	int	num;
	char	**check_n;

	i = 0;
	num = 0;
	check_n = ft_split(str, ',');
	while (check_n[i])
	{
		num = ft_atoi(check_n[i]);
		if (num > 255 || num < 0)
		{
			free_tab(check_n);
			return (ft_printf("Error : Check params : number too big\n"), 1);
		}
		i++;
	}
	free_tab(check_n);
	return (0);
}
