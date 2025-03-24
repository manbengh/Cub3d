#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "../minilibx-linux/mlx.h"

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_W 1280
#define SCREEN_H 800

/* KEYCODES */
# define KEY_ESC 65307   // exit
# define KEY_W 122       // move forwards
# define KEY_A 113       // move left
# define KEY_S 115       // move backwards
# define KEY_D 100       // move right
# define KEY_LEFT 65361  // look left
# define KEY_RIGHT 65363 // look right
# define KEY_CTRL 65507  // ctrl

# define PLAYER_SPEED 0.014
# define ROTATION_SPEED 0.024

//pour x et y des vecteurs
typedef double __attribute((ext_vector_type(2)))	t_double;
typedef int __attribute__((ext_vector_type(2)))		t_int;

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
    t_int    pos;
}               t_map;

typedef struct t_key
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			esc;
	int			ctrl;
    int         rotate;
}	t_key;

typedef struct t_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int bpp;
    int size_line;
    int endian;
    t_double    pos;
    t_int       dir;
    t_double    plane;
}               t_mlx;

typedef struct t_cub
{
    int     lines;
    char    **stock_l;
    t_mlx   *my_mlx;
    t_map   *maps;
    t_key      *keys;
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

#endif