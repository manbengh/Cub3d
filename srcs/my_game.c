#include "cube.h"

void get_pos_player(t_cub *cub)
{
    int i;
    int j;
    
    i = 0;
    while (i < cub->lines)
    {
        j = 0;
        while (j < ft_strlen(cub->maps->my_map[i]))
        {
            if (cub->maps->my_map[i][j] == 'N' || cub->maps->my_map[i][j] == 'S' ||
                cub->maps->my_map[i][j] == 'E' || cub->maps->my_map[i][j] == 'W')
            {
                cub->maps->player_dir = cub->maps->my_map[i][j];  // Stocker la direction
                cub->my_mlx->pos.x = j + 0.5;
                cub->my_mlx->pos.y = i + 0.5;

                printf("Found Player at: x = %f, y = %f\n", cub->my_mlx->pos.x, cub->my_mlx->pos.y);
                printf("Player Direction: %c\n", cub->maps->player_dir);
                return;
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
    // printf("plane x = %f\nplane y %f\n", cub->my_mlx->plane.x, cub->my_mlx->plane.y);
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
    if (keycode == XK_w)
    {
        // printf("W\n");
        cub->keys->w = 1;
    }
    if (keycode == XK_a)
        cub->keys->a = 1;
    if (keycode == XK_s)
        cub->keys->s = 1;
    if (keycode == XK_d)
        cub->keys->d = 1;
    if (keycode == XK_Left)
        cub->keys->left = 1;
    if (keycode == XK_Right)
        cub->keys->right = 1;
    if (keycode == XK_Escape)
        ft_free_escape(cub);
    return (1);
}

int key_release(int keycode, t_cub *cub)
{
    if (keycode == XK_w)
        cub->keys->w = 0;
    if (keycode == XK_a)
        cub->keys->a = 0;
    if (keycode == XK_s)
        cub->keys->s = 0;
    if (keycode == XK_d)
        cub->keys->d = 0;
    if (keycode == XK_Left)
        cub->keys->left = 0;
    if (keycode == XK_Right)
        cub->keys->right = 0;
    if (keycode == XK_Escape)
        cub->keys->esc = 0;
    return (1);
}

void    move_forward(t_cub *cub, t_mlx *my_mlx)
{
    if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x)] == '1')
        return ;
    if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x + my_mlx->dir.x * PLAYER_SPEED)] != '1')
        my_mlx->pos.x += my_mlx->dir.x * PLAYER_SPEED;
    if (cub->maps->my_map[(int)(my_mlx->pos.y + my_mlx->dir.y * PLAYER_SPEED)][(int)(my_mlx->pos.x)] != '1')
        my_mlx->pos.y += my_mlx->dir.y * PLAYER_SPEED;
}

void    move_backward(t_cub *cub, t_mlx *my_mlx)
{
    if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x)] == '1')
        return ;
    if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x - my_mlx->dir.x * PLAYER_SPEED)] != '1')
        my_mlx->pos.x -= my_mlx->dir.x * PLAYER_SPEED;
    if (cub->maps->my_map[(int)(my_mlx->pos.y - my_mlx->dir.y * PLAYER_SPEED)][(int)(my_mlx->pos.x)] != '1')
        my_mlx->pos.y -= my_mlx->dir.y * PLAYER_SPEED;
}

void    move_right(t_cub *cub, t_mlx *my_mlx)
{
    if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x)] == '1')
        return ;
    if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x - my_mlx->dir.y * PLAYER_SPEED)] != '1')
        my_mlx->pos.x -= my_mlx->dir.y * PLAYER_SPEED;
    if (cub->maps->my_map[(int)(my_mlx->pos.y + my_mlx->dir.x * PLAYER_SPEED)][(int)(my_mlx->pos.x)] != '1')
        my_mlx->pos.y += my_mlx->dir.x * PLAYER_SPEED;
}

void    move_left(t_cub *cub, t_mlx *my_mlx)
{
    if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x)] == '1')
        return ;
    if (cub->maps->my_map[(int)(my_mlx->pos.y)][(int)(my_mlx->pos.x + my_mlx->dir.y * PLAYER_SPEED)] != '1')
        my_mlx->pos.x += my_mlx->dir.y * PLAYER_SPEED;
    if (cub->maps->my_map[(int)(my_mlx->pos.y - my_mlx->dir.x * PLAYER_SPEED)][(int)(my_mlx->pos.x)] != '1')
        my_mlx->pos.y -= my_mlx->dir.x * PLAYER_SPEED;
}

void    to_the_right(t_mlx *my_mlx)
{
    double  old_dir_x;
    double  old_plane_x;

    old_dir_x = my_mlx->dir.x;
    old_plane_x = my_mlx->plane.x;
    my_mlx->dir.x = my_mlx->dir.x * cos(ROTATION_SPEED) - my_mlx->dir.y * sin(ROTATION_SPEED);
    my_mlx->dir.y = old_dir_x * sin(ROTATION_SPEED) + my_mlx->dir.y * cos(ROTATION_SPEED);
    my_mlx->plane.x = my_mlx->plane.x * cos(ROTATION_SPEED) - my_mlx->plane.y * sin(ROTATION_SPEED);
    my_mlx->plane.y = old_plane_x * sin(ROTATION_SPEED) + my_mlx->plane.y * cos(ROTATION_SPEED);
}

void    to_the_left(t_mlx *my_mlx)
{
    double  old_dir_x;
    double  old_plane_x;

    old_dir_x = my_mlx->dir.x;
    old_plane_x = my_mlx->plane.x;
    my_mlx->dir.x = my_mlx->dir.x * cos(-ROTATION_SPEED) - my_mlx->dir.y * sin(-ROTATION_SPEED);
    my_mlx->dir.y = old_dir_x * sin(-ROTATION_SPEED) + my_mlx->dir.y * cos(-ROTATION_SPEED);
    my_mlx->plane.x = my_mlx->plane.x * cos(-ROTATION_SPEED) - my_mlx->plane.y * sin(-ROTATION_SPEED);
    my_mlx->plane.y = old_plane_x * sin(-ROTATION_SPEED) + my_mlx->plane.y * cos(-ROTATION_SPEED);
}

void    rotation(t_cub *cub)
{
    if (cub->maps->my_map[(int)(cub->my_mlx->pos.y)][(int)(cub->my_mlx->pos.x)] == 1)
        return ;
    if (cub->keys->rotate == 1)
        to_the_left(cub->my_mlx);
    else if (cub->keys->rotate == -1)
        to_the_right(cub->my_mlx);
}

int moving(t_cub *cub)
{
    if (cub->keys->w == 1)
        move_forward(cub, cub->my_mlx);
    if (cub->keys->s == 1)
        move_backward(cub, cub->my_mlx);
    if (cub->keys->d == 1)
        move_right(cub, cub->my_mlx);
    if (cub->keys->a == 1)
        move_left(cub, cub->my_mlx);
    if (cub->keys->left == 1)
    {
        cub->keys->rotate = -1;
        rotation(cub);
    }
    if (cub->keys->right == 1)
    {
        cub->keys->rotate = 1;
        rotation(cub);
    }
    raycaster(cub);
    return(0);
}

void my_game(t_cub *cub)
{

    init_game(cub);
    // Creation d'une image
    cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, SCREEN_W, SCREEN_H);
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
