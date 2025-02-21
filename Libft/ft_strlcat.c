/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:16:09 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/16 17:16:13 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<bsd/string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_s;
	size_t	len_d;

	if (size == 0 && (!src || !dest))
		return (0);
	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	j = len_d;
	i = 0;
	if (size == 0)
		return (len_s);
	if (len_d < (size - 1) && size > 0)
	{
		while (src[i] && len_d + i < size - 1)
			dest[j++] = src[i++];
		dest[j] = '\0';
	}
	if (len_d >= size)
		len_d = size;
	return (len_s + len_d);
}

/*int main(){
	char a[] = "";
	char b[] = "abc";
	char c[] = "";
	char d[] = "abc";
	printf("%ld\n", strlcat(c, d, 8));
	printf("%ld\n", ft_strlcat(a, b, 8));
}*/