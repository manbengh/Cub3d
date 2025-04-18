/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:13:14 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/16 14:29:53 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// Rouge // Mur à ouest
// Vert // Mur à est
// Bleu // Mur au Nord
// Blanc // Mur au Sud
int	put_mlx_pixel(t_mlx *my_mlx, int x, int y, t_ray *ray)
{
	char	*dest;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return (printf("Pxl Error !\n"), 1);
	dest = my_mlx->img_data + (y * my_mlx->size_line + x * (my_mlx->bpp / 8));
	*(unsigned int *)dest = ray->color;
	return (0);
}

void	draw_vertical_line(int x, t_cub *cub, t_ray *ray)
{
	int	y;

	if (ray->start_draw < 0)
		ray->start_draw = 0;
	if (ray->end_draw >= SCREEN_H)
		ray->end_draw = SCREEN_H - 1;
	y = ray->start_draw;
	my_texture(cub, x);
	ray->line_h = (int)(SCREEN_H / ray->perp_wall_dist);
	ray->start_draw = -ray->line_h / 2 + SCREEN_H / 2;
	ray->end_draw = ray->line_h / 2 + SCREEN_H / 2;
}

void	get_start_end_draw(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
	ray->line_h = (int)(SCREEN_H / ray->perp_wall_dist);
	ray->start_draw = -ray->line_h / 2 + SCREEN_H / 2;
	if (ray->start_draw < 0)
		ray->start_draw = 0;
	ray->end_draw = ray->line_h / 2 + SCREEN_H / 2;
	if (ray->end_draw >= SCREEN_H)
		ray->end_draw = SCREEN_H - 1;
}

void	raycaster(t_cub *cub)
{
	int	x;

	x = 0;
	mlx_destroy_image(cub->my_mlx->mlx_ptr, cub->my_mlx->img_ptr);
	cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, SCREEN_W,
			SCREEN_H);
	cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr,
			&cub->my_mlx->bpp, &cub->my_mlx->size_line, &cub->my_mlx->endian);
	make_floor_sky(cub);
	while (x < SCREEN_W)
	{
		calculate_ray_dir(cub, x);
		calculate_step_dist(cub->my_mlx, cub->ray);
		perform_dda(cub, cub->ray);
		get_start_end_draw(cub->ray);
		draw_vertical_line(x, cub, cub->ray);
		x++;
	}
	mlx_put_image_to_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr,
		cub->my_mlx->img_ptr, 0, 0);
}
