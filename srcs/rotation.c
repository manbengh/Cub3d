/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:15:10 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/20 19:20:54 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	to_the_right(t_mlx *my_mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = my_mlx->dir.x;
	old_plane_x = my_mlx->plane.x;
	my_mlx->dir.x = my_mlx->dir.x * cos(ROTATION_SPEED) - my_mlx->dir.y
		* sin(ROTATION_SPEED);
	my_mlx->dir.y = old_dir_x * sin(ROTATION_SPEED) + my_mlx->dir.y
		* cos(ROTATION_SPEED);
	my_mlx->plane.x = my_mlx->plane.x * cos(ROTATION_SPEED) - my_mlx->plane.y
		* sin(ROTATION_SPEED);
	my_mlx->plane.y = old_plane_x * sin(ROTATION_SPEED) + my_mlx->plane.y
		* cos(ROTATION_SPEED);
}

void	to_the_left(t_mlx *my_mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = my_mlx->dir.x;
	old_plane_x = my_mlx->plane.x;
	my_mlx->dir.x = my_mlx->dir.x * cos(-ROTATION_SPEED) - my_mlx->dir.y
		* sin(-ROTATION_SPEED);
	my_mlx->dir.y = old_dir_x * sin(-ROTATION_SPEED) + my_mlx->dir.y
		* cos(-ROTATION_SPEED);
	my_mlx->plane.x = my_mlx->plane.x * cos(-ROTATION_SPEED) - my_mlx->plane.y
		* sin(-ROTATION_SPEED);
	my_mlx->plane.y = old_plane_x * sin(-ROTATION_SPEED) + my_mlx->plane.y
		* cos(-ROTATION_SPEED);
}

void	rotation(t_cub *cub)
{
	if (cub->keys->rotate == -1)
		to_the_left(cub->my_mlx);
	else if (cub->keys->rotate == 1)
		to_the_right(cub->my_mlx);
	cub->keys->rotate = 0;
}
