/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:00 by ahbey             #+#    #+#             */
/*   Updated: 2025/03/12 14:38:00 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
                cub->maps->start_pos.x = j;
                cub->maps->start_pos.y = i;
                return ;
            }
            j++;
        }
        i++;
    }
}

// void    init_pers(t_cub *cub)
// {
//     cub.
// }

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
    // init_pers(cub);
}

// int my_window(t_cub *cub)
// {
//     int x;
//     int y;

//     x = 0;
//     y = 0;
//     if (cub->my_mlx->win_ptr)
//     {
//         while (x < cub->lines)
//         {
//             printf("x -----> %i\n", x);
//             y = 0;
//             while (y < ft_strlen(cub->maps->my_map[x]))
//             {
//                 mlx_put_image_to_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr, "../thisisfine.xpm", y
//                     * 64, x * 64);
//                 y++;
//             }
//             x++;
//         }
//     }
//     return  (0);
// }

// int key_events(int key_code, t_cub *cub)
// {
//     int x;
//     int y;

//     x = cub->maps->start_pos.x;
//     y = cub->maps->start_pos.y;
//     if (key_code == 119)
//         x--;
//     else if (key_code == 115)
//         x++;
//     else if (key_code == 100)
//         y++;
//     else if (key_code == 97)
//         y--;
//     return (0);
// }

// void my_game(t_cub *cub)
// {
//     int screen_w = SCREEN_W;
//     int screen_h = SCREEN_H;
    
//     init_game(cub);
//     cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, SCREEN_W, SCREEN_H);
//     cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr, &screen_w, &screen_h, &screen_w);
//     mlx_loop_hook(cub->my_mlx->mlx_ptr, my_window, cub);
//     // mlx_hook(cub->my_mlx->win_ptr, 2, 1L << 0, key_events,cub);
//     // mlx_loop(cub->my_mlx->mlx_ptr);
// }



int close_window(t_cub *cub)
{
    mlx_destroy_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr);
    print_error(cub, NULL, NULL);
    exit(0);
    return (0);
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
    mlx_hook(cub->my_mlx->win_ptr, 17, 0, close_window, cub);
    mlx_loop(cub->my_mlx->mlx_ptr);
}


//set directions