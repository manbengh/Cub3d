#include "cube.h"

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
