#include "cube.h"

int close_window(t_cub *cub)
{
    mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
    exit(0);
    return (0);
}

void init_window(t_cub *cub)
{
    int screen_w = 640;
    int screen_h = 480;

    cub->mlx_ptr = mlx_init();
    if (!cub->mlx_ptr)
        print_error(cub, "Mlx fail", NULL);
    cub->win_ptr = mlx_new_window(cub->mlx_ptr, screen_w, screen_h, "Cub3D");
    if (!cub->win_ptr)
        print_error(cub, "Window Fail", NULL);
    // Création d'une image
    cub->img_ptr = mlx_new_image(cub->mlx_ptr, screen_w, screen_h);
    if (!cub->img_ptr)
        print_error(cub, "Image Fail", NULL);
    cub->img_data = mlx_get_data_addr(cub->img_ptr, &cub->bpp, &cub->size_line, &cub->endian);
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
    mlx_hook(cub->win_ptr, 17, 0, close_window, cub);
    mlx_loop(cub->mlx_ptr);
}

int touch_key(int keycode, t_cub *cub)
{
    if (keycode == 65307)
		mlx_loop_end(cub->mlx_ptr);
    my_game(cub);
    return(0);
}

void my_game(t_cub *cub)
{
    init_window(cub);
    
}