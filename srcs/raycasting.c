#include "cube.h"

void print_trig_circle(double angle) {
    printf("\n Cercle Trigonométrique (Angle = %.2f°)\n", angle);
    printf("      N (0°)\n");
    printf("       |\n");
    printf("       |\n");
    printf("  O (270°)---- E (90°)\n");
    printf("       |\n");
    printf("       |\n");
    printf("      S (180°)\n\n");
    
    printf(" Position de l'angle %.2f° :\n", angle);
    
    // Quadrants
    if (angle >= 0 && angle < 90) 
        printf(" - Dans le 1er quadrant (Nord-Est)\n");
    else if (angle >= 90 && angle < 180)
        printf(" - Dans le 2ème quadrant (Sud-Est)\n");
    else if (angle >= 180 && angle < 270)
        printf(" - Dans le 3ème quadrant (Sud-Ouest)\n");
    else
        printf(" - Dans le 4ème quadrant (Nord-Ouest)\n");
}

void calculate_ray_dir(t_cub *cub, int x)
{
    // Calcul de la position x sur le plan de la caméra
    double camera_x = 2 * x / (double)SCREEN_W - 1;
    
    // Calcul de la direction du rayon
    cub->ray->ray_dir.x = cub->my_mlx->dir.x + cub->my_mlx->plane.x * camera_x;
    cub->ray->ray_dir.y = cub->my_mlx->dir.y + cub->my_mlx->plane.y * camera_x;
    
}

void calculate_step_dist(t_cub *cub, t_mlx *my_mlx, t_ray *ray)
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
}

void perform_dda(t_cub *cub, t_ray *ray)
{
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
            ray->side = 1;
        }
        
        // Vérifier où le mur est rencontré
        if (cub->maps->my_map[ray->map_y][ray->map_x] == '1')
            break;
    }
    
    // Calcul de la distance perpendiculaire au mur avec correction fish-eye
    double cos_angle;
    if (ray->side == 0)
    {
        ray->perp_wall_dist = (ray->map_x - cub->my_mlx->pos.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;
        cos_angle = fabs(ray->ray_dir.x * cub->my_mlx->dir.x + ray->ray_dir.y * cub->my_mlx->dir.y);
    }
    else
    {
        ray->perp_wall_dist = (ray->map_y - cub->my_mlx->pos.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;
        cos_angle = fabs(ray->ray_dir.x * cub->my_mlx->dir.x + ray->ray_dir.y * cub->my_mlx->dir.y);
    }
    
    // Division par le cosinus de l'angle pour corriger la déformation
    ray->perp_wall_dist /= cos_angle;
}

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
}

void raycaster(t_cub *cub)
{
    int x = 0;

    mlx_destroy_image(cub->my_mlx->mlx_ptr, cub->my_mlx->img_ptr);
    cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, SCREEN_W, SCREEN_H);
    cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr, &cub->my_mlx->bpp, 
                                              &cub->my_mlx->size_line, &cub->my_mlx->endian);                                      
    while (x < SCREEN_W)
    {
        calculate_ray_dir(cub, x);
        calculate_step_dist(cub, cub->my_mlx, cub->ray);
        perform_dda(cub, cub->ray);
        if (cub->ray->side == 0)
            cub->ray->perp_wall_dist = (cub->ray->side_dist.x - cub->ray->delta_dist.x);
        else
            cub->ray->perp_wall_dist = (cub->ray->side_dist.y - cub->ray->delta_dist.y);
        // Calcul des dimensions du mur
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
    // Affichage de l'image dans la fenêtre
    mlx_put_image_to_window(cub->my_mlx->mlx_ptr, cub->my_mlx->win_ptr, cub->my_mlx->img_ptr, 0, 0);
}

