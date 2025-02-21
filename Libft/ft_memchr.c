/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:37:55 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/13 14:37:57 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((char *) s + i);
		i++;
	}
	return (NULL);
}

/*int main()
{
	char str[] = {0, 1, 2, 3, 4, 5, 10, 60};
	int size = 10;
	printf("%p \n", ft_memchr(str, 4, size));
	printf("%p \n", memchr(str, 4, size));
}*/