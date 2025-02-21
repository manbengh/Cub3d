/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:29:03 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/13 15:29:05 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*o;
	unsigned char	*j;

	i = 0;
	o = (unsigned char *)(s1);
	j = (unsigned char *)(s2);
	while (i < n)
	{
		if (o[i] != j[i])
			return (o[i] - j[i]);
		i++;
	}
	return (0);
}

/*int main()
{
	char a[] = "abc";
	char b[] = "";
	printf("vrai : %d \n", memcmp(a, b, 0));
	printf(" %d \n", ft_memcmp(a, b, 0));
}*/