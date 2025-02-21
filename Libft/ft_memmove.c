/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:29:23 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/08 14:29:26 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (((unsigned char *)dest) < ((unsigned char *)src))
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n -1];
			n--;
		}
	}
	return (dest);
}

/*int main() {
      char src[20] = "Hello, World!";
      char dest[20];

      printf("Before memcpy:\n");
      printf("Source: %s\n", src);
      printf("Destination: %s\n", dest);
 
      ft_memmove(dest, src, 3);
  
      printf("After memcpy:\n");
      printf("Source: %s\n", src);
      printf("Destination: %s\n", dest);
 
      return 0;
}*/