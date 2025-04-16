#include "cube.h"

void calculate_ray_dir(t_cub *cub, int x)
{
    double camera_x;
    
    camera_x = 2 * x / (double)SCREEN_W - 1;
    cub->ray->ray_dir.x = cub->my_mlx->dir.x + cub->my_mlx->plane.x * camera_x;
    cub->ray->ray_dir.y = cub->my_mlx->dir.y + cub->my_mlx->plane.y * camera_x;
}

void calculate_delta_dist(t_ray *ray)
{
    if (fabs(ray->ray_dir.y) < 1e-6)
        ray->delta_dist.y = 1e30;
    else
        ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
    if (ray->ray_dir.x == 0)
        ray->delta_dist.x = 1e30;
    else
        ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
}

void calculate_step_dist(t_mlx *my_mlx, t_ray *ray)
{
    ray->map_x = (int)my_mlx->pos.x;
    ray->map_y = (int)my_mlx->pos.y;
    calculate_delta_dist(ray);
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

void while_dda(t_cub *cub, t_ray *ray)
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
        if (cub->maps->my_map[ray->map_y][ray->map_x] == '1')
            break;
    }
}

void perform_dda(t_cub *cub, t_ray *ray)
{
    double cos_angle;

    while_dda(cub, ray);
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
    ray->perp_wall_dist /= cos_angle;
}
