#include "cube.h"

// void    init_val(t_cub *cub)
// {
    
// }

void my_game(t_cub *cub)
{
    int screen_w = 640;
    int screen_h = 480;

    // init_val(cub);
    printf("ICIIIII\n");
    cub->mlx_ptr = mlx_init();
    if (!cub->mlx_ptr)
    {
        print_error(cub, "Mlx fail", NULL);
        exit (1);
    }
    cub->win_ptr = mlx_new_window(cub->mlx_ptr, screen_w,
        screen_h, "Cub3D");
    if (!cub->win_ptr)
    {
        print_error(cub, "Window Fail", NULL);
        exit (1);
    }
    cub->img_ptr = mlx_new_image(cub->mlx_ptr, screen_w, screen_h);
    cub->img_data = mlx_get_data_addr(cub->img_ptr, &screen_w, &screen_h, &screen_w);
}
