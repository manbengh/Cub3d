/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:20:50 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/15 17:20:51 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *str, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i] && (str[i] != c))
		{
			word++;
			while (str[i] && (str[i] != c))
				i++;
		}
	}
	return (word);
}

static int	ft_strlen_c(const char *str, char c, int j)
{
	int	t;

	t = 0;
	if (!str)
		return (0);
	while (str[j] == c)
		j++;
	while (str[j] && str[j] != c)
	{
		t++;
		j++;
	}
	return (t);
}

static char	*malloc_word(const char *s, char c, int j)
{
	char	*dup;
	int		i;

	i = 0;
	if (!s)
		return (0);
	dup = (char *)malloc((ft_strlen_c(s, c, j) + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (s[j] && (s[j] != c))
	{
		dup[i] = s[j];
		i++;
		j++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	res = (char **)malloc((sizeof(char *)) * (count_word(s, c) + 1));
	if (!res)
		return (0);
	while (s[j])
	{
		while (s[j] && (s[j] == c))
			j++;
		if (s[j] && (s[j] != c))
		{
			res[i] = malloc_word(s, c, j);
			i++;
			while (s[j] && (s[j] != c))
				j++;
		}
	}
	res[i] = 0;
	return (res);
}

/*int main()
{
	char str[100] = "--1-2--3---4----5-----42";
	int i = 0;
	char **s = ft_split(str, '1');
	while (i < 2)
	{
		printf("%s\n", s[i]);
		i++;
	}
	return(0);
}*/