#include "cube.h"

t_mlx	*which_texture(t_cub *cub)
{
	if (cub->ray->side == 0)
	{
		if (cub->ray->ray_dir.x < 0)
			return (&cub->text[1]); // Rouge // Mur à ouest
		return (&cub->text[0]);     // Vert // Mur à est
	}
	else
	{
		if (cub->ray->ray_dir.y < 0)
			return (&cub->text[3]); // Bleu // Mur au Nord
		return (&cub->text[2]);     // Blanc // Mur au Sud
	}
}

int	get_my_text_color(t_mlx *text, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= text->width || y < 0 || y >= text->height)
		return (0);
	dst = text->img_data + (y * text->size_line + x * (text->bpp / 8));
	return (*(unsigned int *)dst);
}

void	calc_text(t_cub *cub, t_ray *ray, t_mlx *text)
{
	if (ray->side == 0)
		cub->my_mlx->wall_x = cub->my_mlx->pos.y + ray->perp_wall_dist
			* ray->ray_dir.y;
	else
		cub->my_mlx->wall_x = cub->my_mlx->pos.x + ray->perp_wall_dist
			* ray->ray_dir.x;
	cub->my_mlx->wall_x -= floor(cub->my_mlx->wall_x);
	text->text_x = (int)(cub->my_mlx->wall_x * (double)text->width);
	// Correction ici : on regarde bien l’axe Y si side == 1
	if (ray->side == 0 && ray->ray_dir.x < 0)
		text->text_x = text->width - text->text_x - 1;
	if (ray->side == 1 && ray->ray_dir.y > 0)
		text->text_x = text->width - text->text_x - 1;
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

int	make_img(t_cub *cub, t_mlx *text, char *path)
{
	path[ft_strlen(path) - 1] = '\0';
	text->img_ptr = mlx_xpm_file_to_image(cub->my_mlx->mlx_ptr, path,
			&text->width, &text->height);
	if (text->img_ptr == NULL)
		return (ft_printf("Error textures 1\n"), 1);
	text->img_data = mlx_get_data_addr(text->img_ptr, &text->bpp,
			&text->size_line, &text->endian);
	if (!text->img_data)
		return (ft_printf("Error textures\n"), 1);
	return (0);
}

int	init_text(t_cub *cub)
{
	// cub->text[0] = "textures/prout.xpm";
	if (make_img(cub, &cub->text[0], cub->maps->no[1]))
		return (1);
	if (make_img(cub, &cub->text[1], cub->maps->so[1]))
		return (2);
	if (make_img(cub, &cub->text[2], cub->maps->we[1]))
		return (3);
	if (make_img(cub, &cub->text[3], cub->maps->ea[1]))
		return (4);
	return (0);
}
