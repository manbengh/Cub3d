#include "cube.h"

int my_window(t_cub *cub)
{
    
}

void my_game(t_cub *cub)
{
    int screen_w = 640;
    int screen_h = 480;

    cub->my_mlx->mlx_ptr = mlx_init();
    if (!cub->my_mlx->mlx_ptr)
    {
        print_error(cub, "Mlx fail", NULL);
        exit (1);
    }
    cub->my_mlx->win_ptr = mlx_new_window(cub->my_mlx->mlx_ptr, screen_w,
        screen_h, "Cub3D");
    if (!cub->my_mlx->win_ptr)
    {
        print_error(cub, "Window Fail", NULL);
        exit (1);
    }
    cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, screen_w, screen_h);
    cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr, &screen_w, &screen_h, &screen_w);
    mlx_loop_hook(cub->my_mlx->mlx_ptr, my_window, cub);
}
