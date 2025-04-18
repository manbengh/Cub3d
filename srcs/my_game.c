/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:13:01 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/16 14:13:03 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->keys->w = 1;
	if (keycode == XK_a)
		cub->keys->a = 1;
	if (keycode == XK_s)
		cub->keys->s = 1;
	if (keycode == XK_d)
		cub->keys->d = 1;
	if (keycode == XK_Left)
		cub->keys->left = 1;
	if (keycode == XK_Right)
		cub->keys->right = 1;
	if (keycode == XK_Escape)
		cub->keys->esc = 1;
	if (keycode == KEY_CTRL)
		cub->keys->ctrl = 1;
	return (1);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->keys->w = 0;
	if (keycode == XK_a)
		cub->keys->a = 0;
	if (keycode == XK_s)
		cub->keys->s = 0;
	if (keycode == XK_d)
		cub->keys->d = 0;
	if (keycode == XK_Left)
		cub->keys->left = 0;
	if (keycode == XK_Right)
		cub->keys->right = 0;
	if (keycode == XK_Escape)
		cub->keys->esc = 0;
	return (1);
}

void	my_game(t_cub *cub)
{
	init_game(cub);
	cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr,
			&cub->my_mlx->bpp, &cub->my_mlx->size_line, &cub->my_mlx->endian);
	mlx_put_image_to_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr,
		cub->my_mlx->img_ptr, 0, 0);
	mlx_hook(cub->my_mlx->win_ptr, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->my_mlx->win_ptr, 3, 1L << 1, &key_release, cub);
	mlx_hook(cub->my_mlx->win_ptr, DestroyNotify, StructureNotifyMask,
		&destroy_all, cub);
	mlx_hook(cub->my_mlx->win_ptr, 17, 0, &destroy_all, cub);
	mlx_loop_hook(cub->my_mlx->mlx_ptr, &moving, cub);
	mlx_loop(cub->my_mlx->mlx_ptr);
}
