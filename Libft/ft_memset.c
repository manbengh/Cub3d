/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:29:52 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/06 17:29:54 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/*int    main(void)
{
    char *s = "Bonjour";
    void *p = &s;
    printf("ma fonction : %s\n", (char *)ft_memset(p, 'a', 3));
    printf("vraie fonction : %s", (char *)memset(p, 'a', 3));
}*/