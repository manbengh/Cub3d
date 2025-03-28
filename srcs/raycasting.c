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
    
    // Log pour voir l'angle de vision en degrés
    double angle = atan2(cub->ray->ray_dir.y, cub->ray->ray_dir.x) * 180 / M_PI;
    
    // Debug prints
    printf("Ray Direction: x = %f, y = %f\n", cub->ray->ray_dir.x, cub->ray->ray_dir.y);
    printf("Ray Angle: %f°\n", angle);
    
    // Option conditionnelle pour le cercle trigonométrique
    #ifdef DEBUG_TRIG
    print_trig_circle(angle);
    #endif
}
// void calculate_ray_dir(t_cub *cub, int x)
// {
//     double camera_x = 2 * x / (double)SCREEN_W - 1;
//     cub->ray->ray_dir.x = cub->my_mlx->dir.x + cub->my_mlx->plane.x * camera_x;
//     cub->ray->ray_dir.y = cub->my_mlx->dir.y + cub->my_mlx->plane.y * camera_x;

//     // Normalisation de ray_dir
//     double length = sqrt(cub->ray->ray_dir.x * cub->ray->ray_dir.x + 
//                          cub->ray->ray_dir.y * cub->ray->ray_dir.y);
//     if (length != 0)  
//     {
//         cub->ray->ray_dir.x /= length;
//         cub->ray->ray_dir.y /= length;
//     }

//     // Log pour voir si c'est bien normalisé
//     // printf("Normalized ray_dir: x = %f, y = %f\n", cub->ray->ray_dir.x, cub->ray->ray_dir.y);

//     // Log pour voir l'angle de vision en degrés
//      double angle = atan2(cub->ray->ray_dir.y, cub->ray->ray_dir.x) * 180 / M_PI;
//      print_trig_circle(angle);
// }




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

// void    calculate_step_dist(t_cub *cub, t_mlx *my_mlx, t_ray *ray)
// {
//     (void)cub;
//     ray->map_x = (int)my_mlx->pos.x;
//     ray->map_y = (int)my_mlx->pos.y;

//     if (fabs(ray->ray_dir.y) < 1e-6)
//         ray->delta_dist.y = 1e30;
//     else
//         ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
//     if (ray->ray_dir.x == 0)
//         ray->delta_dist.x = 1e30;
//     else
//         ray->delta_dist.x = fabs(1 / ray->ray_dir.x);

//     // if (ray->ray_dir.y == 0)
//     //     ray->delta_dist.y = 1e30;
//     // else
//     //     ray->delta_dist.y = fabs(1 / ray->ray_dir.y);

//     if (ray->ray_dir.x < 0)
//     {
//         ray->step_x = -1;
//         ray->side_dist.x = (my_mlx->pos.x - ray->map_x) * ray->delta_dist.x;
//     }
//     else
//     {
//         ray->step_x = 1;
//         ray->side_dist.x = (ray->map_x + 1.0 - my_mlx->pos.x) * ray->delta_dist.x;
//     }

//     if (ray->ray_dir.y < 0)
//     {
//         ray->step_y = -1;
//         ray->side_dist.y = (my_mlx->pos.y - ray->map_y) * ray->delta_dist.y;
//     }
//     else
//     {
//         ray->step_y = 1;
//         ray->side_dist.y = (ray->map_y + 1.0 - my_mlx->pos.y) * ray->delta_dist.y;
//     }
//     // printf("1 / ray_dir.x = %f\n", 1 / ray->ray_dir.x);
//     // printf("1 / ray_dir.y = %f\n", 1 / ray->ray_dir.y);
//     // printf("delta_dist.x = %f\n", ray->delta_dist.x);
//     // printf("delta_dist.y = %f\n", ray->delta_dist.y);

// }

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


// void perform_dda(t_cub *cub, t_ray *ray)
// {
//     while (1)
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
//             ray->side = 1;
//         }

//         // Vérifier où le mur est rencontré
//         if (cub->maps->my_map[ray->map_y][ray->map_x] == '1')
//         {
//             printf("Hit Wall at Map Position: x = %d, y = %d\n", ray->map_x, ray->map_y);

//             if (ray->side == 0)
//             {
//                 if (ray->ray_dir.x > 0)
//                     printf("Hit an East wall\n");
//                 else
//                     printf("Hit a West wall\n");
//             }
//             else
//             {
//                 if (ray->ray_dir.y > 0)
//                     printf("Hit a South wall\n");
//                 else
//                     printf("Hit a North wall\n");
//             }
//             break;
//         }

//         // Calculer la distance du mur
//         if (ray->side == 0)
//             ray->perp_wall_dist = (ray->map_x - cub->my_mlx->pos.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;
//         else
//             ray->perp_wall_dist = (ray->map_y - cub->my_mlx->pos.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;

//         // printf("Wall distance: %f\n", ray->perp_wall_dist);
//     }
// }



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
        {
            printf("Hit Wall at Map Position: x = %d, y = %d\n", ray->map_x, ray->map_y);
    
            if (ray->side == 0)
            {
                if (ray->ray_dir.x > 0)
                    printf("Hit an East wall\n");
                else
                    printf("Hit a West wall\n");
            }
            else
            {
                if (ray->ray_dir.y > 0)
                    printf("Hit a South wall\n");
                else
                    printf("Hit a North wall\n");
            }
            break;
        }
    }
    
    // Calcul de la distance perpendiculaire au mur avec correction fish-eye
    double cos_angle;
    if (ray->side == 0)
    {
        ray->perp_wall_dist = (ray->map_x - cub->my_mlx->pos.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;
        // Correction fish-eye : projection sur le plan de la caméra
        cos_angle = fabs(ray->ray_dir.x * cub->my_mlx->dir.x + ray->ray_dir.y * cub->my_mlx->dir.y);
    }
    else
    {
        ray->perp_wall_dist = (ray->map_y - cub->my_mlx->pos.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;
        // Correction fish-eye : projection sur le plan de la caméra
        cos_angle = fabs(ray->ray_dir.x * cub->my_mlx->dir.x + ray->ray_dir.y * cub->my_mlx->dir.y);
    }
    
    // Division par le cosinus de l'angle pour corriger la déformation
    ray->perp_wall_dist /= cos_angle;
    
    // Debug de la distance du mur
    printf("Wall distance (fish-eye corrected): %f\n", ray->perp_wall_dist);
    printf("Cos Angle: %f\n", cos_angle);
}
// void perform_dda(t_cub *cub, t_ray *ray)
// {
//     while (1)
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
//             ray->side = 1;
//         }

//                 // Vérifier où le mur est rencontré
//                 if (cub->maps->my_map[ray->map_y][ray->map_x] == '1')
//                 {
//                     printf("Hit Wall at Map Position: x = %d, y = %d\n", ray->map_x, ray->map_y);
        
//                     if (ray->side == 0)
//                     {
//                         if (ray->ray_dir.x > 0)
//                             printf("Hit an East wall\n");
//                         else
//                             printf("Hit a West wall\n");
//                     }
//                     else
//                     {
//                         if (ray->ray_dir.y > 0)
//                             printf("Hit a South wall\n");
//                         else
//                             printf("Hit a North wall\n");
//                     }
//                     break;
//                 }
//     }

//     // Calcul de la distance perpendiculaire au mur
//     // Calcul de la distance perpendiculaire au mur
//     if (ray->side == 0)
//         ray->perp_wall_dist = (ray->map_x - cub->my_mlx->pos.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;
//     else
//         ray->perp_wall_dist = (ray->map_y - cub->my_mlx->pos.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;

//     // Correction Fish-Eye
//     double cos_angle = fabs(ray->ray_dir.x * cub->my_mlx->dir.x + ray->ray_dir.y * cub->my_mlx->dir.y);
//     ray->perp_wall_dist /= cos_angle; 

//     // Debug de la distance du mur
//     printf("Wall distance: %f\n", ray->perp_wall_dist);
// }



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
    // printf("Wall Height: %d, Start: %d, End: %d\n", ray->line_h, ray->start_draw, ray->end_draw);

}

void init_mlx_vectors(t_mlx *my_mlx, char orientation) {
    if (orientation == 'E') {  
        my_mlx->dir.x = 1.0;
        my_mlx->dir.y = 0.0;
        my_mlx->plane.x = 0.0;
        my_mlx->plane.y = 0.66;
    } 
    else if (orientation == 'W') {  
        my_mlx->dir.x = -1.0;
        my_mlx->dir.y = 0.0;
        my_mlx->plane.x = 0.0;
        my_mlx->plane.y = -0.66;
    } 
    else if (orientation == 'S') {  
        my_mlx->dir.x = 0.0;
        my_mlx->dir.y = 1.0;
        my_mlx->plane.x = -0.66;
        my_mlx->plane.y = 0.0;
    } 
    else {  // Nord
        my_mlx->dir.x = 0.0;
        my_mlx->dir.y = -1.0;
        my_mlx->plane.x = 0.66;
        my_mlx->plane.y = 0.0;
    }

    // Debug
    // printf("Orientation: %c\n", orientation);
    // printf("Dir: x = %f, y = %f\n", my_mlx->dir.x, my_mlx->dir.y);
    // printf("Plane: x = %f, y = %f\n", my_mlx->plane.x, my_mlx->plane.y);
}


// void init_mlx_vectors(t_mlx *my_mlx) {
//     // Initialisation du vecteur de direction (dir) et du plan (plane)
//     // Ces valeurs peuvent être définies en fonction de l'orientation de la caméra
//     my_mlx->dir[0] = 1.0;  // Direction sur l'axe X (pour une vue de base)
//     my_mlx->dir[1] = 0.0;  // Direction sur l'axe Y

//     my_mlx->plane[0] = 0.0;  // Plan sur l'axe X (perpendiculaire à la direction)
//     my_mlx->plane[1] = 0.66; // Plan sur l'axe Y (pour la perspective)

//     // Vérification que les vecteurs sont initialisés
//     printf("Direction vector: x = %f, y = %f\n", my_mlx->dir[0], my_mlx->dir[1]);
//     printf("Plane vector: x = %f, y = %f\n", my_mlx->plane[0], my_mlx->plane[1]);
// }



void raycaster(t_cub *cub)
{
    int x = 0;

    // Récupérer la position et l'orientation du joueur
    // get_pos_player(cub);

    // Initialiser les vecteurs en fonction de l'orientation du joueur
    // init_mlx_vectors(cub->my_mlx, cub->maps->player_dir);

    // Affichage des valeurs d'initialisation
    // printf("Plane: x = %f, y = %f\n", cub->my_mlx->plane.x, cub->my_mlx->plane.y);
    // printf("Player Position: x = %f, y = %f\n", cub->my_mlx->pos.x, cub->my_mlx->pos.y);
    // printf("Player Direction: x = %f, y = %f\n", cub->my_mlx->dir.x, cub->my_mlx->dir.y);

    // Détruire et recréer l'image pour le rendu
    mlx_destroy_image(cub->my_mlx->mlx_ptr, cub->my_mlx->img_ptr);
    cub->my_mlx->img_ptr = mlx_new_image(cub->my_mlx->mlx_ptr, SCREEN_W, SCREEN_H);
    cub->my_mlx->img_data = mlx_get_data_addr(cub->my_mlx->img_ptr, &cub->my_mlx->bpp, 
                                              &cub->my_mlx->size_line, &cub->my_mlx->endian);
    
    while (x < SCREEN_W)
    {
        calculate_ray_dir(cub, x);
        calculate_step_dist(cub, cub->my_mlx, cub->ray);
        perform_dda(cub, cub->ray);

        // Vérifier la distance finale avant de dessiner
        // printf("Final Perpendicular Wall Distance: %f\n", cub->ray->perp_wall_dist);
        
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

