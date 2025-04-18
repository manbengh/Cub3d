/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:24 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/16 16:24:09 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	compare_dir_c_f(t_map *maps, char *stock_l)
{
	if (ft_strncmp("WE ", stock_l, 3) == 0 && maps->we == NULL)
	{
		maps->we = ft_split(stock_l, ' ');
		if (maps->we == NULL)
			return (0);
		return (1);
	}
	else if (ft_strncmp("C ", stock_l, 2) == 0 && maps->c == NULL)
	{
		maps->c = split_first_keyword(stock_l);
		if (maps->c == NULL)
			return (0);
		return (1);
	}
	else if (ft_strncmp("F ", stock_l, 2) == 0 && maps->f == NULL)
	{
		maps->f = split_first_keyword(stock_l);
		if (maps->f == NULL)
			return (0);
		return (1);
	}
	return (0);
}

int	compare_dir(t_map *maps, char *stock_l)
{
	if (ft_strncmp("NO ", stock_l, 3) == 0 && maps->no == NULL)
	{
		maps->no = ft_split(stock_l, ' ');
		if (maps->no == NULL)
			return (0);
		return (1);
	}
	else if (ft_strncmp("SO ", stock_l, 3) == 0 && maps->so == NULL)
	{
		maps->so = ft_split(stock_l, ' ');
		if (maps->so == NULL)
			return (0);
		return (1);
	}
	else if (ft_strncmp("EA ", stock_l, 3) == 0 && maps->ea == NULL)
	{
		maps->ea = ft_split(stock_l, ' ');
		if (maps->ea == NULL)
			return (0);
		return (1);
	}
	return (compare_dir_c_f(maps, stock_l));
}

char	*clean_color_string(char *str)
{
	char	*cleaned;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cleaned = malloc(ft_strlen(str) + 1);
	if (!cleaned)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			continue ;
		}
		cleaned[j++] = str[i++];
	}
	free(str);
	cleaned[j] = '\0';
	return (cleaned);
}

int	check_params_f(t_map *maps)
{
	int	i;

	i = 0;
	if (maps->f)
	{
		maps->f[1] = clean_color_string(maps->f[1]);
		if (maps->f[1] == NULL)
			return (1);
		while (maps->f[1][i])
		{
			if (ft_isalpha(maps->f[1][i]))
				return (printf("Error !\nCheck params : no letters \n"), 1);
			if (maps->f[1][i] == ',' && (ft_isdigit(maps->f[1][i + 1]) == 0
					|| ft_isdigit(maps->f[1][i - 1]) == 0))
				return (printf("Error !\nCheck params : incorrect number\n"),
					1);
			if (ft_count_num(maps->f[1]) < 3 || ft_count_num(maps->f[1]) > 9)
				return (printf("Error !\nCheck params : incorrect number\n"),
					1);
			if (ft_check_nums(maps->f[1]) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}

int	check_params_c(t_map *maps)
{
	int	i;

	i = 0;
	if (maps->c)
	{
		maps->c[1] = clean_color_string(maps->c[1]);
		if (maps->c[1] == NULL)
			return (1);
		while (maps->c[1][i])
		{
			if (ft_isalpha(maps->c[1][i]))
				return (printf("Error !\nCheck params : no letters \n"), 1);
			if (maps->c[1][i] == ',' && (!ft_isdigit(maps->c[1][i + 1])
				|| !ft_isdigit(maps->c[1][i - 1])))
				return (printf("Error !\nCheck params : incorrect number\n"),
					1);
			if (ft_count_num(maps->c[1]) < 3 || ft_count_num(maps->c[1]) > 9)
				return (printf("Error !\nCheck params : incorrect number\n"),
					1);
			if (ft_check_nums(maps->c[1]) == 1)
				return (1);
			i++;
		}
	}
	return (check_params_f(maps));
}
