/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:38:22 by ahbey             #+#    #+#             */
/*   Updated: 2025/04/16 14:16:53 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	u1;
	unsigned char	u2;

	i = 0;
	while (s1[i] && s2[i])
	{
		u1 = (unsigned char)s1[i];
		u2 = (unsigned char)s2[i];
		if (u1 != u2 || u1 == '\0' || u2 == '\0')
			return (u1 - u2);
		i++;
	}
	return (0);
}

int	check_file_name(char *argv)
{
	int		len;
	char	*str;

	str = argv;
	len = ft_strlen(str);
	if (argv)
	{
		if (len <= 4)
		{
			write(1, "File name wrong !\n", 18);
			exit(1);
		}
		if (len > 4 && ft_strcmp(str + len - 4, ".cub") != 0)
		{
			write(1, "File name wrong !\n", 18);
			exit(1);
		}
	}
	return (0);
}

int	count_lines(int fd)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		exit(1);
	}
	if (str)
	{
		i = ft_strlen(str);
		while (str[i] == '\0')
		{
			free(str);
			str = get_next_line(fd);
			j++;
			if (!str)
				break ;
			i = ft_strlen(str);
		}
	}
	return (j);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_count_num(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			count++;
		i++;
	}
	return (count);
}
