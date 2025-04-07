#include "cube.h"

t_mlx	*which_texture(t_cub *cub)
{
	if (cub->ray->side == 0)
	{
		if (cub->ray->ray_dir.x < 0)
			return (&cub->text[1]);// Rouge // Mur à ouest
		return (&cub->text[0]);// Vert // Mur à est
	}
	else
	{
		if (cub->ray->ray_dir.y < 0)
			return (&cub->text[3]);// Bleu // Mur au Nord
		return (&cub->text[2]); // Blanc // Mur au Sud
	}
}
void    calc_text(t_ray *ray, t_map *maps, t_mlx *text)
{
    if(ray->side == 0)
        
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

