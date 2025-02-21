/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:03:09 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/08 11:09:00 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *) s)[i] = (unsigned char) 0;
		i++;
	}
}

/*int main(void)
{
    char str[50] = "hello";
    ft_bzero(str, 2);
    //printf("%p", ft_bzero(str, 2));
    return (0);
}*/
