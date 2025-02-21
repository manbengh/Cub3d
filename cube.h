#ifndef CUBE_H
# define CUBE_H

// # include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
    t_map   *maps;
}               t_cub;

// CHECKS

int	check_player(t_cub *cub, char **map_check);
int	check_other_num(t_cub *cub, char **map_check);
int	check_first_last_line(t_cub *cub, char **map_check);
int	check_walls(t_cub *cub, char **map_check);
int	check_file_name(char *argv);

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

#endif