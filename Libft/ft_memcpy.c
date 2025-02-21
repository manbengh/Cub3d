/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:10:18 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/08 12:38:58 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*#include<stdio.h>
int main() {
      char src[20] = "World!!";
      char dest[20]= "Hello";
  
      printf("Before memcpy:\n");
      printf("Source: %s\n", src);
      printf("Destination: %s\n", dest);
 
      ft_memcpy(dest, src, 3);
  
      printf("After memcpy:\n");
      printf("Source: %s\n", src);
      printf("Destination: %s\n", dest);
 
      return 0;
  }*/