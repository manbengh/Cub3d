#include "cube.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

// Carte du monde (identique à l'original)
int worldMap[MAP_WIDTH][MAP_HEIGHT] = 
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};




























































// void *mlx_ptr;
// void *win_ptr;
// void *img_ptr;
// char *img_data;

// int screen_width = SCREEN_WIDTH;
// int screen_height = SCREEN_HEIGHT;

// // Fonction d'initialisation de la fenêtre
// int init() {
//     mlx_ptr = mlx_init();
//     if (!mlx_ptr) {
//         printf("MLX could not initialize!\n");
//         return -1;
//     }
//     win_ptr = mlx_new_window(mlx_ptr, screen_width, screen_height, "Raycaster");
//     if (!win_ptr) {
//         printf("Window could not be created!\n");
//         return -1;
//     }
//     img_ptr = mlx_new_image(mlx_ptr, screen_width, screen_height);
//     img_data = mlx_get_data_addr(img_ptr, &screen_width, &screen_height, &screen_width);
//     return 0;
// }

// // Fonction pour dessiner une ligne verticale (manipulation directe des pixels)
// void drawVerticalLine(int x, int startY, int endY, int color) {
//     for (int y = startY; y < endY; y++) {
//         img_data[(y * screen_width + x) * 4] = color & 0xFF;       // Blue
//         img_data[(y * screen_width + x) * 4 + 1] = (color >> 8) & 0xFF; // Green
//         img_data[(y * screen_width + x) * 4 + 2] = (color >> 16) & 0xFF; // Red
//         img_data[(y * screen_width + x) * 4 + 3] = 0;                 // Alpha (not used)
//     }
// }

// int main() {
//     if (init() < 0) {
//         return -1;
//     }

//     double posX = 23, posY = 16;  // Position du joueur
//     double dirX = -1, dirY = 0;   // Direction du joueur
//     double planeX = 0, planeY = 0.66; // Plan de la caméra

//     // double time = 0;  // Temps actuel
//     // double oldTime = 0;  // Temps de l'ancien frame

//     while (1) {
//         mlx_clear_window(mlx_ptr, win_ptr);

//         // Calcul du raycasting pour chaque pixel à l'écran
//         for (int x = 0; x < screen_width; x++) {
//             double cameraX = 2 * x / (double)screen_width - 1;
//             double rayDirX = dirX + planeX * cameraX;
//             double rayDirY = dirY + planeY * cameraX;
//             int mapX = (int)posX;
//             int mapY = (int)posY;

//             double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//             double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

//             double sideDistX, sideDistY;
//             int stepX, stepY;
//             int hit = 0;
//             int side;

//             // Initialisation des directions de déplacement et distances
//             if (rayDirX < 0) {
//                 stepX = -1;
//                 sideDistX = (posX - mapX) * deltaDistX;
//             } else {
//                 stepX = 1;
//                 sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//             }
//             if (rayDirY < 0) {
//                 stepY = -1;
//                 sideDistY = (posY - mapY) * deltaDistY;
//             } else {
//                 stepY = 1;
//                 sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//             }

//             // DDA algorithm pour déterminer le point d'intersection
//             while (hit == 0) {
//                 if (sideDistX < sideDistY) {
//                     sideDistX += deltaDistX;
//                     mapX += stepX;
//                     side = 0;
//                 } else {
//                     sideDistY += deltaDistY;
//                     mapY += stepY;
//                     side = 1;
//                 }
//                 if (worldMap[mapX][mapY] > 0) hit = 1;
//             }

//             double perpWallDist;
//             if (side == 0) perpWallDist = (sideDistX - deltaDistX);
//             else perpWallDist = (sideDistY - deltaDistY);

//             int lineHeight = (int)(screen_height / perpWallDist);
//             int drawStart = -lineHeight / 2 + screen_height / 2;
//             if (drawStart < 0) drawStart = 0;
//             int drawEnd = lineHeight / 2 + screen_height / 2;
//             if (drawEnd >= screen_height) drawEnd = screen_height - 1;

//             int color;
//             if (side == 0) {
//                 color = 0xFF0000; // Rouge
//             } else {
//                 color = 0x00FF00; // Vert
//             }

//             drawVerticalLine(x, drawStart, drawEnd, color);
//         }

//         mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
//         mlx_do_sync(mlx_ptr);

//         usleep(1000 / 60);  // Limiter à 60 FPS
//     }

//     mlx_destroy_image(mlx_ptr, img_ptr);
//     mlx_destroy_window(mlx_ptr, win_ptr);
//     return 0;
// }




