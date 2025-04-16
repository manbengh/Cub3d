/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:12:48 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/16 14:12:49 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	move_forward(t_cub *cub, t_mlx *my_mlx)
{
	if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x
			+ my_mlx->dir.x * PLAYER_SPEED)] != '1')
		my_mlx->pos.x += my_mlx->dir.x * PLAYER_SPEED;
	if (cub->maps->my_map[(int)(my_mlx->pos.y + my_mlx->dir.y
			* PLAYER_SPEED)][(int)(my_mlx->pos.x)] != '1')
		my_mlx->pos.y += my_mlx->dir.y * PLAYER_SPEED;
}

void	move_backward(t_cub *cub, t_mlx *my_mlx)
{
	if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x
			- my_mlx->dir.x * PLAYER_SPEED)] != '1')
		my_mlx->pos.x -= my_mlx->dir.x * PLAYER_SPEED;
	if (cub->maps->my_map[(int)(my_mlx->pos.y - my_mlx->dir.y
			* PLAYER_SPEED)][(int)(my_mlx->pos.x)] != '1')
		my_mlx->pos.y -= my_mlx->dir.y * PLAYER_SPEED;
}

void	move_right(t_cub *cub, t_mlx *my_mlx)
{
	if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x
			- my_mlx->dir.y * PLAYER_SPEED)] != '1')
		my_mlx->pos.x -= my_mlx->dir.y * PLAYER_SPEED;
	if (cub->maps->my_map[(int)(my_mlx->pos.y + my_mlx->dir.x
			* PLAYER_SPEED)][(int)(my_mlx->pos.x)] != '1')
		my_mlx->pos.y += my_mlx->dir.x * PLAYER_SPEED;
}

void	move_left(t_cub *cub, t_mlx *my_mlx)
{
	if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x
			+ my_mlx->dir.y * PLAYER_SPEED)] != '1')
		my_mlx->pos.x += my_mlx->dir.y * PLAYER_SPEED;
	if (cub->maps->my_map[(int)(my_mlx->pos.y - my_mlx->dir.x
			* PLAYER_SPEED)][(int)(my_mlx->pos.x)] != '1')
		my_mlx->pos.y -= my_mlx->dir.x * PLAYER_SPEED;
}

int	moving(t_cub *cub)
{
	if (cub->keys->w == 1)
		move_forward(cub, cub->my_mlx);
	if (cub->keys->s == 1)
		move_backward(cub, cub->my_mlx);
	if (cub->keys->d == 1)
		move_right(cub, cub->my_mlx);
	if (cub->keys->a == 1)
		move_left(cub, cub->my_mlx);
	if (cub->keys->left == 1)
		cub->keys->rotate = -1;
	if (cub->keys->right == 1)
		cub->keys->rotate = 1;
	rotation(cub);
	if (cub->keys->esc == 1)
		destroy_all(cub);
	raycaster(cub);
	return (0);
}
