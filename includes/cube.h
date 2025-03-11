#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "../minilibx-linux/mlx.h"

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
#include <math.h>

typedef struct t_map
{
    int long_line;
    char **no;
    char **so;
    char **ea;
    char **we;
    char **f;
    char **c;
    char **my_map;
    char    player_dir;
}               t_map;


typedef struct t_cub
{
    int     lines;
    char    **stock_l;
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int bpp;
    int size_line;
    int endian;
    t_map   *maps;
}               t_cub;

// CHECKS

int	check_player(t_cub *cub, char **map_check);
int	check_other_num(t_cub *cub, char **map_check);
int	check_first_last_line(t_cub *cub, char **map_check);
int	check_walls(t_cub *cub, char **map_check);
int	check_file_name(char *argv);
int	ft_check_nums(char *str);
int	check_names(t_map *maps);

int compare_dir(t_map *maps, char *stock_l);
int	check_params_c(t_map *maps);

int line_is_empty(char *line);
int	longest_line(t_cub *cub);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	count_lines(int fd);
int	ft_count_num(char *str);
int	ft_count_times(char *str, char c);
int	check_my_map(t_cub *cub, char **map_check, int c);

//FREE
void	free_tab(char **tab);
void	free_struct(t_cub *cub);
void	print_error(t_cub *cub, char *str, char **map_check);

// GAME
void my_game(t_cub *cub);
int touch_key(int keycode, t_cub *cub);


#endif