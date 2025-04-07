/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:24 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/07 15:33:37 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int compare_dir_c_f(t_map *maps, char *stock_l)
{
    if (ft_strncmp("C ", stock_l, 2) == 0 && maps->c == NULL)
    {
        maps->c = ft_split(stock_l, ' ');
        return (1);
    }
    else if (ft_strncmp("F ", stock_l, 2) == 0 && maps->f == NULL)
    {
        maps->f = ft_split(stock_l, ' ');
        return (1);
    }
    return (0);
}

int compare_dir(t_map *maps, char *stock_l)
{
    if (ft_strncmp("NO ", stock_l, 3) == 0 && maps->no == NULL)
    {
        maps->no = ft_split(stock_l, ' ');
        return (1);
    }
    else if (ft_strncmp("SO ", stock_l, 3) == 0 && maps->so == NULL)
    {
        maps->so = ft_split(stock_l, ' ');
        return (1);
    }
    else if (ft_strncmp("EA ", stock_l, 3) == 0 && maps->ea == NULL)
    {
        maps->ea = ft_split(stock_l, ' ');
        return (1);
    }
    else if (ft_strncmp("WE ", stock_l, 3) == 0 && maps->we == NULL)
    {
        maps->we = ft_split(stock_l, ' ');
        return (1);
    }
    return (compare_dir_c_f(maps, stock_l));
}

int check_params_f(t_map *maps)
{
    int i;

    i = 0;
    if (maps->f)
    {
        while (maps->f[1][i])
        {
            // if (ft_isdigit(maps->f[1][i]) == 0 || maps->f[1][i] != ',')
            if (ft_isalpha(maps->f[1][i]))
                return (printf("Error !\nCheck params : no letters \n"), 1);
            if (maps->f[1][i] == ',' && (ft_isdigit(maps->f[1][i + 1]) == 0 || ft_isdigit(maps->f[1][i - 1]) == 0))
                return (printf("Error !\nCheck params : incorrect number\n"), 1);
            if (ft_count_num(maps->f[1]) < 3 || ft_count_num(maps->f[1]) > 9)
                return (printf("Error !\nCheck params : incorrect number\n"), 1);
            if (ft_check_nums(maps->f[1]) == 1)
                return (1);
            i++;
        }
    }
    return (0);
}

int check_params_c(t_map *maps)
{
    int i;

    i = 0;
    if (maps->c)
    {
        while (maps->c[1][i])
        {
            // if (ft_isdigit(maps->c[1][i]) == 0 && maps->c[1][i] != ',')
            if (ft_isalpha(maps->c[1][i]))
                return (printf("Error !\nCheck params : no letters \n"), 1);
            if (maps->c[1][i] == ',' && (!ft_isdigit(maps->c[1][i + 1]) || !ft_isdigit(maps->c[1][i - 1])))
                return (printf("Error !\nCheck params : incorrect number\n"), 1);
            if (ft_count_num(maps->c[1]) < 3 || ft_count_num(maps->c[1]) > 9)
                return (printf("Error !\nCheck params : incorrect number\n"), 1);
            if (ft_check_nums(maps->c[1]) == 1)
                return (1);
            i++;
        }
    }
    return (check_params_f(maps));
}

int check_names(t_map *maps)
{
    int i;

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
