#include "cube.h"

void	get_pos_player(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->lines)
	{
		j = 0;
		while (j < ft_strlen(cub->maps->my_map[i]))
		{
			if (cub->maps->my_map[i][j] == 'N' || cub->maps->my_map[i][j] == 'S'
				|| cub->maps->my_map[i][j] == 'E'
				|| cub->maps->my_map[i][j] == 'W')
			{
				cub->maps->player_dir = cub->maps->my_map[i][j];
				cub->my_mlx->pos.x = j + 0.5;
				cub->my_mlx->pos.y = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	set_directions(t_cub *cub, char p)
{
	if (p == 'N')
	{
		cub->my_mlx->dir.x = 0;
		cub->my_mlx->dir.y = -1;
	}
	else if (p == 'S')
	{
		cub->my_mlx->dir.x = 0;
		cub->my_mlx->dir.y = 1;
	}
	else if (p == 'W')
	{
		cub->my_mlx->dir.x = -1;
		cub->my_mlx->dir.y = 0;
	}
	else if (p == 'E')
	{
		cub->my_mlx->dir.x = 1;
		cub->my_mlx->dir.y = 0;
	}
}

void	set_plane(t_cub *cub, char p)
{
	if (p == 'N')
	{
		cub->my_mlx->plane.x = 0.66;
		cub->my_mlx->plane.y = 0;
	}
	else if (p == 'S')
	{
		cub->my_mlx->plane.x = -0.66;
		cub->my_mlx->plane.y = 0;
	}
	else if (p == 'W')
	{
		cub->my_mlx->plane.x = 0;
		cub->my_mlx->plane.y = -0.66;
	}
	else if (p == 'E')
	{
		cub->my_mlx->plane.x = 0;
		cub->my_mlx->plane.y = 0.66;
	}
}

void	initi_floor_sky(t_cub *cub)
{
	cub->ray->my_sky[0] = 163; // Rouge
	cub->ray->my_sky[1] = 206; // Vert
	cub->ray->my_sky[2] = 220; // Bleu
	cub->ray->my_floor[0] = 211;
	cub->ray->my_floor[1] = 211;
	cub->ray->my_floor[2] = 211;


}

void	init_game(t_cub *cub)
{
	cub->my_mlx->mlx_ptr = mlx_init();
	if (!cub->my_mlx->mlx_ptr)
	{
		print_error(cub, "Mlx fail", NULL);
		exit(1);
	}
	cub->my_mlx->win_ptr = mlx_new_window(cub->my_mlx->mlx_ptr, SCREEN_W,
			SCREEN_H, "Cub3D");
	if (!cub->my_mlx->win_ptr)
	{
		print_error(cub, "Window Fail", NULL);
		exit(1);
	}
    initi_floor_sky(cub);
	get_pos_player(cub);
	set_directions(cub, cub->maps->player_dir);
	set_plane(cub, cub->maps->player_dir);
}
