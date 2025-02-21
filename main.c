#include "cube.h"

char	**check_map(t_cub *cub, int fd)
{
	char	**map_check;
	char	*str;
    int 	i;

    i = 0;
	map_check = ft_calloc((cub->lines + 1), sizeof(char *));
	if (!map_check)
		printf("Error malloc!");
	while (i < cub->lines)
	{
		str = get_next_line(fd);
		map_check[i] = ft_strdup(str);
		if (!map_check)
			printf("Error malloc!");
		free(str);
		i++;
	}
	close(fd);
	check_my_map(cub, map_check, cub->lines);
	// return (check_path(map_check, cub->lines));
    free_tab(map_check);
    return (NULL);
}


void    init_struct(t_cub *cub, int fd, char **argv)
{
    cub->lines = count_lines(fd);
    close(fd);
    fd = open(argv[1], O_RDONLY);
    cub->maps = malloc(sizeof(t_map));
    if (!cub->maps)
        return ;
    cub->maps->my_map = ft_calloc((cub->lines + 1 ), sizeof(char *));
    if (!cub->maps->my_map)
        return ;
    cub->maps->c = NULL;
    cub->maps->f = NULL;
    cub->maps->no = NULL;
    cub->maps->so = NULL;
    cub->maps->ea = NULL;
    cub->maps->we = NULL;
    cub->maps->long_line = 0;
    check_map(cub, fd);
}


int main(int argc, char **argv)
{
    int fd;
    t_cub   cub;

    if (argc == 2)
    {
        check_file_name(argv[1]);
        fd = open(argv[1], O_RDONLY);
        if (fd < 0 || read(fd, 0, 0) < 0)
			return (printf("Error !\nFile can't be opened\n"), 0);
        init_struct(&cub, fd, argv);
        // free_struct(&cub);
        print_error(&cub, NULL, NULL);
    }
    return (0);
}
