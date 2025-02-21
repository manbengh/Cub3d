/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:59:46 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/15 14:59:47 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_char(char const *a, int c)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
	{
		if (a[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		s;
	char	*str;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1) - 1;
	s = 0;
	while ((s1[start]) && (is_in_char(set, s1[start])))
		start++;
	while ((end > start) && (is_in_char(set, s1[end])))
		end--;
	str = malloc(((end - start) + 2) * sizeof(char));
	if (!str)
		return (0);
	while (start <= end)
		str[s++] = s1[start++];
	str[s] = 0;
	return (str);
}

// int main()
// {
// 	char a[] = "HelloWorld";
// 	char b[] = "Hd";
// 	printf("%s", ft_strtrim(a, b));
// }