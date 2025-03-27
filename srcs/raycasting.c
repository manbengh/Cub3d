#include "cube.h"

void    calculate_ray_dir(t_cub *cub, int x)
{
    double  camera_x = 2 * x / (double)SCREEN_W - 1;
    cub->ray->ray_dir.x = cub->my_mlx->dir.x + cub->my_mlx->plane.x * camera_x;
    cub->ray->ray_dir.y = cub->my_mlx->dir.y + cub->my_mlx->plane.y * camera_x;

    // Normalisation de ray_dir
    double length = sqrt(cub->ray->ray_dir.x * cub->ray->ray_dir.x + 
                         cub->ray->ray_dir.y * cub->ray->ray_dir.y);
    if (length != 0)  // Éviter la division par zéro
    {
        cub->ray->ray_dir.x /= length;
        cub->ray->ray_dir.y /= length;
    }

    // Debug pour voir si c'est bien normalisé
    printf("Normalized ray_dir: x = %f, y = %f\n", cub->ray->ray_dir.x, cub->ray->ray_dir.y);
}


void    calculate_step_dist(t_cub *cub, t_mlx *my_mlx, t_ray *ray)
{
    (void)cub;
    ray->map_x = (int)my_mlx->pos.x;
    ray->map_y = (int)my_mlx->pos.y;

    if (fabs(ray->ray_dir.y) < 1e-6)
        ray->delta_dist.y = 1e30;
    else
        ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
    if (ray->ray_dir.x == 0)
        ray->delta_dist.x = 1e30;
    else
        ray->delta_dist.x = fabs(1 / ray->ray_dir.x);

    // if (ray->ray_dir.y == 0)
    //     ray->delta_dist.y = 1e30;
    // else
    //     ray->delta_dist.y = fabs(1 / ray->ray_dir.y);

    if (ray->ray_dir.x < 0)
    {
        ray->step_x = -1;
        ray->side_dist.x = (my_mlx->pos.x - ray->map_x) * ray->delta_dist.x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist.x = (ray->map_x + 1.0 - my_mlx->pos.x) * ray->delta_dist.x;
    }

    if (ray->ray_dir.y < 0)
    {
        ray->step_y = -1;
        ray->side_dist.y = (my_mlx->pos.y - ray->map_y) * ray->delta_dist.y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist.y = (ray->map_y + 1.0 - my_mlx->pos.y) * ray->delta_dist.y;
    }
    printf("1 / ray_dir.x = %f\n", 1 / ray->ray_dir.x);
    printf("1 / ray_dir.y = %f\n", 1 / ray->ray_dir.y);
    printf("delta_dist.x = %f\n", ray->delta_dist.x);
    printf("delta_dist.y = %f\n", ray->delta_dist.y);

}

// void    perform_dda(t_cub *cub, t_ray *ray)
// {
//     int wall;

//     wall = 0;
//     while (wall == 0)
//     {
//         if (ray->side_dist.x < ray->side_dist.y)
//         {
//             ray->side_dist.x += ray->delta_dist.x;
//             ray->map_x += ray->step_x;
//             ray->side = 0;
//         }
//         else
//         {
//             ray->side_dist.y += ray->delta_dist.y;
//             ray->map_y += ray->step_y;
//             // printf("stepy ==> %i\n",ray->step_y);
//             ray->side = 1;
//         }
//         // printf("mapx ======= %i\n mapy ====== %i\n",ray->map_x ,ray->map_y);
//         if (cub->maps->my_map && cub->maps->my_map[ray->map_y][ray->map_x] > 0)
//         {
//             wall = 1;
//             break ;
//         }
//     }
// }

void    perform_dda(t_cub *cub, t_ray *ray)
{
    // int wall;

    // wall = 0;
    while (1)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map_y += ray->step_y;
            // printf("stepy ==> %i\n",ray->step_y);
            ray->side = 1;
        }
        // printf("mapx ======= %i\n mapy ====== %i\n",ray->map_x ,ray->map_y);
        if (cub->maps->my_map[ray->map_y][ray->map_x] == '1')
        {
            // wall = 1;
            break ;
        }
        // Test de distance correcte pour le mur
        if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - cub->my_mlx->pos.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;
    else
        ray->perp_wall_dist = (ray->map_y - cub->my_mlx->pos.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;

    printf("Wall distance: %f\n", ray->perp_wall_dist);

    }
}


// void get_wall_color(t_ray *ray)
// {
//     if (ray->side == 0)
//     {
//         if (ray->ray_dir.x < 0)
//             ray->color = 0xFF0000;
//         else if (ray->ray_dir.x > 0)
//         ray->color = 0x00FF00;    // Vert // Mur à est
//     }
//     else
//     {
//         if (ray->ray_dir.y < 0)
//             ray->color = 0x0000FF;    // Bleu // Mur au Nord
//         else
//             ray->color = 0xFFFFFF;    // Blanc // Mur au Sud
//     }
// }
void get_wall_color(t_ray *ray)
{
    if (ray->side == 0)  // Mur vertical
    {
        if (ray->ray_dir.x < 0)
            ray->color = 0xFF0000;  // Rouge, mur à l'ouest
        else
            ray->color = 0x00FF00;  // Vert, mur à l'est
    }
    else  // Mur horizontal
    {
        if (ray->ray_dir.y < 0)
            ray->color = 0x0000FF;  // Bleu, mur au nord
        else
            ray->color = 0xFFFFFF;  // Blanc, mur au sud
    }
}

void put_mlx_pixel(t_mlx *my_mlx, int x, int y, t_ray *ray)
{
    char *dest;

    if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
        return; 
    dest = my_mlx->img_data + (y * my_mlx->size_line + x * (my_mlx->bpp / 8));
    *(unsigned int*)dest = ray->color;
}

void    draw_vertical_line(int x, t_cub *cub, t_ray *ray)
{
    int y;

    if (ray->start_draw < 0)
        ray->start_draw = 0;
    if (ray->end_draw >= SCREEN_H)
        ray->end_draw = SCREEN_H - 1;
    y = ray->start_draw;
    while (y <= ray->end_draw)
    {
        put_mlx_pixel(cub->my_mlx, x, y, ray);
        y++;
    }
    ray->line_h = (int)(SCREEN_H / ray->perp_wall_dist);
    ray->start_draw = -ray->line_h / 2 + SCREEN_H / 2;
    ray->end_draw = ray->line_h / 2 + SCREEN_H / 2;
    printf("Wall Height: %d, Start: %d, End: %d\n", ray->line_h, ray->start_draw, ray->end_draw);

}


void init_mlx_vectors(t_mlx *my_mlx) {
    // Initialisation du vecteur de direction (dir) et du plan (plane)
    // Ces valeurs peuvent être définies en fonction de l'orientation de la caméra
    my_mlx->dir[0] = 1.0;  // Direction sur l'axe X (pour une vue de base)
    my_mlx->dir[1] = 0.0;  // Direction sur l'axe Y

    my_mlx->plane[0] = 0.0;  // Plan sur l'axe X (perpendiculaire à la direction)
    my_mlx->plane[1] = 0.66; // Plan sur l'axe Y (pour la perspective)

    // Vérification que les vecteurs sont initialisés
    printf("Direction vector: x = %d, y = %d\n", my_mlx->dir[0], my_mlx->dir[1]);
    printf("Plane vector: x = %f, y = %f\n", my_mlx->plane[0], my_mlx->plane[1]);
}



void    raycaster(t_cub *cub)
{
    int x;

    x = 0;
    // printf("ptr img = %p\n", cub->my_mlx->img_ptr);
    init_mlx_vectors(cub->my_mlx);
    printf("Plane: x = %f, y = %f\n", cub->my_mlx->plane.x, cub->my_mlx->plane.y);

    mlx_destroy_image(cub->my_mlx->mlx_ptr, cub->my_mlx->img_ptr);
    cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, SCREEN_W, SCREEN_H);
    cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr, &cub->my_mlx->bpp, &cub->my_mlx->size_line, &cub->my_mlx->endian);
    
    
    while (x < SCREEN_W)
    {
        calculate_ray_dir(cub, x);
        calculate_step_dist(cub, cub->my_mlx, cub->ray);
        perform_dda(cub, cub->ray);
        if (cub->ray->side == 0)
        cub->ray->perp_wall_dist = (cub->ray->side_dist.x - cub->ray->delta_dist.x);
        else
        cub->ray->perp_wall_dist = (cub->ray->side_dist.y - cub->ray->delta_dist.y);
        cub->ray->line_h = (int)(SCREEN_H / cub->ray->perp_wall_dist);
        cub->ray->start_draw = -cub->ray->line_h / 2 + SCREEN_H / 2;
        if (cub->ray->start_draw < 0)
        cub->ray->start_draw = 0;
        cub->ray->end_draw = cub->ray->line_h / 2 + SCREEN_H / 2;
        if (cub->ray->end_draw >= SCREEN_H)
        cub->ray->end_draw = SCREEN_H - 1;
        get_wall_color(cub->ray);
        draw_vertical_line(x, cub, cub->ray);
        x++;
    }
    mlx_put_image_to_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr, cub->my_mlx->img_ptr, 0, 0);
}
