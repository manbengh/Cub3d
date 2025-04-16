/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:38 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/16 16:13:27 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	make_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	put_pixel_floor_sky(t_mlx *my_mlx, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dest = my_mlx->img_data + (y * my_mlx->size_line + x * (my_mlx->bpp / 8));
	*(unsigned int *)dest = color;
}

void	make_floor_sky(t_cub *cub)
{
	int	x;
	int	y;
	int	my_floor;
	int	my_sky;

	my_sky = make_rgb(cub->ray->my_sky[0], cub->ray->my_sky[1],
			cub->ray->my_sky[2]);
	my_floor = make_rgb(cub->ray->my_floor[0], cub->ray->my_floor[1],
			cub->ray->my_floor[2]);
	y = 0;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			if (y < SCREEN_H / 2)
				put_pixel_floor_sky(cub->my_mlx, x, y, my_sky);
			else
				put_pixel_floor_sky(cub->my_mlx, x, y, my_floor);
			x++;
		}
		y++;
	}
}

void	my_texture(t_cub *cub, int x)
{
	t_mlx	*text;

	text = which_texture(cub);
	if (cub->ray->start_draw < 0)
		cub->ray->start_draw = 0;
	if (cub->ray->end_draw >= SCREEN_H)
		cub->ray->end_draw = SCREEN_H - 1;
	calc_text(cub, cub->ray, text);
	text->step = (double)text->height / (double)cub->ray->line_h;
	text->text_pos = (cub->ray->start_draw - SCREEN_H / 2.0 + cub->ray->line_h
			/ 2.0) * text->step;
	cub->my_mlx->y = cub->ray->start_draw;
	while (cub->my_mlx->y <= cub->ray->end_draw)
	{
		text->text_y = (int)text->text_pos;
		if (text->text_y < 0)
			text->text_y = 0;
		if (text->text_y >= text->height)
			text->text_y = text->height - 1;
		text->text_pos += text->step;
		cub->ray->color = get_my_text_color(text, text->text_x, text->text_y);
		if (put_mlx_pixel(cub->my_mlx, x, cub->my_mlx->y, cub->ray))
			return ;
		cub->my_mlx->y++;
	}
}

int	destroy_all(t_cub *cub)
{
	free_my_text(cub);
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
