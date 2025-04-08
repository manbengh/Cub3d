/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:02 by ahbey             #+#    #+#             */
/*   Updated: 2025/03/26 15:02:20 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int close_window(t_cub *cub)
{
    destroy_all(cub);
    return (0);
}

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

int destroy_all(t_cub *cub)
{
	// printf("AAAAAAAAAAAAAAAAAA %p\n", cub->my_mlx->img_ptr);
	mlx_destroy_image(cub->my_mlx->mlx_ptr, cub->my_mlx->img_ptr);
    if (cub->my_mlx->win_ptr)
        mlx_destroy_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr);
    if (cub->my_mlx->mlx_ptr)
    {
        mlx_destroy_display(cub->my_mlx->mlx_ptr);
        free(cub->my_mlx->mlx_ptr);
    }
    print_error(cub, NULL, NULL);
    return (0);
}
