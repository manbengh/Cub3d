#include "cube.h"

void	get_wall_color(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir.x < 0)
			ray->color = 0xFF0000;// Rouge // Mur à ouest
		else
			ray->color = 0x00FF00; // Vert // Mur à est
	}
	else
	{
		if (ray->ray_dir.y < 0) 
			ray->color = 0x0000FF; // Bleu // Mur au Nord
		else
			ray->color = 0xFFFFFF; // Blanc // Mur au Sud
	}
}

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
		ray->perp_wall_dist = (ray->side_dist.x
				- ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y
				- ray->delta_dist.y);
	ray->line_h = (int)(SCREEN_H / ray->perp_wall_dist);
	ray->start_draw = -ray->line_h / 2 + SCREEN_H / 2;
	if (ray->start_draw < 0)
		ray->start_draw = 0;
	ray->end_draw = ray->line_h / 2 + SCREEN_H / 2;
	if (ray->end_draw >= SCREEN_H)
		ray->end_draw = SCREEN_H - 1;
}

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
	int x;
	int y;
	int	my_floor;
	int	my_sky;

	my_sky = make_rgb(cub->ray->my_sky[0], cub->ray->my_sky[1], cub->ray->my_sky[2]);
	my_floor = make_rgb(cub->ray->my_floor[0], cub->ray->my_floor[1], cub->ray->my_floor[2]);
	y = 0;
	while(y < SCREEN_H)
	{
		x = 0;
		while(x < SCREEN_W)
		{
			if(y < SCREEN_H / 2)
				put_pixel_floor_sky(cub->my_mlx, x, y, my_sky);
			else
				put_pixel_floor_sky(cub->my_mlx, x, y, my_floor);
			x++;
		}
		y++;
	}

}

void	raycaster(t_cub *cub)
{
	int	x;

	x = 0;
	mlx_destroy_image(cub->my_mlx->mlx_ptr, cub->my_mlx->img_ptr);
	cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr,
			SCREEN_W, SCREEN_H);
	cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr,
			&cub->my_mlx->bpp, &cub->my_mlx->size_line,
			&cub->my_mlx->endian);
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
