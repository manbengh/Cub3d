/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:18:51 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/13 16:18:53 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *s, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!s || !to_find) && len == 0)
		return (0);
	if (to_find[j] == '\0')
		return ((char *)s);
	while (s[i] && i < len)
	{
		j = 0;
		while (to_find[j] == s[i + j] && to_find[j] != '\0' && (i + j) < len)
		{
			if (to_find[j + 1] == '\0')
				return (((char *)s) + i);
			j++;
		}
		i++;
	}
	return (0);
}

/*int main()
{
	char a[] = "il etait une fois";
	char b[] = "e";
	printf("vrai : %s \n", strnstr(a, b, 4));
	printf("%s", ft_strnstr(a, b, 20));
}*/