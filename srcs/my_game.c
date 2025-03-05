#include "cube.h"

// int my_window(t_cub *cub)
// {
    
// }

void    get_pos_player(t_cub *cub)
{
    int i;
    int j;

    i = 0;
    while (i < cub->lines)
    {
        j = 0;
        while (j < ft_strlen(cub->maps->my_map[i]))
        {
            if (cub->maps->my_map[i][j] == cub->maps->player_dir)
            {
                cub->maps->start_pos.x = j;
                cub->maps->start_pos.y = i;
                return ;
            }
            j++;
        }
        i++;
    }
}

void    init_game(t_cub *cub)
{
    cub->my_mlx->mlx_ptr = mlx_init();
    if (!cub->my_mlx->mlx_ptr)
    {
        print_error(cub, "Mlx fail", NULL);
        exit (1);
    }
    cub->my_mlx->win_ptr = mlx_new_window(cub->my_mlx->mlx_ptr, SCREEN_W,
        SCREEN_H, "Cub3D");
    if (!cub->my_mlx->win_ptr)
    {
        print_error(cub, "Window Fail", NULL);
        exit (1);
    }
    get_pos_player(cub);
    printf("pos x == %i\npos y == %i\n", cub->maps->start_pos.x, cub->maps->start_pos.y);
}
    
void my_game(t_cub *cub)
{
    int screen_w = SCREEN_W;
    int screen_h = SCREEN_H;

    init_game(cub);
    cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, SCREEN_W, SCREEN_H);
    cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr, &screen_w, &screen_h, &screen_w);
    // mlx_loop_hook(cub->my_mlx->mlx_ptr, my_window, cub);
}
