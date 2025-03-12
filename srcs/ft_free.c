/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:02 by ahbey             #+#    #+#             */
/*   Updated: 2025/03/12 14:34:09 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_struct(t_cub *cub)
{
	if (cub->maps->c)
		free_tab(cub->maps->c);
	if (cub->maps->f)
		free_tab(cub->maps->f);
	free(cub->maps);
}

void	print_error(t_cub *cub, char *str, char **map_check)
{
	if (str)
		printf("%s\n", str);
	free_tab(map_check);
	free_tab(cub->maps->c);
	free_tab(cub->maps->f);
	free_tab(cub->maps->ea);
	free_tab(cub->maps->we);
	free_tab(cub->maps->no);
	free_tab(cub->maps->so);
	free_tab(cub->maps->my_map);
	free(cub->maps);
	exit(1);
}
