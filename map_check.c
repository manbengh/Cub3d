#include "cube.h"

int compare_dir(t_map *maps, char *stock_l)
{
	if (ft_strncmp("NO ", stock_l, 3) == 0 && maps->no == NULL)
	{
		maps->no = ft_split(stock_l, ' ');
		printf("NO ==> %s %s", maps->no[0], maps->no[1]);
		return (1);
	}
	else if (ft_strncmp("SO ", stock_l, 3) == 0 && maps->so == NULL)
	{
		maps->so = ft_split(stock_l, ' ');
		printf("SO ==> %s %s", maps->so[0], maps->so[1]);
		return (1);
	}
	else if (ft_strncmp("EA ", stock_l, 3) == 0 && maps->ea == NULL)
	{
		maps->ea = ft_split(stock_l, ' ');
		printf("EA ==> %s %s", maps->ea[0], maps->ea[1]);
		return (1);
	}
	else if (ft_strncmp("WE ", stock_l, 3) == 0 && maps->we == NULL)
	{
		maps->we = ft_split(stock_l, ' ');
		printf("WE ==> %s %s", maps->we[0], maps->we[1]);
		return (1);
	}
	else if (ft_strncmp("C ", stock_l, 2) == 0 && maps->c == NULL)
	{
		maps->c = ft_split(stock_l, ' ');
		printf("C ==> %s %s", maps->c[0], maps->c[1]);
		return (1);
	}
	else if (ft_strncmp("F ", stock_l, 2) == 0 && maps->f == NULL)
	{
		maps->f = ft_split(stock_l, ' ');
		printf("F ==> %s %s", maps->f[0], maps->f[1]);
		return (1);
	}
	return (0);
}

int	check_names(t_map *maps)
{
	int	i;

	i = 0;
	if (maps->c && ft_count_times(maps->c[1], ',') != 2)
		return (printf("Error : check C params\n"), 1);
	if (maps->f && ft_count_times(maps->f[1], ',') != 2)
		return (printf("Error : check F params\n"), 1);
	if (maps->no && (!ft_strchr(maps->no[1], '/') || !maps->no[1]))
		return (printf("Error : check NO path\n"), 1);
	if (maps->so && (!ft_strchr(maps->so[1], '/') || !maps->so[1]))
		return (printf("Error : check SO path\n"), 1);
	if (maps->ea && (!ft_strchr(maps->ea[1], '/') || !maps->ea[1]))
		return (printf("Error : check EA path\n"), 1);
	if (maps->we && (!ft_strchr(maps->we[1], '/') || !maps->we[1]))
		return (printf("Error : check WE path\n"), 1);
	return (0);
}

int	ft_check_nums(char *str)
{
	int	i;
	int	num;
	char	**check_n;

	i = 0;
	num = 0;
	check_n = ft_split(str, ',');
	while (check_n[i])
	{
		num = ft_atoi(check_n[i]);
		if (num > 255 || num < 0)
		{
			free_tab(check_n);
			return (ft_printf("Error : check params\n"), 1);
		}
		i++;
	}
	free_tab(check_n);
	return (0);
}

int	check_params(t_map *maps)
{
	int i;

	i = 0;
	if (maps->c)
	{
		while (maps->c[1][i])
		{
			if (ft_isalpha(maps->c[1][i]) == 1)
				return (printf("Error : check params \n"), 1);
			if (maps->c[1][i] == ',' && (ft_isdigit(maps->c[1][i + 1]) == 0 || ft_isdigit(maps->c[1][i - 1]) == 0))
				return (printf("Error : check params !\n"), 1);
			if (ft_count_num(maps->c[1]) < 3 || ft_count_num(maps->c[1]) > 9)
				return (printf("Error : check params !!\n"), 1);
			if (ft_check_nums(maps->c[1]) == 1)
				return (1);
			i++;
		}
	}
	i = 0;
	if (maps->f)
	{
		while (maps->f[1][i])
		{
			if (ft_isalpha(maps->f[1][i]) == 1)
				return (printf("Error : check params \n"), 1);
			if (maps->f[1][i] == ',' && (ft_isdigit(maps->f[1][i + 1]) == 0 || ft_isdigit(maps->f[1][i - 1]) == 0))
				return (printf("Error : check params \n"), 1);
			if (ft_count_num(maps->f[1]) < 3 || ft_count_num(maps->f[1]) > 9)
				return (printf("Error : check params \n"), 1);
			if (ft_check_nums(maps->f[1]) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}

void init_maps(t_cub *cub, char **stock_l, char **map_check)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (compare_dir(cub->maps, stock_l[i]) == 0)
		{
			free_tab(stock_l);
			print_error(cub, "Missing parameters", map_check);
			return ;
		}
		if (check_names(cub->maps) == 1 || check_params(cub->maps) == 1)
		{
			free_tab(stock_l);
			return (print_error(cub, NULL, map_check)) ;
		}
		i++;
	}
}

int check_dir(char **map_check, t_cub *cub)
{
	int i;
	int j;
	char **stock_l;

	i = 0;
	j = 0;
	stock_l = ft_calloc(7, sizeof(char *));
	while (i < cub->lines)
	{
		if (!line_is_empty(map_check[i]))
		{
			stock_l[j] = ft_strdup(map_check[i]);
			j++;
		}
		i++;
		if (j == 6)
			break;
	}
	if (i == 0)
		return (print_error(cub, "File empty", map_check), 1);
	if (j != 6)
		return (print_error(cub, "Not enough", map_check), 1);
	init_maps(cub, stock_l, map_check);
	free_tab(stock_l);
	return (i);
}

int	check_flood(t_cub *cub, char **map_check)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->lines - 1)
	{
		j = -1;
		while (++j < ft_strlen(cub->maps->my_map[i]))
		{
			if (cub->maps->my_map[i][j] == '0')
			{
				if (cub->maps->my_map[i][j + 1] == ' ')
					return (print_error(cub, "Error !\nFlood 1", map_check), 1);
				else if (cub->maps->my_map[i][j - 1] == ' ')
					return (print_error(cub, "Error !\nFlood 2", map_check), 1);
				else if (ft_strlen(cub->maps->my_map[i - 1]) - 2 < j || cub->maps->my_map[i - 1][j] == ' ')
					return (print_error(cub, "Error !\nFlood 3", map_check), 1);
				else if (ft_strlen(cub->maps->my_map[i + 1]) - 2 < j || cub->maps->my_map[i + 1][j] == ' ')
					return (print_error(cub, "Error !\nFlood 4", map_check), 1);
			}
		}
	}
	return (0);
}

int	fill_my_map(t_cub *cub, char **map_check, int i)
{
	int j;

	j = 0;
	while (i < cub->lines)
	{
		if (!line_is_empty(map_check[i]))
		{
			cub->maps->my_map[j] = ft_strdup(map_check[i]);
			// printf("cub->maps->my_map[j] => {%s}\n", cub->maps->my_map[j]);
			j++;
		}
		i++;
	}
	if (j == 0)
		return (print_error(cub, "Error !\nMissing parameters !", map_check), 1);
	cub->lines = j;
	cub->maps->long_line = longest_line(cub);
	if (check_first_last_line(cub, map_check) == 1 || check_walls(cub, map_check) == 1
		|| check_player(cub, map_check) == 1 || check_other_num(cub, map_check) == 1)
		return (1);
	if (check_flood(cub, map_check) == 1)
		return (1);
	return (0);
}

int	check_my_map(t_cub *cub, char **map_check, int c)
{
	int	len;
	int	i;
	
	(void)c;
	len = ft_strlen(map_check[0]);
	i = check_dir(map_check, cub);
	if (i > 1)
	{
		if (fill_my_map(cub, map_check, i) == 1)
			return (1);
	}
	return (0);
}
