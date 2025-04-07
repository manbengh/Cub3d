#include "cube.h"

t_mlx	*which_texture(t_cub *cub)
{
	if (cub->ray->side == 0)
	{
		if (cub->ray->ray_dir.x < 0)
			return (&cub->text[1]);
		return (&cub->text[0]);
	}
	else
	{
		if (cub->ray->ray_dir.y < 0)
			return (&cub->text[3]);
		return (&cub->text[2]);
	}
}

void	get_wall_color(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir.x < 0)
			ray->color = 0xFF0000;
		else
			ray->color = 0x00FF00;
	}
	else
	{
		if (ray->ray_dir.y < 0)
			ray->color = 0x0000FF;
		else
			ray->color = 0xFFFFFF;
	}
}

void	put_mlx_pixel(t_mlx *my_mlx, int x, int y, t_ray *ray)
{
	char	*dest;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dest = my_mlx->img_data + (y * my_mlx->size_line + x * (my_mlx->bpp / 8));
	*(unsigned int *)dest = ray->color;
}

void	draw_vertical_line(int x, t_cub *cub, t_ray *ray)
{
	int	y;

	if (ray->start_draw < 0)
		ray->start_draw = 0;
	if (ray->end_draw >= SCREEN_H)
		ray->end_draw = SCREEN_H - 1;
	y = ray->start_draw;
	while (y <= ray->end_draw)
	{
		put_mlx_pixel(cub->my_mlx, x, y, ray);
		y++;
	}
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

void	calc_text(t_cub *cub, t_ray *ray, t_mlx *text)
{
	if (ray->side == 0)
		cub->my_mlx->wall_x = cub->my_mlx->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		cub->my_mlx->wall_x = cub->my_mlx->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	cub->my_mlx->wall_x -= floor(cub->my_mlx->wall_x);
	cub->my_mlx->text_x = (int)(cub->my_mlx->wall_x * text->width);
	if (ray->side == 0 && ray->ray_dir.x < 0)
		cub->text->text_x = text->width - cub->text->text_x - 1;
	if (ray->side == 1 && ray->ray_dir.x > 0)
		cub->text->text_x = text->width - cub->text->text_x - 1;
}

int	get_my_text_color(t_ray *ray, t_mlx *text, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= text->width || y < 0 || y >= text->height)
		return (0);
	dst = text->img_data + (y * ray->line_h + x * (text->bpp / 8));
	return (*(unsigned int *)dst);
}

int	put_my_pxl(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_W || y >= SCREEN_H)
		return (ft_printf("Error pixel put\n"), 1);
	dst = cub->my_mlx->img_data + (y * cub->ray->line_h + x * (cub->my_mlx->bpp / 8));
	*(unsigned int *)dst = color;
	return (0);
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
	cub->text->step = (double)text->height / cub->ray->line_h;
	cub->text->text_pos = (cub->ray->start_draw - SCREEN_W / 2 + cub->ray->line_h / 2) * cub->text->step;
	cub->my_mlx->y = cub->ray->start_draw;
	while (cub->my_mlx->y <= cub->ray->end_draw)
	{
		if (cub->text->text_pos >= text->height)
			cub->text->text_y = (int)(cub->text->text_pos) % text->height;
		else
			cub->text->text_y = (int)(cub->text->text_pos);
		cub->text->text_pos += cub->text->step;
		cub->text->color = get_my_text_color(cub->ray, text, cub->text->text_x, cub->text->text_y);
		if (put_my_pxl(cub, x, cub->my_mlx->y, cub->text->color))
			return ;
		cub->my_mlx->y++;
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
		my_texture(cub, x);
		draw_vertical_line(x, cub, cub->ray);
		x++;
	}
	mlx_put_image_to_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr,
		cub->my_mlx->img_ptr, 0, 0);
}
