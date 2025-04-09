/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:55 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/09 19:12:36 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void check_map(t_cub *cub, int fd)
{
	char **map_check;
	char *str;
	int i;

	i = 0;
	map_check = ft_calloc((cub->lines + 1), sizeof(char *));
	if (!map_check)
		return (print_error(cub, "map_check alloc error", map_check));
	while (i < cub->lines)
	{
		str = get_next_line(fd);
		map_check[i] = ft_strdup(str);
		if (!map_check)
			return (print_error(cub, "strdup alloc error", map_check));
		free(str);
		i++;
	}
	close(fd);
	check_my_map(cub, map_check, cub->lines);
	
	free_tab(map_check);
}

void init_struct(t_cub *cub, int fd, char **argv)
{
	cub->lines = count_lines(fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	cub->maps = ft_calloc(sizeof(t_map), 1);
	if (!cub->maps)
		return ;
	cub->my_mlx = ft_calloc(sizeof(t_mlx), 1);
	if (!cub->my_mlx)
		return ;
	cub->maps->my_map = ft_calloc((cub->lines + 1), sizeof(char *));
	if (!cub->maps->my_map)
		return;
	cub->keys = ft_calloc(sizeof(t_key), 1);
	if (!cub->keys)
		return ;
	cub->ray = ft_calloc(sizeof(t_ray), 1);
		if (!cub->ray)
			return ;
	check_map(cub, fd);
}

int main(int argc, char **argv)
{
	int fd;
	t_cub cub;
	
	if (argc == 2)
	{
		check_file_name(argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0 || read(fd, 0, 0) < 0)
			return (printf("Error !\nFile can't be opened\n"), 0);
		init_struct(&cub, fd, argv);
		for(int i = 0;cub.maps->my_map[i];i++)
			printf("%s",cub.maps->my_map[i]);
		my_game(&cub);
	}
	return (0);
}

