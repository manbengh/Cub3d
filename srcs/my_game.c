#include "cube.h"

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
                cub->maps->pos.x = j + 0.5;
                cub->maps->pos.y = i + 0.5;
                return ;
            }
            j++;
        }
        i++;
    }
}

void    set_directions(t_cub *cub, char p)
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

void    set_plane(t_cub *cub, char p)
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
    printf("plane x = %f\nplane y %f\n", cub->my_mlx->plane.x, cub->my_mlx->plane.y);
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
    // printf("pos x == %i\npos y == %i\n", cub->maps->pos.x, cub->maps->pos.y);
    set_directions(cub, cub->maps->player_dir);
    set_plane(cub, cub->maps->player_dir);
}

int close_window(t_cub *cub)
{
    mlx_destroy_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr);
    print_error(cub, NULL, NULL);
    exit(0);
    return (0);
}

int key_press(int keycode, t_cub *cub)
{
    if (keycode == KEY_W)
        cub->keys->w = 1;
    if (keycode == KEY_A)
        cub->keys->a = 1;
    if (keycode == KEY_S)
        cub->keys->s = 1;
    if (keycode == KEY_D)
        cub->keys->d = 1;
    if (keycode == KEY_LEFT)
        cub->keys->left = 1;
    if (keycode == KEY_RIGHT)
        cub->keys->right = 1;
    if (keycode == KEY_ESC)
        cub->keys->esc = 1;
    return (1);
}

int key_release(int keycode, t_cub *cub)
{
    if (keycode == KEY_W)
        cub->keys->w = 0;
    if (keycode == KEY_A)
        cub->keys->a = 0;
    if (keycode == KEY_S)
        cub->keys->s = 0;
    if (keycode == KEY_D)
        cub->keys->d = 0;
    if (keycode == KEY_LEFT)
        cub->keys->left = 0;
    if (keycode == KEY_RIGHT)
        cub->keys->right = 0;
    if (keycode == KEY_ESC)
        cub->keys->esc = 0;
    return (1);
}

int moving(t_cub *cub)
{
    if (cub->keys->w == 1)
        move_forward(cub, );
}

void my_game(t_cub *cub)
{
    int screen_w = 640;
    int screen_h = 480;

    init_game(cub);
    // Création d'une image
    cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, screen_w, screen_h);
    if (!cub->my_mlx->img_ptr)
        print_error(cub, "Image Fail", NULL);
    cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr, &cub->my_mlx->bpp, &cub->my_mlx->size_line, &cub->my_mlx->endian);
    mlx_put_image_to_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr, cub->my_mlx->img_ptr, 0, 0);
    mlx_hook(cub->my_mlx->win_ptr, 2, 1L << 0, &key_press, cub);
    mlx_hook(cub->my_mlx->win_ptr, 3, 1L << 1, &key_release, cub);
    mlx_loop_hook(cub->my_mlx->mlx_ptr, &moving, cub);
    mlx_hook(cub->my_mlx->win_ptr, 17, 0, close_window, cub);
    mlx_loop(cub->my_mlx->mlx_ptr);
}


//set directions