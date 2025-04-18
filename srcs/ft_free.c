/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:02 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/18 16:33:40 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// void	ft_secure(char *str)
// {
// 	if (str == NULL)
// 		destroy_all()
// }

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

void	maps_free(t_map *maps)
{
	free_tab(maps->c);
	free_tab(maps->f);
	free_tab(maps->ea);
	free_tab(maps->we);
	free_tab(maps->no);
	free_tab(maps->so);
	free_tab(maps->my_map);
	free(maps);
}

void	print_error(t_cub *cub, char *str, char **map_check)
{
	if (str)
		printf("%s\n", str);
	free_tab(map_check);
	maps_free(cub->maps);
	free(cub->my_mlx);
	free(cub->keys);
	free(cub->ray);
	exit(1);
}

void	free_my_text(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->text[i].img_ptr)
			mlx_destroy_image(cub->my_mlx->mlx_ptr, cub->text[i].img_ptr);
		i++;
	}
}
