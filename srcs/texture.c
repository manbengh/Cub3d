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

int	make_image(t_cub *cub, t_text *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(cub->my_mlx->mlx_ptr, path,
			&texture->win, &texture->size_h);
	if (texture->img == NULL)
		return (ft_printf("Error: texture\n"), 1);
	texture->img_addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_h, &texture->endian);
	if(texture->img_addr == NULL)
		return (ft_printf("Error: texture\n"), 1);
	return(0);
}

int	init_texture(t_cub *cub)
{
	if (make_image(cub, &cub->text[0], cub->maps->no[1]))
	if (make_image(cub, &cub->text[0], cub->maps->no[1]))
}

void	calc_text(t_ray *ray, t_map *maps, t_mlx *text)
{
	if (ray->side == 0)
}

void	my_texture(t_cub *cub)
{
	t_mlx	*text;

	text = which_texture(cub);
	if (cub->ray->start_draw < 0)
		cub->ray->start_draw = 0;
	if (cub->ray->end_draw >= SCREEN_H)
		cub->ray->end_draw = SCREEN_H - 1;
	calc_text(cub->ray, cub->maps, text);
}
